#include "codegen.h"

extern int blocknumber;
extern int curLevel;
extern int blockoffs[MAXBLOCKS];
extern int outLevel[MAXBLOCKS];
extern int basicsizes[5];

int nextLabel;    /* Next available label number */
int stackFrameSize;   /* total stack frame size */

/* save rbp of each block in other regs, to access. 
 * accessLink[level] = R8 means R8 = RBP of this level's block*/
int accessLink[MAXBLOCKS] = { 0 };

/* Top-level entry for code generator.
   parseResult    = pointer to code:  (program foo (output) (progn ...))
   varsize  = size of local storage in bytes
   maxlabel = maximum label number used so far

_ADD this line to the end of your main program:
	genCode(parseresult, blockoffs[curLevel], labelnumber);
The generated code is printed out; use a text editor to extract it for
your .asm file.		 */
void genCode(TOKEN parseResult, int varsize, int maxlabel)
{
	TOKEN name, function, main;
	name = parseResult; 
	function = parseResult->operands;
	stackFrameSize = asmentry(name->stringVal, varsize);	/* print head and get the stack frame size*/
	int access = getRBPReg();		/* save rbp for access link */
	accessLink[curLevel] = access;
	asmrr64(MOV, RBP, access);
	asmjump(JMP, 0);				/* jump to L0 (start) */
	nextLabel = maxlabel + 1;		
	/* generate code for function declarations */
	while (function->whichToken == OP_FUN_DCL)
	{
		asmlabelstr(function->operands->operands->stringVal);	/* print label for this function*/
		genc(function);				/* generate code */
		function = function->next;	/* check next function*/
	}
	/* generate the main body */
	main = function;
	asmlabel(0);		/* label L0 (start)*/
	genc(main);
	asmexit(name->stringVal);		/* generate the exit code */
}

/* Get a free register.
 * Return the register number.
 * Set this register as used.
 */
int getReg(int kind)
{
	int i = 0;
	int stop = NUM_INT_REGS;
	if (kind != DATA_INT)
	{
		i = 16;
		stop = NUM_REGS;
	}

	for (; i < stop; i++)		
	{
		if (regs[i] == 0)
		{
			/* saved 4 registers */
			if (i == EDI || i == ESI || i == ESP || i == EBP)
			{
				continue;
			}
			regs[i] = 1;
			return i;
		}
	}
	if (i >= stop) 
		printf("Regster Overflow.\n");
	return RBASE;
}

/* get reg to save access link, in r8 - r15 */
int getRBPReg()
{
	int i;
	for (i = 8; i <= 15; i++)
	{
		if (regs[i] == 0)
		{
			if (i == 9)
				continue;
			regs[i] = 1;
			return i;
		}
	}
	if (i > 15)
		return RBASE;
}

/* Generate code for arithmetic expression, 
 * return a register number, the answer of the expression is saved in this register.
 */
int genExp(TOKEN code)
{
	int ret = -1; /* return the register number; */
	switch (code->tokenType) 
	{
	/* TOKEN code is a const data. mov the val into the register */
	case TYPE_DATA:
	{
		ret = getReg(DATA_INT);				/* get a free reg, e.g. eax */
		asmimmed(MOV, code->intVal, ret);	/* make a mov inst. e.g. mov eax, 1 */
		break;
	}
	/* TOKEN code is a ID. mov the val from ID's address into the register */
	case TYPE_ID:
	{
		SYMBOL funSym, idSym;
		char fname[16];
		/* make function name. function name is stored with a '_' ahead, to differ from the return var. */
		fname[0] = '_';
		strcpy(fname + 1, code->stringVal);
		funSym = searchst(fname);	/* funSym points to the symbol table entry of the function */

		int level = curLevel;
		idSym = searchlev(code->stringVal, level);	/* search var name in the current block */
		if (idSym == NULL)		/* var not in this block, check the out level */ 
			asmpush(RBP);		/* save rbp */
		while (idSym == NULL)		/* if var not in this block, find which level it is in */
		{
			level = outLevel[level];
			idSym = searchlev(code->stringVal, level);
		}
		if (level != curLevel)	/* var not in this block, get the rbp of the block it is defined. */
		{
			asmrr64(MOV, accessLink[level], RBP);
			stackFrameSize = getStackSize(level);	/* get the stack frame size of th*/
		}

		if (idSym->kind == SYM_ARGVAR)			/* pass by reference, in function body, b means *(&b) */
		{
			int temp = getReg(DATA_INT);		/* e.g. 0: rax */ 
			char name[20];				/* &b -> rax */ 
			sprintf(name, "&%s", code->stringVal);
			asmld64(MOV, idSym->offset - stackFrameSize, temp, name);
			ret = getReg(code->dataType);		/* get a free reg, e.g. ebx */ 
			asmldr(MOV, 0, temp, ret);			/* [rax] -> ebx;  mov ebx, [rax] */
			setRegUsed(ret);		/* use ebx */
			freeReg(temp);			/* free rax */
		}
		else		/* a normal variable */
		{
			ret = getReg(code->dataType);	/* get a free reg */
			/* DATA INT */
			if (idSym->dataType->kind != SYM_ARRAY)
				asmld(MOV, idSym->offset - stackFrameSize, ret, code->stringVal);
		}
		if (level != curLevel)		/* var not defined in current block, need to restore rbp after get var */
		{
			asmpop(RBP);	/* restore current rbp */
			stackFrameSize = getStackSize(curLevel);	/* restore the frame size */
		}
		break;
	}
	/* code is an operator, generate the expr, as right value */
	case TYPE_OPERATOR:
	{
		if (code->whichToken == OP_FUN_CALL)	/* fun call */
		{
			ret = genFunCall(code);
		}
		else if (code->whichToken == OP_ARRAYREF)	/* array reference OP_ARRAYREF->name->offset in array */
		{
			TOKEN arrayName = code->operands;		
			TOKEN arrayOffset = arrayName->next;	/* a const value, based on the address of array */
			/* find the array name in symbol table */
			SYMBOL arraySym = searchst(arrayName->stringVal);
			int offs = arraySym->offset + arrayOffset->intVal - stackFrameSize;
			/* calculate the index based on offset, used for print comment */
			int index = (arrayOffset->intVal) / (basicsizes[arraySym->basicType - 1]) + arraySym->dataType->lowBound;
			/* get a free reg */
			ret = getReg(arraySym->basicType);
			char refstr[20];
			sprintf(refstr, "%s[%d]", arrayName->stringVal, index);
			asmld(MOV, offs, ret, refstr);		/* generate the mov instruction */
		}
		else		/* normal operator, e.g. +, - ...*/
		{
			int leftReg = genExp(code->operands);	/* get the value of left operand in leftReg */
			int rightReg = genExp(code->operands->next);	/* get the value of right operand in rightReg */
			ret = genOp(code, leftReg, rightReg);	/* generate part of op */
		}
		break;
	}
	default: break;
	}
	return ret;			/* the value of the expression is saved in the register with number ret. */
}

/* get the value of an expr into the return value's register.
 * the expr is in the form: leftReg OP rightReg  
 */
int genOp(TOKEN code, int leftReg, int rightReg)
{
	int ret = 0;
	switch (code->whichToken)
	{
		case PLUS:
		{
			asmrr(ADD, rightReg, leftReg);		/* add left, right */
			ret = leftReg;		/* the answer is in leftReg */
			setRegUsed(ret);
			freeReg(rightReg);
			break;
		}
		case MINUS:
		{
			asmrr(SUB, rightReg, leftReg);		/* sub left, right */
			ret = leftReg;		/* left = left - right */
			setRegUsed(ret);
			freeReg(rightReg);
			break;
		}
		case MUL:		/* mul reg  (edx, eax) = eax * reg */
		{
			ret = EAX;		/* ret of mul is set to be EAX by x86 */
			if (regs[EAX] )		/* if eax is used, save the value */
			{
				asmrr(MOV, EAX, getReg(DATA_INT));
			}
			if (leftReg != EAX)		/* if leftReg is not eax, mov it into eax */
			{
				asmrr(MOV, leftReg, EAX);
				freeReg(leftReg);
			}
			asm1r(_MUL, rightReg);	/* mul rightReg */
			freeReg(rightReg);
			setRegUsed(ret);
			setRegUsed(EDX);
			break;
		}
		case DIV:		/* div reg;  eax = (edx, eax) / reg */
		{
			ret = EAX;		/* quotient is saved in EAX by x86 */
			if (regs[EAX])	/* if eax is used, save the value */
			{
				asmrr(MOV, EAX, getReg(DATA_INT));
			}
			if (leftReg != EAX)		/* if leftReg is not eax, mov it into eax */
			{
				asmrr(MOV, leftReg, EAX);
				freeReg(leftReg);
			}
			if (regs[EDX])		/* if eax is used, save the value */
			{
				asmrr(MOV, EDX, getReg(DATA_INT));
			}
			asmimmed(MOV, 0, EDX);		/* set edx to 0, ( assume not excceed 32 bits )*/
			asm1r(_DIV, rightReg);		/* div reg */
			freeReg(rightReg);
			setRegUsed(ret);		
			break;
		}
		case MOD:	/* mod is done by div instruction. remainder in EDX */
		{
			ret = EDX;		/* remainder is saved in EDX by x86 */
			if (regs[EAX])	
			{
				asmrr(MOV, EAX, getReg(DATA_INT));
			}
			if (leftReg != EAX)		/* if eax is used, save the value */
			{
				asmrr(MOV, leftReg, EAX);
				freeReg(leftReg);
			}
			if (regs[EDX])			/* if edx is used, save the value */
			{
				asmrr(MOV, EDX, getReg(DATA_INT));
			}
			asmimmed(MOV, 0, EDX); 
			asm1r(_DIV, rightReg);
			freeReg(rightReg);
			setRegUsed(ret);		/* remainder in EDX */
			break;
		}
		case EQ:		/* eax = ebx , cmp eax, ebx */
		{
			ret = nextLabel++;		/* get a new label */
			asmrr(CMP, rightReg, leftReg);
			asmjump(JE, ret);
			break;
		}
		case NE:		/* eax <> ebx , cmp eax, ebx */
		{
			ret = nextLabel++;
			asmrr(CMP, rightReg, leftReg);
			asmjump(JNE, ret);
			break;
		}
		case LT:		/* left < right, cmp left, right  jl label */
		{
			ret = nextLabel++;
			asmrr(CMP, rightReg, leftReg);		/* leftReg - rightReg set flags */
			asmjump(JL, ret);
			break;
		}
		case LE:		/* left <= right, cmp left, right  jle label */
		{
			ret = nextLabel++;
			asmrr(CMP, rightReg, leftReg);
			asmjump(JLE, ret);
			break;
		}
		case GT:		/* left <= right, cmp left, right  jg label */
		{
			ret = nextLabel++;
			asmrr(CMP, rightReg, leftReg);
			asmjump(JG, ret);
			break;
		}
		case GE:		/* left <= right, cmp left, right  jge label */
		{
			ret = nextLabel++;
			asmrr(CMP, rightReg, leftReg);
			asmjump(JGE, ret);
			break;
		}
		default:
			break;
	}
	freeReg(leftReg);
	freeReg(rightReg);
	return ret;
}

/* Generate code for a Statement from an intermediate-code form */
void genc(TOKEN code)
{
	resetRegs();		/* new statement, regs can be reset */
	if (code->tokenType != TYPE_OPERATOR)
	{
		if (code->tokenType == TYPE_DATA)
		{
			return;
		}
		printf("Bad code token");
	}

	switch (code->whichToken)
	{
		case OP_PROGN:		/* start of a code block */
		{
			TOKEN token = code->operands;
			while (token)
			{
				genc(token);
				token = token->next;	/* next code block */
			}
			break;
		}
		case ASSIGN:		/* assign statement, e.g. a := b  ASSIGN->a->b*/
		{
			TOKEN leftValue = code->operands;
			TOKEN rightValue = code->operands->next;
			int offset;		/* offset of the leftValue */
			int rightReg = genExp(rightValue);       /* generate rhs into a register */
			char leftname[20];
			/* the OP_ARRAYREF token doesn't have a name string, the array name is its oprands token */
			/* ARRAYREF as left, only need to get offset */
			if (leftValue->whichToken == OP_ARRAYREF)		
			{
				TOKEN arrayName = leftValue->operands;
				TOKEN arrayOffset = arrayName->next;
				SYMBOL arraySym = searchst(arrayName->stringVal);
				offset = (arraySym->offset + arrayOffset->intVal) - stackFrameSize;
				int index = (arrayOffset->intVal) / (basicsizes[arraySym->basicType - 1]) + arraySym->dataType->lowBound;
				sprintf(leftname, "%s[%d]", arrayName->stringVal, index);
				asmst(MOV, rightReg, offset, leftname);
			}
			else		/* other tokens have name string, and can search in table directly */
			{
				int level = curLevel;
				SYMBOL leftSymbol;
				leftSymbol = searchlev(leftValue->stringVal, level);
				if (leftSymbol == NULL)		/* var not in this block, check the out level */
					asmpush(RBP);
				while(leftSymbol == NULL)  /* find the symbol in out levels */
				{
					level = outLevel[level];
					leftSymbol = searchlev(leftValue->stringVal, level);
				}
				if (level != curLevel)		/* symbol in out level, need to save rbp */
				{
					asmrr64(MOV, accessLink[level], RBP);
					stackFrameSize = getStackSize(level);
				}

				if (leftSymbol != NULL)
					offset = leftSymbol->offset - stackFrameSize;          /* get offset of the var   */
				if (leftSymbol->kind == SYM_ARGVAR)		/* pass by reference, the address is stored in offset */
				{
					/* if reference argument is left value, get the address, mov value of rightReg in it */
					int temp = getReg(DATA_INT);		/* 0: rax */
					char name[20];				/* &b -> rax */ 
					sprintf(name, "&%s", leftValue->stringVal);
					asmld64(MOV, leftSymbol->offset - stackFrameSize, temp, name);
					asmstr(MOV, rightReg, 0, temp);		/* mov [rax], rightReg */
					freeReg(temp);
				}
				else		/* normal var, get offset */
				{ 
					strcpy(leftname, leftValue->stringVal);
					asmst(MOV, rightReg, offset, leftname);		/* mov [rbp-offset], rightReg */
				}
				if (level != curLevel)		/* restore rbp */
				{
					asmpop(RBP);
					stackFrameSize = getStackSize(curLevel);
				}
			}
			freeReg(rightReg);
			break;
		}
		case OP_LABEL:		/* asm a label */
		{
			asmlabel(code->operands->intVal);
			break;
		}
		case OP_GOTO:		/* asm a goto statement, jmp label */
		{
			asmjump(JMP, code->operands->intVal);
			break;
		}
		case IF:		/* IF -> ifbody -> else -> else body */
		{
			TOKEN exp = code->operands;
			TOKEN ifStmt = code->operands->next;
			TOKEN elseStmt = ifStmt->next;
			int ifLabel = genExp(exp);
			int elseLabel;
			int endIfLabel = nextLabel++;
			if (elseStmt)
				elseLabel = nextLabel++;
			
			/* have else */
			if (elseStmt)
			{
				asmjump(JMP, elseLabel);	/* 0 -> else_label */
				asmlabel(ifLabel);			/* if_label */
				genc(ifStmt);
				asmjump(JMP, endIfLabel);	/* jump -> endif */
				asmlabel(elseLabel);		/* else_label */
				genc(elseStmt);
				asmlabel(endIfLabel);		/* endif_label */
			}
			/* no else */
			else
			{
				asmjump(JMP, endIfLabel);	/* 0 -> endif_label */
				asmlabel(ifLabel);			/* if_label */
				genc(ifStmt);
				asmlabel(endIfLabel);		/* endif_label */
			}
			break;
		}
		case OP_FUN_CALL:		/* fun call statement */
		{
			genFunCall(code);
			break;
		}
		case OP_FUN_DCL:		/* function declatration OP_FUN_DCL->function->fname->fbody */
		{
			TOKEN functionName = code->operands->operands;
			TOKEN functionBody = functionName->next;
			char fname[16];
			fname[0] = '_';
			strcpy(fname + 1, functionName->stringVal);
			SYMBOL functionSymbol = searchst(fname);
			if (functionSymbol != NULL)
			{
				curLevel = functionSymbol->flevel;		/* enter function's level */
				stackFrameSize = getStackSize(curLevel);		/* get the frame size for this block */
				printf(funcTopCode, stackFrameSize);		/* make function head */
				int access = getRBPReg();
				accessLink[curLevel] = access;		/* save this function's rbp for access link use */
				asmrr64(MOV, RBP, access);

				SYMBOL func_ret = functionSymbol->args;		/* the first arg is the return var. */
				SYMBOL func_args = func_ret->args;		/* the second arg is the argument */
				int index = 0;
				/* save arguments form register to stack */
				while (func_args)
				{
					if (func_args->kind == SYM_ARGVAR)		/* call by reference, argument is address */
					{
						int argReg = argRegs[index++];
						setRegUsed(argReg);
						int offset = func_args->offset - stackFrameSize;
						asmst64(MOV, argReg, offset, func_args->nameString);
					}
					else		/* argurments by value */
					{
						int argReg = argRegs[index++];
						setRegUsed(argReg);
						int offset = func_args->offset - stackFrameSize;
						asmst(MOV, argReg, offset, func_args->nameString);
					}
					func_args = func_args->args;
				}
				genc(functionBody);		/* generate routine body */
				/* save return value in EAX */
				int offset = func_ret->offset - stackFrameSize;
				asmld(MOV, offset, EAX, func_ret->nameString);

				directPrint(funBotCode);		/* print function end */
				curLevel = outLevel[curLevel];		/* restore level */
				stackFrameSize = getStackSize(curLevel);
			}
			else
			{
				printf("Function declaration error!\n");
			}
			break;
		}
		default:
			break;
	}
}

/* generate codes for a fun call, put return value in the return register */
int genFunCall(TOKEN code)
{
	int ret = -1;
	TOKEN argList = code->operands->next;

	int count = 0;
	char fname[16];
	fname[0] = '_';
	strcpy(fname + 1, code->stringVal); 
	SYMBOL fsym = searchst(fname);		/* function symbol */
	SYMBOL fargsym = fsym->args->args;
	SYMBOL asym;
	/* move argument into registers before call */
	while (argList != NULL)
	{
		asym = searchst(argList->stringVal);
		if (fargsym->kind == SYM_ARGVAR)			/* pass by reference, in function body, b means *(&b) */
		{
			if (asym->kind == SYM_ARGVAR)			/* if the argument is already a reference, means it is already the address, then pass value*/
			{
				int temp = getReg(DATA_INT);		/* get a free temp  */
				asmld64(MOV, asym->offset - stackFrameSize, temp, argList->stringVal);
				if (temp != argRegs[count])			/* move to argument use reg */
				{
					asmrr64(MOV, temp, argRegs[count]); /* store values into argument use reg */
					setRegUsed(argRegs[count++]);
					freeReg(temp);
				}
			}
			else	/* need to get the address of the var and pass */
			{
				int temp = getReg(DATA_INT);		/* get a free reg, e.g. 0: rax  */
				char name[20];				/* &b -> rax */
				sprintf(name, "&%s", code->stringVal);
				asmld64(LEA, asym->offset - stackFrameSize, temp, name);	/* get address: lea rax, [rbp-offs] */
				if (temp != argRegs[count])
				{
					asmrr64(MOV, temp, argRegs[count]);		
					setRegUsed(argRegs[count++]);
					freeReg(temp);
				}
			}
		}
		else		/* pass by value */
		{
			int temp = genExp(argList);		/* put one arg's value in temp */
			if (temp != argRegs[count])
			{
				asmrr(MOV, temp, argRegs[count]); /* store values into arg reg */
				setRegUsed(argRegs[count++]);
				freeReg(temp);
			}
		}
		argList = argList->next;	/* deal with next argument */
		fargsym = fargsym->args;
	}
	int temp;
	if (regs[EAX] == 1)		/* eax is used before */
	{
		asmpush(EAX);		/* save */
		asmcall(code->stringVal);			/* return is EAX */
		temp = getReg(fsym->basicType);		/* get the return value into another free reg */
		asmrr(MOV, EAX, temp);
		asmpop(EAX);		/* restore the eax before*/
	}
	else		/* return value in eax */
	{
		asmcall(code->stringVal);
		temp = EAX;
	}
	ret = temp;
	for (int i = 0; i < count; i++)		/* free temp reg */
	{
		freeReg(argRegs[i]);
	}
	setRegUsed(ret);
	return ret;
}

/* set regs to be unused */
void resetRegs()
{
	for (int i = 0; i < NUM_REGS; i++)
	{
		regs[i] = 0;
	}
	for (int i = 0; i < NUM_REGS; i++)
	{
		if (accessLink[i] != 0)
			regs[accessLink[i]] = 1;
	}
}

/* set a reg to be free */
void freeReg(int regNum)
{
	if (regNum >= 0 && regNum < NUM_REGS)
	{
		regs[regNum] = 0;
	}
	else
	{
		printf("Error: wrong register assignment from freeReg!\n");
	}
}

/* set a reg to be used */
void setRegUsed(int regNum)
{
	if (regNum >= 0 && regNum < NUM_REGS)
	{
		regs[regNum] = 1;
	}
	else
	{
		printf("Error: wrong register assignment from setRegUsed!\n");
	}
}

/* get stack frame size for a block */
int getStackSize(level)
{
	int stacksize;		
	/* blockoffs[level] is the space all local var in the block needs. align to 16 */
	stacksize = roundup(blockoffs[level],16);
	return stacksize;
}
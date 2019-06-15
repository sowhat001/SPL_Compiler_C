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
		switch (code->dataType)
		{
			case DATA_INT:
			{
				ret = getReg(DATA_INT);				/* get a free reg, e.g. eax */
				asmimmed(MOV, code->intVal, ret);	/* make a mov inst. e.g. mov eax, 1 */
				break;
			}
			case DATA_REAL:
			{
				ret = getReg(DATA_REAL);
				makeflit(code->realVal, nextLabel);
				asmldflit(MOVSD, nextLabel++, ret);
				break;
			}
		}
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
		if (idSym == NULL)		/* var not in this block, check the out level*/ 
			asmpush(RBP);
		while (idSym == NULL)
		{
			level = outLevel[level];
			idSym = searchlev(code->stringVal, level);
		}
		if (level != curLevel)
		{
			asmrr64(MOV, accessLink[level], RBP);
			stackFrameSize = getStackSize(level);
		}
		
		if (idSym->nestLevel == 0)
		{
			int temp_reg = getReg(DATA_INT);
			asmld(MOV, 0, temp_reg, "static link");
			ret = getReg(DATA_INT);
			asmld(MOV, idSym->offset - stackFrameSize, ret, code->stringVal);
			break;
		}

		if (code->whichToken == OP_FUN_CALL)
		{
			ret = genFunCall(code);
		}
		else
		{
			if (idSym->kind == SYM_ARGVAR)			// pass by reference, in function body, b means *(&b)
			{
				int temp = getReg(DATA_INT);		// 0: rax
				char name[20];				// &b -> rax 
				sprintf(name, "&%s", code->stringVal);
				asmld64(MOV, idSym->offset - stackFrameSize, temp, name);
				ret = getReg(code->dataType);		// get a free reg, e.g. ebx 
				asmldr(MOV, 0, temp, ret);			// [rax] -> ebx;  mov ebx, [rax]
				setRegUsed(ret);		// use ebx
				freeReg(temp);			// free rax
			}
			else
			{
				ret = getReg(code->dataType);
				// DATA_INT
				if (ret < NUM_INT_REGS)
				{
					if (idSym->dataType->kind != SYM_ARRAY)
					{
						asmld(MOV, idSym->offset - stackFrameSize, ret, code->stringVal);
					}
				}
				else
				{
					asmld(MOVSD, idSym->offset - stackFrameSize, ret, code->stringVal);
				}
			}
		}
		if (level != curLevel)
		{
			asmpop(RBP);
			stackFrameSize = getStackSize(curLevel);
		}
		break;
	}
	case TYPE_OPERATOR:
	{
		if (code->whichToken == OP_FUN_CALL)
		{
			ret = genFunCall(code);
		}
		else if (code->whichToken == OP_ARRAYREF)
		{
			TOKEN arrayName = code->operands;
			TOKEN arrayOffset = arrayName->next;
			SYMBOL arraySym = searchst(arrayName->stringVal);
			int offs = arraySym->offset + arrayOffset->intVal - stackFrameSize;
			int index = (arrayOffset->intVal) / (basicsizes[arraySym->basicType - 1]) + arraySym->dataType->lowBound;
			ret = getReg(arraySym->basicType);
			char refstr[20];
			sprintf(refstr, "%s[%d]", arrayName->stringVal, index);
			asmld(MOV, offs, ret, refstr);
		}
		else
		{
			int leftReg = genExp(code->operands);
			int rightReg = genExp(code->operands->next);
			ret = genOp(code, leftReg, rightReg);
		}
		break;
	}
	default:
		break;
	}
	return ret;
}

int genOp(TOKEN code, int leftReg, int rightReg)
{
	int ret = 0;
	switch (code->whichToken)
	{
		case PLUS:
		{
			if (hasFloat(leftReg, rightReg))
			{
				asmrr(ADDSD, rightReg, leftReg);
			}
			else
			{
				asmrr(ADD, rightReg, leftReg);
			}
			ret = leftReg;
			setRegUsed(ret);
			freeReg(rightReg);
			break;
		}
		case MINUS:
		{
			if (hasFloat(leftReg, rightReg))
			{
				asmrr(SUBSD, rightReg, leftReg);
			}
			else
			{
				asmrr(SUB, rightReg, leftReg);
			}
			ret = leftReg;
			setRegUsed(ret);
			freeReg(rightReg);
			break;
		}
		case MUL:
		{
			if (hasFloat(leftReg, rightReg))
			{
				
			}
			else
			{
				ret = EAX;
				if (regs[EAX] && leftReg != EAX)
				{
					asmrr(MOV, EAX, getReg(DATA_INT));
					asmrr(MOV, leftReg, EAX);
					freeReg(leftReg);
				}
				else if (leftReg != EAX)
				{
					asmrr(MOV, leftReg, EAX);
					freeReg(leftReg);
				}
				asm1r(_MUL, rightReg);
				freeReg(rightReg);
				setRegUsed(ret);
				setRegUsed(EDX);
			}
			break;
		}
		case DIV:
		{
			if (hasFloat(leftReg, rightReg))
			{

			}
			else
			{
				ret = EAX;
				if (regs[EAX] && leftReg != EAX)
				{
					asmrr(MOV, EAX, getReg(DATA_INT));
					asmrr(MOV, leftReg, EAX);
					freeReg(leftReg);
				}
				else if (leftReg != EAX)
				{
					asmrr(MOV, leftReg, EAX);
					freeReg(leftReg);
				}
				if (regs[EDX])
				{
					asmrr(MOV, EDX, getReg(DATA_INT));
				}
				asmimmed(MOV, 0, EDX);
				asm1r(_DIV, rightReg);
				freeReg(rightReg);
				setRegUsed(ret);
				setRegUsed(EDX);
			}
			break;
		}

		case REAL_DIV:
		{

			break;
		}
		case MOD:
		{
			if (hasFloat(leftReg, rightReg))
			{

			}
			else
			{
				ret = EDX;
				if (regs[EAX] && leftReg != EAX)
				{
					asmrr(MOV, EAX, getReg(DATA_INT));
					asmrr(MOV, leftReg, EAX);
					freeReg(leftReg);
				}
				else if (leftReg != EAX)
				{
					asmrr(MOV, leftReg, EAX);
					freeReg(leftReg);
				}
				if (regs[EDX])
				{
					asmrr(MOV, EDX, getReg(DATA_INT));
				}
				asmimmed(MOV, 0, EDX);
				asm1r(_DIV, rightReg);
				freeReg(rightReg);
				setRegUsed(ret);
				setRegUsed(EDX);
			}
			break;
		}
		case EQ:
		{
			ret = nextLabel++;
			asmrr(CMP, rightReg, leftReg);
			asmjump(JE, ret);
			break;
		}
		case NE:
		{
			ret = nextLabel++;
			asmrr(CMP, rightReg, leftReg);
			asmjump(JNE, ret);
			break;
		}
		case LT:
		{
			ret = nextLabel++;
			asmrr(CMP, rightReg, leftReg);
			asmjump(JL, ret);
			break;
		}
		case LE:
		{
			ret = nextLabel++;
			asmrr(CMP, rightReg, leftReg);
			asmjump(JLE, ret);
			break;
		}
		case GT:
		{
			ret = nextLabel++;
			asmrr(CMP, rightReg, leftReg);
			asmjump(JG, ret);
			break;
		}
		case GE:
		{
			ret = nextLabel++;
			asmrr(CMP, rightReg, leftReg);
			asmjump(JGE, ret);
			break;
		}
		case FLOAT:
		{
			ret = getReg(DATA_REAL);			
			asmfloat(rightReg, ret);
			setRegUsed(ret);
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
	resetRegs();
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
		case OP_PROGN:
		{
			TOKEN token = code->operands;
			while (token)
			{
				genc(token);
				token = token->next;
			}
			break;
		}
		case ASSIGN:
		{
			TOKEN leftValue = code->operands;
			TOKEN rightValue = code->operands->next;
			int offset;		// offset of the leftValue
			int rightReg = genExp(rightValue);       // generate rhs into a register 
			char leftname[20];
			// the OP_ARRAYREF token doesn't have a name string, the array name is its oprands token
			if (leftValue->whichToken == OP_ARRAYREF)		
			{
				TOKEN arrayName = leftValue->operands;
				TOKEN arrayOffset = arrayName->next;
				SYMBOL arraySym = searchst(arrayName->stringVal);
				offset = (arraySym->offset + arrayOffset->intVal) - stackFrameSize;
				int index = (arrayOffset->intVal) / (basicsizes[arraySym->basicType - 1]) + arraySym->dataType->lowBound;
				sprintf(leftname, "%s[%d]", arrayName->stringVal, index);
				switch (code->dataType)
				{
				case DATA_INT:
					asmst(MOV, rightReg, offset, leftname);
					break;
				case DATA_REAL:
					asmst(MOVSD, rightReg, offset, leftname);
					break;
				default:
					break;
				}
			}
			else		// other tokens have name string, and can search in table directly 
			{
				int level = curLevel;
				SYMBOL leftSymbol;
				leftSymbol = searchlev(leftValue->stringVal, level);
				if (leftSymbol == NULL)		// var not in this block, check the out level
					asmpush(RBP);
				while(leftSymbol == NULL)
				{
					level = outLevel[level];
					leftSymbol = searchlev(leftValue->stringVal, level);
				}
				if (level != curLevel)
				{
					asmrr64(MOV, accessLink[level], RBP);
					stackFrameSize = getStackSize(level);
				}

				//SYMBOL leftSymbol = searchst(leftValue->stringVal);
				if (leftSymbol != NULL)
					offset = leftSymbol->offset - stackFrameSize;          /* net offset of the var   */
				if (leftSymbol->kind == SYM_ARGVAR)		// pass by reference, the address is stored in offset
				{
					int temp = getReg(DATA_INT);		// 0: rax
					char name[20];				// &b -> rax 
					sprintf(name, "&%s", leftValue->stringVal);
					asmld64(MOV, leftSymbol->offset - stackFrameSize, temp, name);
					asmstr(MOV, rightReg, 0, temp);
					freeReg(temp);
				}
				else
				{ 
					strcpy(leftname, leftValue->stringVal);
					switch (code->dataType)
					{
					case DATA_INT:
						asmst(MOV, rightReg, offset, leftname);
						break;
					case DATA_REAL:
						asmst(MOVSD, rightReg, offset, leftname);
						break;
					default:
						break;
					}
				}
				if (level != curLevel)
				{
					asmpop(RBP);
					stackFrameSize = getStackSize(curLevel);
				}
			}
			freeReg(rightReg);
			break;
		}
		case OP_LABEL:
		{
			asmlabel(code->operands->intVal);
			break;
		}
		case OP_GOTO:
		{
			asmjump(JMP, code->operands->intVal);
			break;
		}
		case IF:
		{
			TOKEN exp = code->operands;
			TOKEN ifStmt = code->operands->next;
			TOKEN elseStmt = code->operands->next->next;
			int ifLabel = genExp(exp);
			int elseLabel;
			int endIfLabel = nextLabel++;
			if (elseStmt)
			{
				elseLabel = nextLabel++;
			}
			
			// have else
			if (elseStmt)
			{
				asmjump(JMP, elseLabel);	// 0 -> else_label
				asmlabel(ifLabel);			// if_label
				genc(ifStmt);
				asmjump(JMP, endIfLabel);	// jump -> endif
				asmlabel(elseLabel);		// else_label
				genc(elseStmt);
				asmlabel(endIfLabel);		// endif_label
			}
			// no else
			else
			{
				asmjump(JMP, endIfLabel);	// 0 -> endif_label
				asmlabel(ifLabel);			// if_label
				genc(ifStmt);
				asmlabel(endIfLabel);		// endif_label
			}
			break;
		}
		case OP_FUN_CALL:
		{
			genFunCall(code);
			break;
		}
		case OP_FUN_DCL:
		{
			TOKEN functionName = code->operands->operands;
			TOKEN functionBody = functionName->next;
			char fname[16];
			fname[0] = '_';
			strcpy(fname + 1, functionName->stringVal);
			SYMBOL functionSymbol = searchst(fname);
			if (functionSymbol != NULL)
			{
				curLevel = functionSymbol->flevel;
				stackFrameSize = getStackSize(curLevel);		// get the frame size for this block
				printf(funcTopCode, stackFrameSize);
				int access = getRBPReg();
				accessLink[curLevel] = access;
				asmrr64(MOV, RBP, access);

				SYMBOL func_ret = functionSymbol->args;		// the first arg is the return var. 
				SYMBOL func_args = func_ret->args;		// the second arg is the argument
				int index = 0;
				while (func_args)
				{
					if (func_args->kind == SYM_ARGVAR)		// call by reference, argument is address
					{
						int argReg = argRegs[index++];
						setRegUsed(argReg);
						int offset = func_args->offset - stackFrameSize;
						asmst64(MOV, argReg, offset, func_args->nameString);
					}
					else		// by value
					{
						switch (func_args->basicType)
						{
						case DATA_INT:
						{
							int argReg = argRegs[index++];
							setRegUsed(argReg);
							int offset = func_args->offset - stackFrameSize;
							asmst(MOV, argReg, offset, func_args->nameString);
						}
						break;
						case DATA_REAL:
						{
							int argReg = argRegs[index++];
							setRegUsed(argReg);
							int offset = func_args->offset - stackFrameSize;
							asmst(MOVSD, argReg, offset, func_args->nameString);
						}
						break;
						default:
							break;
						}
					}
					func_args = func_args->args;
				}
				genc(functionBody);	// routine body
				switch (func_ret->basicType)
				{
				case DATA_INT:
				{
					int offset = func_ret->offset - stackFrameSize;
					asmld(MOV, offset, EAX, func_ret->nameString);
				}
				break;
				case DATA_REAL:
				{
					int offset = func_ret->offset - stackFrameSize;
					asmld(MOVSD, offset, EAX, func_ret->nameString);
				}
				default:
					break;
				}
				directPrint(funBotCode);
				curLevel = outLevel[curLevel];
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

int genFunCall(TOKEN code)
{
	int ret = -1;
	TOKEN argList = code->operands->next;

	if (strstr(code->stringVal, "write"))
	{
		if (argList->tokenType == TYPE_DATA)
		{
			SYMBOL sym = searchst(argList->stringVal);
			if (argList->dataType == DATA_STRING)
			{
				asmlitarg(nextLabel, argRegs[0]);		// move the _ADDr of string to EDI 
				asmcall(code->stringVal);
				makeblit(argList->stringVal, nextLabel++);
			}
			else if (argList->dataType == DATA_CHAR)	// print char as a string 
			{
				char s[2];
				s[0] = argList->charVal;
				s[1] = '\0';
				asmlitarg(nextLabel, EDI);
				asmcall(code->stringVal);
				makeblit(argList->stringVal, nextLabel++);
			}
			else if (argList->dataType == DATA_INT)
			{
				int temp = getReg(DATA_INT);
				asmld(MOV, sym->offset - stackFrameSize, temp, sym->nameString);
				asmrr(MOV, temp, EDI);
				asmcall(code->stringVal);
			}
			else if (argList->dataType == DATA_REAL)
			{
				int temp = getReg(DATA_REAL);
				asmld(MOVSD, sym->offset - stackFrameSize, temp, sym->nameString);
				asmrr(MOVSD, temp, EDI);
				asmcall(code->stringVal);
			}
		}
		else if (argList->tokenType == TYPE_ID)
		{
			SYMBOL argSym = searchst(argList->stringVal);
			int offset = argSym->offset - stackFrameSize;
			asmld(MOV, offset, EAX, argList->stringVal);		// get local variable from stack
			asmrr(MOV, EAX, argRegs[0]);		// pass value to the argument register EDI
			asmcall(code->stringVal);
		}
		else if (argList->tokenType == TYPE_OPERATOR)
		{
			int des_reg = genExp(argList);		// generate asm code for the expr, get the value in des_reg
			asmrr(MOV, des_reg, argRegs[0]);
			asmcall(code->stringVal);
		}
	}
	// other procedure
	else
	{
		int count = 0;
		char fname[16];
		fname[0] = '_';
		strcpy(fname + 1, code->stringVal);
		SYMBOL fsym = searchst(fname);		// function symbol
		SYMBOL fargsym = fsym->args->args;
		SYMBOL asym;
		while (argList != NULL)
		{
			asym = searchst(argList->stringVal);
			if (fargsym->kind == SYM_ARGVAR)			// pass by reference, in function body, b means *(&b)
			{
				if (asym->kind == SYM_ARGVAR)
				{
					int temp = getReg(DATA_INT);		// put one arg's value in temp
					asmld64(MOV, asym->offset - stackFrameSize, temp, argList->stringVal);
					if (temp != argRegs[count])
					{
						asmrr64(MOV, temp, argRegs[count]); // score values into arg reg
						setRegUsed(argRegs[count++]);
						freeReg(temp);
					}
				}
				else
				{
					int temp = getReg(DATA_INT);		// 0: rax
					char name[20];				// &b -> rax 
					sprintf(name, "&%s", code->stringVal);
					asmld64(LEA, asym->offset - stackFrameSize, temp, name);		// lea rax, [rbp-offs]
					if (temp != argRegs[count])
					{
						asmrr64(MOV, temp, argRegs[count]);		// mov rdi, rax
						setRegUsed(argRegs[count++]);
						freeReg(temp);
					}
				}
			}
			else
			{
				int temp = genExp(argList);		// put one arg's value in temp
				if (temp != argRegs[count])
				{
					asmrr(MOV, temp, argRegs[count]); // score values into arg reg
					setRegUsed(argRegs[count++]);
					freeReg(temp);
				}
			}
			argList = argList->next;
			fargsym = fargsym->args;
		}
		int temp;
		if (regs[EAX] == 1)
		{
			asmpush(EAX);
			asmcall(code->stringVal);		// return is EAX
			temp = getReg(fsym->basicType);
			asmrr(MOV, EAX, temp);
			asmpop(EAX);
		}
		else
		{
			asmcall(code->stringVal);
			temp = EAX;
		}
		ret = temp;
		for (int i = 0; i < count; i++)
		{
			freeReg(argRegs[i]);
		}
		setRegUsed(ret);
	}
	return ret;
}

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

int hasFloat(int lhs_reg, int rhs_reg)
{
	if ((lhs_reg >= NUM_INT_REGS && lhs_reg < NUM_REGS) ||
		(rhs_reg >= NUM_INT_REGS && rhs_reg < NUM_REGS))
	{
		return 1;
	}
	return 0;
}

int bothFloat(int lhs_reg, int rhs_reg)
{
	if ((lhs_reg >= NUM_INT_REGS && lhs_reg < NUM_REGS) &&
		(rhs_reg >= NUM_INT_REGS && rhs_reg < NUM_REGS))
	{
		return 1;
	}
	return 0;
}

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

int getStackSize(level)
{
	int stacksize;
	stacksize = roundup(blockoffs[level],16);
	return stacksize;
}
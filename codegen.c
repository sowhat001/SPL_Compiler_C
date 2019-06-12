#include "codegen.h"

extern int blocknumber;
extern int curLevel;
extern int basicsizes[5];

int nextLabel;    /* Next available label number */
int stackFrameSize;   /* total stack frame size */

/* Top-level entry for code generator.
   parseResult    = pointer to code:  (program foo (output) (progn ...))
   varsize  = size of local storage in bytes
   maxlabel = maximum label number used so far

Add this line to the end of your main program:
	genCode(parseresult, blockoffs[blocknumber], labelnumber);
The generated code is printed out; use a text editor to extract it for
your .s file.
		 */

void genCode(TOKEN parseResult, int varsize, int maxlabel)
{
	TOKEN name, function, main;
	name = parseResult;
	function = parseResult->operands;
	stackFrameSize = asmentry(name->stringVal, varsize);
	asmjump(JMP, 0);	// jump to L0 (start)
	nextLabel = maxlabel + 1;
	while (function->whichToken == OP_FUN_DCL)
	{
		asmlabelstr(function->operands->operands->stringVal);
		genc(function);
		function = function->next;
	}

	main = function;
	asmlabel(0);		// label L0 (start)
	curLevel = 1;
	genc(main);
	asmexit(name->stringVal);
}

/* Trivial version: always returns RBASE + 0 */
/* Get a register.   */
/* Need a type parameter or two versions for INTEGER or REAL */
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
			if (i == EDI || i == ESI || i == ESP || i == EBP)
			{
				continue;
			}
			regs[i] = 1;
			return i;
		}
	}
	if (i >= stop) printf("Regster Overflow.\n");

	return RBASE;
}

/* Trivial version */
/* Generate code for arithmetic expression, return a register number */
int genExp(TOKEN code)
{
	int ret = -1; //return the register number;
	switch (code->tokenType)
	{
	case TYPE_DATA:
	{
		switch (code->dataType)
		{
			case DATA_INT:
			{
				ret = getReg(DATA_INT);
				asmimmed(MOVL, code->intVal, ret);
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
	case TYPE_ID:
	{
		SYMBOL funSym, idSym;
		char fname[16];
		fname[0] = '_';
		strcpy(fname + 1, code->stringVal);
		funSym = searchst(fname);
		idSym = searchst(code->stringVal);

		if (idSym->nestLevel == 0)
		{
			int temp_reg = getReg(DATA_INT);
			asmld(MOVL, 0, temp_reg, "static link");
			ret = getReg(DATA_INT);
			asmld(MOVL, idSym->offset - stackFrameSize, ret, code->stringVal);
			break;
		}

		if (code->whichToken == OP_FUN_CALL)
		{
			ret = genFunCall(code);
		}
		else
		{
			ret = getReg(code->dataType);
			// DATA_INT
			if (ret < NUM_INT_REGS)
			{
				if (idSym->dataType->kind != SYM_ARRAY)
				{
					asmld(MOVL, idSym->offset - stackFrameSize, ret, code->stringVal);
				}
			}
			else
			{
				asmld(MOVSD, idSym->offset - stackFrameSize, ret, code->stringVal);
			}
		}
		break;
	}
	case TYPE_OPERATOR:
	{
		if (code->whichToken == OP_FUN_CALL)
		{
			ret = genFunCall(code);
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
				asmrr(ADDSD, leftReg, rightReg);
			}
			else
			{
				asmrr(ADDL, leftReg, rightReg);
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
				asmrr(SUBSD, leftReg, rightReg);
			}
			else
			{
				asmrr(SUBL, leftReg, rightReg);
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
					asmrr(MOVL, EAX, getReg(DATA_INT));
					asmrr(MOVL, leftReg, EAX);
					freeReg(leftReg);
				}
				else if (leftReg != EAX)
				{
					asmrr(MOVL, leftReg, EAX);
					freeReg(leftReg);
				}
				if (regs[EDX])
				{
					asmrr(MOVL, EDX, getReg(DATA_INT));
				}
				asmimmed(MOVL, 0, EDX);
				asm1r(IMULL, rightReg);
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
					asmrr(MOVL, EAX, getReg(DATA_INT));
					asmrr(MOVL, leftReg, EAX);
					freeReg(leftReg);
				}
				else if (leftReg != EAX)
				{
					asmrr(MOVL, leftReg, EAX);
					freeReg(leftReg);
				}
				if (regs[EDX])
				{
					asmrr(MOVL, EDX, getReg(DATA_INT));
				}
				asmimmed(MOVL, 0, EDX);
				asm1r(DIVL, rightReg);
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
					asmrr(MOVL, EAX, getReg(DATA_INT));
					asmrr(MOVL, leftReg, EAX);
					freeReg(leftReg);
				}
				else if (leftReg != EAX)
				{
					asmrr(MOVL, leftReg, EAX);
					freeReg(leftReg);
				}
				if (regs[EDX])
				{
					asmrr(MOVL, EDX, getReg(DATA_INT));
				}
				asmimmed(MOVL, 0, EDX);
				asm1r(DIVL, rightReg);
				freeReg(rightReg);
				setRegUsed(ret);
				setRegUsed(EDX);
			}
			break;
		}
		case EQ:
		{
			ret = nextLabel++;
			asmrr(CMPL, leftReg, rightReg);
			asmjump(JE, ret);
			break;
		}
		case NE:
		{
			ret = nextLabel++;
			asmrr(CMPL, leftReg, rightReg);
			asmjump(JNE, ret);
			break;
		}
		case LT:
		{
			ret = nextLabel++;
			asmrr(CMPL, leftReg, rightReg);
			asmjump(JL, ret);
			break;
		}
		case LE:
		{
			ret = nextLabel++;
			asmrr(CMPL, leftReg, rightReg);
			asmjump(JLE, ret);
			break;
		}
		case GT:
		{
			ret = nextLabel++;
			asmrr(CMPL, leftReg, rightReg);
			asmjump(JG, ret);
			break;
		}
		case GE:
		{
			ret = nextLabel++;
			asmrr(CMPL, leftReg, rightReg);
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
			SYMBOL leftSymbol = searchst(leftValue->stringVal);

			// simple var
			if (leftSymbol != NULL)
			{
				int rightReg = genExp(rightValue);                        /* generate rhs into a register */
				int offset = leftSymbol->offset - stackFrameSize;          /* net offset of the var   */
				switch (code->dataType)
				{
				case DATA_INT:
					asmst(MOVL, rightReg, offset, leftValue->stringVal);
					break;
				case DATA_REAL:
					asmst(MOVSD, rightReg, offset, leftValue->stringVal);
					break;
				default:
					break;
				}
			}
			break;
		}
		case IF:
		{
			TOKEN exp = code->operands;
			TOKEN ifStmt = code->operands->next;
			TOKEN elseStmt = code->operands->next->next;
			int ifLabel = genExp(exp);
			int elseLabel;
			int endIfLabel;
			if (elseStmt)
			{
				elseLabel = nextLabel++;
			}
			endIfLabel = nextLabel++;

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
			TOKEN functionBody = code->operands->operands->next;
			char fname[16];
			fname[0] = '_';
			strcpy(fname + 1, functionName->stringVal);
			SYMBOL functionSymbol = searchst(fname);
			if (functionSymbol != NULL)
			{
				directPrint(funcTopCode);
				SYMBOL func_ret = functionSymbol->args;		// the first arg is the return var. 
				SYMBOL func_args = func_ret->args;		// the second arg is the argument
				int index = 0;
				while (func_args)
				{
					switch (func_args->basicType)
					{
					case DATA_INT:
					{
						int argReg = argRegs[index++];
						setRegUsed(argReg);
						int offset = func_args->offset - stackFrameSize;
						asmst(MOVL, argReg, offset, func_args->nameString);
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
					func_args = func_args->args;
				}
				genc(functionBody);	// routine body
				switch (func_ret->basicType)
				{
				case DATA_INT:
				{
					int offset = func_ret->offset - stackFrameSize;
					asmld(MOVL, offset, EAX, func_ret->nameString);
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
				asmlitarg(nextLabel, argRegs[0]);		// move the addr of string to EDI 
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
				asmld(MOVL, sym->offset - stackFrameSize, temp, sym->nameString);
				asmrr(MOVL, temp, EDI);
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
			asmld(MOVL, offset, EAX, argList->stringVal);		// get local variable from stack
			asmrr(MOVL, EAX, argRegs[0]);		// pass value to the argument register EDI
			asmcall(code->stringVal);
		}
		else if (argList->tokenType == TYPE_OPERATOR)
		{
			int des_reg = genExp(argList);		// generate asm code for the expr, get the value in des_reg
			asmrr(MOVL, des_reg, argRegs[0]);
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

		while (argList != NULL)
		{
			int temp = genExp(argList);		// put one arg's value in temp
			if (temp != argRegs[count])
			{
				asmrr(MOVL, temp, argRegs[count]); // score values into arg reg
				setRegUsed(argRegs[count++]);
				freeReg(temp);
			}
			argList = argList->next;
		}
		asmcall(code->stringVal);
		setRegUsed(EAX);		// return is EAX
		int temp = getReg(fsym->basicType);
		asmrr(MOVL, EAX, temp);
		freeReg(EAX);
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
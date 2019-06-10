#include "symtab.h"
#include "genasm.h"
#include "codegen.h"
#include "utils.h"

extern int blocknumber;
extern int basicsizes[5];

int nextlabel;    /* Next available label number */
int stkframesize;   /* total stack frame size */

TOKEN inline_funcall = NULL;        /* to handle function calls in the RHS of an ASSIGNOP statement */
int num_inlines_processed;
int saved_inline_reg;
int saved_inline_regs[10];

int saved_label_num = -1;           /* saves the label number of the top-level label; used to handle repeat statements */

double saved_float_reg = -DOUBLE_MAX;  /* in an ASSIGNOP, holds the value of the float being assigned */
int saved_float_reg_num = -1;       /* the register where the float in saved_float_reg is stored */

int nil_flag = 0;           /* if assigning a NUMBERTOK with whichToken == 0 to a ptr, set to 1 */

TOKEN saved_rhs_reg = NULL;         /* in an ASSIGNOP, save the TOKEN representing the RHS (value to be assigned) */
int saved_rhs_reg_num = -1;         /* in an ASSIGNOP, save the register location of saved_rhs_reg */

int nested_refs = 0;        /* used in POINTEROP in genop(). probably can be deprecated but have not checked */
TOKEN first_op_genarith = NULL;     /* used to signal if multiple pointer dereferences are made in a single statement */
TOKEN nested_ref_stop_at = NULL;    /* in an AREFOP in genop(), and if multiple ptr dereferences are made in a single statement,
									   signals the second-to-last pointer dereference */

TOKEN last_ptr = NULL;              /* the last pointer to be referenced in any single statement */
int last_ptr_reg_num;               /* the register number last_ptr */
int last_ptr_deref_offs;            /* the offset of the field being dereferenced by the statement in which last_ptr is set */

int last_id_reg_num;                /* the register number location of the last identifier referenced in a statement (EXCEPT pointers) */

					 /* integer regs */
int used_regs[32] = { 0, 0, 0, 0, 0, 0, 0, 0,
/* FP regs; r8d to r15d */
 0, 0, 0, 0, 0, 0, 0, 0,
	/* xmm0 to xmm15 */
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
int arg_reg[4] = { EDI, ESI, EDX, ECX };

char* funcTopCode[] = 
{
  "	pushq	%rbp			# save base pointer on stack",
  "	movq	%rsp, %rbp		# move stack pointer to base pointer",
  "	subq	$32, %rsp		# make space for this stack frame",
  "",
};
char* funBotCode[] = 
{
	"	movq    %rbp, %rsp",
	"	popq    %rbp",
	"	ret",
	"",
};

#define NUM_INT_REGS    8
#define NUM_FP_REGS     24
#define NUM_REGS        32

void print_used_regs();
int symbol_is_null_int(char *str);

/* Top-level entry for code generator.
   parseResult    = pointer to code:  (program foo (output) (progn ...))
   varsize  = size of local storage in bytes
   maxlabel = maximum label number used so far

Add this line to the end of your main program:
	gencode(parseresult, blockoffs[blocknumber], labelnumber);
The generated code is printed out; use a text editor to extract it for
your .s file.
		 */

void gencode(TOKEN parseResult, int varsize, int maxlabel)
{
	TOKEN name, function, main;
	name = parseResult;
	function = parseResult->operands;
	stkframesize = asmentry(name->stringVal, varsize);
	asmjump(JMP, 0);	// jump to L0 (start)
	while (function->whichToken == OP_FUN_DCL)
	{
		asmlabelstr(function->operands->operands->stringVal);
		genc(function);
		function = function->next;
	}

	main = function;
	nextlabel = maxlabel + 1;
	asmlabel(0);		// label L0 (start)
	blocknumber = 1;
	genc(main);
	asmexit(name->stringVal);
}

/* Trivial version: always returns RBASE + 0 */
/* Get a register.   */
/* Need a type parameter or two versions for INTEGER or REAL */
int getreg(int kind)
{
	int i = 0;
	int stop = NUM_INT_REGS;
	if (kind != DATA_INT)
	{
		//        i = 8;
		i = 16;
		stop = NUM_REGS;
	}

	for (; i < 7; i++)
	{
		if (used_regs[i] == 0)
		{
			if (i == EDI || i == ESI || i == EDX || i == ECX)
			{
				continue;
			}
			used_regs[i] = 1;
			return i;
		}
	}
	if (i >= stop) printf("Regster Overflow.\n");

	return RBASE;
}

/* Trivial version */
/* Generate code for arithmetic expression, return a register number */
int genarith(TOKEN code)
{

	int num, reg_num, lhs_reg, rhs_reg;
	SYMBOL sym;

	switch (code->tokenType)
	{
	case TYPE_DATA:
		switch (code->dataType)
		{
		case DATA_INT:
		{
			num = code->intVal;
			reg_num = getreg(DATA_INT);
			if (num >= MINIMMEDIATE && num <= MAXIMMEDIATE)
			{
				if (last_ptr && last_ptr_reg_num > -1)
				{

					// asmimmed(MOVQ, num, last_ptr_reg_num);
					asmimmed(MOVQ, num, reg_num);
					last_ptr_reg_num = -1;
				}
				else if (!nil_flag)
				{
					asmimmed(MOVL, num, reg_num);
				}
				else
				{
					asmimmed(MOVQ, num, reg_num);
				}

			}
		}
		break;
		case DATA_REAL:
		{
			/* Generate literal for the value of the constant, then
			load the literal into a register. */

			reg_num = getreg(DATA_REAL);
			saved_float_reg = code->realVal;
			saved_float_reg_num = reg_num;

			makeflit(code->realVal, nextlabel);
			asmldflit(MOVSD, nextlabel++, reg_num);
		}
		break;
		}
		break;
	case TYPE_ID:
	{
		sym = searchst(code->stringVal);
		if (!sym)
		{
			return symbol_is_null_int(code->stringVal);
		}

		if (sym->nestLevel == 0)
		{
			int temp_reg = getreg(DATA_INT);
			asmld(MOVL, 0, temp_reg, "static link");
			reg_num = getreg(DATA_INT);
			asmld(MOVL, sym->offset - stkframesize, reg_num, code->stringVal);
			break;
		}

		num = sym->offset;

		if (sym->kind == SYM_FUNCTION)
		{
			reg_num = getreg(sym->dataType->basicType);
			inline_funcall = code;
			//genc(code->next);
		}
		else
		{

			reg_num = getreg(code->dataType);
			// DATA_INT
			if (reg_num < NUM_INT_REGS)
			{

				SYMBOL temp = searchst(code->stringVal);
				if (!temp)
				{
					return symbol_is_null_int(code->stringVal);
				}

				SYMBOL next = temp->dataType;

				if (!next)
				{
					return symbol_is_null_int(NULL);
				}

				if (next->kind != SYM_ARRAY)
				{
					last_id_reg_num = reg_num;
					asmld(MOVL, sym->offset - stkframesize, reg_num, code->stringVal);
				}

			}
			// DATA_REAL
			else
			{

				last_id_reg_num = reg_num;
				asmld(MOVSD, sym->offset - stkframesize, reg_num, code->stringVal);
			}

		}
	}
	break;
	case TYPE_OPERATOR:
	{
		if (code->whichToken == MOD)
		{
			lhs_reg = genarith(code->operands);
			rhs_reg = genarith(code->operands->next);
			asmrr(MOVL, lhs_reg, EAX);
			asmrr(MOVL, lhs_reg, EDX);
			asmcall("mod");
			reg_num = EAX;
			break;
		}
		if (code->whichToken == MUL)
		{
			lhs_reg = genarith(code->operands);
			rhs_reg = genarith(code->operands->next);
			if (lhs_reg != EAX)
			{
				asmrr(MOVL, lhs_reg, EAX);
			}
			asm1r(IMULL, rhs_reg);
			reg_num = EAX;
			break;
		}

		if (first_op_genarith == NULL)
		{
			first_op_genarith = code;
		}
		else
		{
			nested_refs = 1;
		}

		if (code->whichToken == MINUS)
		{
			lhs_reg = genarith(code->operands->next);
		}
		else
		{
			lhs_reg = genarith(code->operands);
		}

		int count = 0;
		if (code->operands->next)
		{
			if (code->whichToken == MINUS)
			{
				rhs_reg = genarith(code->operands);
			}
			else if (code->whichToken == OP_FUNCALL)
			{
				TOKEN arglist = code->operands->next;
				int temp_reg;
				while (arglist)
				{
					temp_reg = genarith(arglist);
					if (temp_reg != arg_reg[count])
					{
						asmrr(MOVL, temp_reg, arg_reg[count]); // score values into arg reg
						mark_reg_used(arg_reg[count++]);
						free_reg(temp_reg);
					}
					arglist = arglist->next;
				}
			}
			else rhs_reg = genarith(code->operands->next);
		}
		else
		{
			// FLOATOP (and possibly FIXOP?)
			rhs_reg = 0;
		}

		/************* key code ***************/
		if (code->whichToken == OP_FUNCALL) saved_inline_reg = EAX;

		if (code->whichToken == MINUS)
			lhs_reg = genop(code, lhs_reg, rhs_reg);
		else
			lhs_reg = genop(code, rhs_reg, lhs_reg);

		if (code->whichToken == OP_FUNCALL)
		{
			int i;
			for (i = 0; i < count; i++)
			{
				free_reg(arg_reg[i]);
			}
		}
		else free_reg(rhs_reg);

		reg_num = lhs_reg;

	}
	break;
	default:
		return symbol_is_null_int(NULL);
		break;
	}

	first_op_genarith = NULL;

	return reg_num;
}


int genop(TOKEN code, int rhs_reg, int lhs_reg)
{
	int out = 0;
	int which_val = code->whichToken;

	if (which_val == PLUS)
	{
		if (at_least_one_float(lhs_reg, rhs_reg))
		{
			asmrr(ADDSD, rhs_reg, lhs_reg);
		}
		else
		{
			asmrr(ADDL, rhs_reg, lhs_reg);
		}
		out = lhs_reg;
	}
	else if (which_val == MINUS)
	{
		if (lhs_reg > 15 && lhs_reg < NUM_REGS)
		{
			asmfneg(lhs_reg, getreg(DATA_REAL));
			rhs_reg = lhs_reg;
		}
		else if (at_least_one_float(lhs_reg, rhs_reg))
		{
			asmrr(SUBSD, rhs_reg, lhs_reg);
		}
		else
		{
			asmrr(SUBL, rhs_reg, lhs_reg);
		}
		out = lhs_reg;
	}
	else if (which_val == MUL)
	{
		if (at_least_one_float(lhs_reg, rhs_reg))
		{
			asmrr(MULSD, rhs_reg, lhs_reg);
		}
		else
		{
			asmrr(IMULL, rhs_reg, lhs_reg);
		}
		out = lhs_reg;
	}
	else if (which_val == REAL_DIV)
	{
		if (at_least_one_float(lhs_reg, rhs_reg))
		{
			asmrr(DIVSD, rhs_reg, lhs_reg);
		}
		else
		{
			asmrr(DIVL, rhs_reg, lhs_reg);
		}
		out = lhs_reg;
	}
	else if (which_val == MOD)
	{
		int temp_reg = getreg(DATA_INT);
		asmrr(MOVL, lhs_reg, temp_reg);
		asmrr(DIVL, rhs_reg, lhs_reg);
		asmrr(IMULL, rhs_reg, lhs_reg);
		asmrr(SUBL, lhs_reg, temp_reg);
		out = temp_reg;
	}
	else if (which_val == EQ)
	{
		out = nextlabel++;
		asmrr(CMPL, rhs_reg, lhs_reg);
		asmjump(JE, out);
	}
	else if (which_val == NE)
	{
		out = nextlabel++;
		asmrr(CMPQ, rhs_reg, lhs_reg);
		asmjump(JNE, out);
	}
	else if (which_val == LT)
	{
		out = nextlabel++;
		asmrr(CMPL, rhs_reg, lhs_reg);
		asmjump(JL, out);
	}
	else if (which_val == LE)
	{
		out = nextlabel++;
		asmrr(CMPL, rhs_reg, lhs_reg);
		asmjump(JLE, out);
	}
	else if (which_val == GE)
	{
		out = nextlabel++;
		asmrr(CMPL, rhs_reg, lhs_reg);
		asmjump(JGE, out);
	}
	else if (which_val == GT)
	{
		out = nextlabel++;
		asmrr(CMPL, rhs_reg, lhs_reg);
		asmjump(JG, out);
	}
	else if (which_val == OP_FUNCALL)
	{

		int temp_reg;
		if (inline_funcall)
		{
			asmcall(inline_funcall->stringVal);
			temp_reg = getreg(DATA_INT);
			if (temp_reg != EAX) asmrr(MOVL, EAX, temp_reg);
		}
		else
		{
		}

		out = temp_reg;
	}
	else if (which_val == OP_ARRAYREF)
	{

		if (saved_float_reg != -DOUBLE_MAX)
		{
			asmldr(MOVQ, code->operands->next->intVal, lhs_reg, rhs_reg, "^.");
		}
		else
		{
			if (last_id_reg_num > -1)
			{
				int temp = rhs_reg;
				if (last_id_reg_num > -1 && last_id_reg_num < 16)
				{
					if (last_id_reg_num == rhs_reg)
					{
						rhs_reg = getreg(DATA_INT);
						free_reg(temp);
					}

					if (last_ptr && last_ptr_reg_num > -1)
					{

						int found = 0;
						SYMBOL temp0, temp1, temp2, temp3, temp4, temp5, typsym;
						temp0 = searchst(last_ptr->stringVal);
						typsym = NULL;

						if (!temp0)
						{
							return symbol_is_null_int(code->stringVal);
						}

						temp1 = searchst(temp0->next->nameString);

						if (!temp1)
						{
							return symbol_is_null_int(code->stringVal);
						}

						if (temp1->dataType->kind == SYM_ARRAY)
						{
							typsym = temp1->dataType;
							while (typsym && typsym->kind == SYM_ARRAY)
							{
								typsym = typsym->dataType;
							}

							if (!typsym)
							{
								return symbol_is_null_int(code->stringVal);
							}

							temp2 = typsym->dataType;
							if (temp2 && temp2->kind == SYM_RECORD)
							{
								temp3 = temp2->dataType;

								while (temp3 && !found)
								{
									if (temp3->offset == last_ptr_deref_offs)
									{
										found = 1;

										if (temp3->size > basicsizes[DATA_INT])
										{
											asmldr(MOVQ, code->operands->next->intVal, lhs_reg, rhs_reg, "^.");
										}
										else
										{
											asmldr(MOVL, code->operands->next->intVal, lhs_reg, rhs_reg, "^.");
										}
									}
									temp3 = temp3->next;
								}
							}

						}
						else
						{

						}

						// probably broken
						if (!found)
						{
							asmldr(MOVL, code->operands->next->intVal, lhs_reg, rhs_reg, "^.");
						}

						last_ptr_reg_num = -1;
					}
					else
					{
						asmldr(MOVL, code->operands->next->intVal, lhs_reg, rhs_reg, "^.");
					}

				}
				else
				{
					if (last_id_reg_num == rhs_reg)
					{
						rhs_reg = getreg(DATA_REAL);
						free_reg(temp);
					}
					asmldr(MOVSD, code->operands->next->intVal, lhs_reg, rhs_reg, "^.");
				}
				// else // WHAT ABOUT IF LHS IS > 15 ???????????????????????????????????????????????????
			}
			else
			{
				free_reg(rhs_reg);
				rhs_reg = getreg(DATA_REAL);
				asmldr(MOVSD, code->operands->next->intVal, lhs_reg, rhs_reg, "^.");
			}

		}

		last_ptr_reg_num = rhs_reg;

		out = rhs_reg;

	}
	else if (which_val == FLOAT)
	{
		int freg = getreg(DATA_REAL);
		asmfloat(rhs_reg, freg);
		free_reg(lhs_reg);
		free_reg(rhs_reg);
		out = freg;
	}
	//else if (which_val == OP_FIX)
	//{
	//	int dreg = getreg(DATA_INT);
	//	asmfix(lhs_reg, dreg);
	//	free_reg(lhs_reg);
	//	free_reg(rhs_reg);
	//	out = dreg;
	//}

	if (inline_funcall != NULL && num_funcalls_in_tree > 0)
	{
		saved_inline_reg = rhs_reg;
	}

	return out;
}

/* Generate code for a Statement from an intermediate-code form */
void genc(TOKEN code)
{
	int reg_num, offs;
	reset_regs();
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
		last_ptr = NULL;
		last_ptr_reg_num = -1;
		last_ptr_deref_offs = -1;
		nested_ref_stop_at = NULL;
		for (int i = 0; i < 10; i++)
		{
			saved_inline_regs[i] = -1;
		}
		num_inlines_processed = 0;
		last_id_reg_num = -1;
		while (token)
		{
			saved_inline_reg = 0;       // may need to set to -1 as sentinel value
			genc(token);
			token = token->next;
		}
	}
	break;
	case ASSIGN:
	{
		//TOKEN lastOperand = code;
 		//	while (lastOperand->operands != NULL)
		//{
		//	lastOperand = lastOperand->operands;
		//}
		//TOKEN outer_link = code->operands->next;

		//lhs = code->operands;
		//rhs = lhs->next;
		TOKEN leftValue = code->operands;
		TOKEN rightValue = code->operands->next;
		SYMBOL leftSymbol = searchst(leftValue->stringVal);

		//if (code->operands->operands != NULL)
		//{
		//	nested_ref_stop_at = code->operands->operands;
		//}
		reg_num = genarith(rightValue);                        /* generate rhs into a register */
		saved_rhs_reg = rightValue;
		saved_rhs_reg_num = reg_num;

		// simple var
		if (leftSymbol)
		{
			offs = leftSymbol->offset - stkframesize;          /* net offset of the var   */
			switch (code->dataType)
			{
			case DATA_INT:
				asmst(MOVL, reg_num, offs, leftValue->stringVal);
				break;
			case DATA_REAL:
				asmst(MOVSD, reg_num, offs, leftValue->stringVal);
				break;
			default:
				break;
			}
		}
		//if (leftValue->operands)
		//{
		//	reg_num = genarith(leftValue->operands);
		//}
		nil_flag = 0;
		saved_float_reg = -DOUBLE_MAX;
		saved_rhs_reg = NULL;
		saved_rhs_reg_num = -1;
		nested_refs = 0;
		last_ptr = NULL;
		last_ptr_reg_num = -1;
		nested_ref_stop_at = NULL;
	} // end of case OP_ASSIGN
	break;
	case IF:
	{
		TOKEN exp = code->operands;
		TOKEN ifStmt = code->operands->next;
		TOKEN elseStmt = code->operands->next->next;
		int if_label_num = genarith(exp);
		int else_label_num;
		int endif_label_num;
		if (elseStmt)
		{
			else_label_num = nextlabel++;
		}
		endif_label_num = nextlabel++;

		// have else
		if (elseStmt)
		{
			asmjump(JMP, else_label_num);	// 0 -> else_label

			asmlabel(if_label_num);			// if_label
			genc(elseStmt);
			asmjump(JMP, endif_label_num);	// jump -> endif

			asmlabel(else_label_num);		// else_label
			genc(elseStmt->next);
			asmlabel(endif_label_num);		// endif_label
		}
		// no else
		else
		{
			asmjump(JMP, endif_label_num);	// 0 -> endif_label

			asmlabel(if_label_num);			// if_label
			genc(elseStmt);
			//asmjump(JMP, endif_label_num);	// jump -> endif, not necessary

			asmlabel(endif_label_num);		// endif_label
		}

	}
	break;
	// procedures. functions will be generate by OP_ASSIGN / genarith
	case OP_FUNCALL:
	{
		TOKEN lhs, rhs;
		SYMBOL sym;
		lhs = code->operands;
		rhs = code->operands->next;
		SYMBOL argsym;

		if (strstr(lhs->stringVal, "write"))
		{      // write/writeln
			sym = searchst(lhs->stringVal);

			if (rhs->tokenType == DATA_STRING)
			{
				asmlitarg(nextlabel, EDI);
				asmcall(lhs->stringVal);
				makeblit(rhs->stringVal, nextlabel++);
			}
			else if (rhs->tokenType == DATA_CHAR)
			{
				char s[2];
				s[0] = rhs->charVal;
				s[1] = '\0';
				asmlitarg(nextlabel, EDI);
				asmcall(lhs->stringVal);
				makeblit(rhs->stringVal, nextlabel++);
			}
			else if (rhs->tokenType == TYPE_OPERATOR)
			{
				if (rhs->whichToken == OP_ARRAYREF)
				{

					sym = searchst(rhs->operands->stringVal);
					if (!sym)
					{
						sym = searchst(rhs->operands->operands->stringVal);
						if (sym)
						{
							reg_num = getreg(DATA_INT);
							offs = sym->offset - stkframesize;
							asmld(MOVQ, offs, reg_num, sym->nameString);

							offs = rhs->operands->next->intVal;
							int temp = getreg(DATA_REAL);
							asmldr(MOVSD, offs, reg_num, temp, "^.");

							asmcall(lhs->stringVal);

						}
					}
				}
			}

			else if (sym != NULL && (sym->dataType->basicType == DATA_INT ||
				sym->dataType->basicType == DATA_REAL))
			{

				SYMBOL argsym;

				if (rhs->tokenType == TYPE_DATA)
				{
					printf("\nTYPE_DATA UNFINISHED\n");
				}

				else if (rhs->tokenType == TYPE_ID)
				{
					argsym = searchst(rhs->stringVal);
					if (!argsym)
					{
						printf("Error: no symbol table entry for var \"%s\"", rhs->stringVal);
						return;
					}

					if (argsym->basicType == DATA_INT)
					{
						reg_num = getreg(DATA_INT);
						offs = argsym->offset - stkframesize;

						asmld(MOVL, offs, reg_num, argsym->nameString);
						asmrr(MOVL, reg_num, EDI);
						asmcall(lhs->stringVal);
					}

					else if (argsym->basicType == DATA_REAL)
					{
						reg_num = getreg(DATA_REAL);
						offs = argsym->offset - stkframesize;
						asmld(MOVSD, offs, reg_num, argsym->nameString);
						asmrr(MOVSD, reg_num, EDI);
						asmcall(lhs->stringVal);
					}
				}
			}
		}
		// other procedure
		else
		{
			TOKEN arglist = rhs;
			int temp_reg, index = 0;
			while (arglist)
			{
				temp_reg = genarith(arglist);
				asmrr(MOVL, temp_reg, arg_reg[index]); // score values into arg reg
				mark_reg_used(arg_reg[index++]);
				free_reg(temp_reg);
				arglist = arglist->next;
			}
			asmcall(lhs->stringVal);
			free_reg(arg_reg[0]);
			free_reg(arg_reg[1]);
			free_reg(arg_reg[2]);
			free_reg(arg_reg[3]);
		}
	} // end of CASE OP_FUNCALL
	break;
	case OP_FUN_DCL:
	{
		TOKEN functionName = code->operands->operands;
		TOKEN functionBody = code->operands->operands->next;
		SYMBOL functionSymbol = searchst(functionName->stringVal);
		if (functionSymbol != NULL)
		{
			cannedcode(funcTopCode);
			SYMBOL func_args = functionSymbol->args;
			int index = 0;
			while (func_args)
			{
				switch (func_args->basicType)
				{
				case DATA_INT:
				{
					reg_num = arg_reg[index++];
					mark_reg_used(reg_num);
					offs = func_args->offset - stkframesize;
					asmst(MOVL, reg_num, offs, func_args->nameString);
				}
				break;
				case DATA_REAL:
				{
					reg_num = arg_reg[index++];
					mark_reg_used(reg_num);
					offs = func_args->offset - stkframesize;
					asmst(MOVSD, reg_num, offs, func_args->nameString);
				}
				break;
				default:
					break;
				}
				func_args = func_args->next;
			}
			genc(functionBody);	// routine body
			switch (functionSymbol->basicType)
			{
			case DATA_INT:
			{
				offs = functionSymbol->offset - stkframesize;
				asmld(MOVL, offs, EAX, functionSymbol->nameString);
			}
			break;
			case DATA_REAL:
			{
				offs = functionSymbol->offset - stkframesize;
				asmld(MOVSD, offs, EAX, functionSymbol->nameString);
			}
			default:
				break;
			}
			cannedcode(funBotCode);
		}
		else
		{
			printf("Function declaration error!\n");
		}
		//lhs = code->operands;
		//rhs = code->operands->next;

		//blocknumber = lhs->operands->intVal;

		//cannedcode(funcTopCode);	// print function top code

		//TOKEN arglist;

		//// store arguments into vars(memory)
		//if (strcmp(lhs->stringVal, "function") == 0)
		//{
		//	arglist = lhs->operands->next->next->next;
		//}
		//else
		//{
		//	arglist = lhs->operands->next->next;
		//}
		//int index = 0;
		//while (arglist)
		//{
		//	SYMBOL argsym = searchst(arglist->stringVal);
		//	switch (argsym->basicType)
		//	{
		//	case DATA_INT:
		//	{
		//		reg_num = arg_reg[index++];
		//		mark_reg_used(reg_num);
		//		offs = argsym->offset - stkframesize;
		//		asmst(MOVL, reg_num, offs, argsym->nameString);
		//	}
		//	break;
		//	case DATA_REAL:
		//	{
		//		reg_num = arg_reg[index++];
		//		mark_reg_used(reg_num);
		//		offs = argsym->offset - stkframesize;
		//		asmst(MOVSD, reg_num, offs, argsym->nameString);
		//	}
		//	break;
		//	}
		//	arglist = arglist->next;
		//}
		////asmst2(MOVQ, 0);

		//genc(rhs);	// routine body

		//TOKEN fun_name = lhs->operands->next;

		//// store return value into %eax
		//if (strcmp(lhs->stringVal, "function") == 0)
		//{
		//	char fun_var[16];
		//	int i;
		//	fun_var[0] = '_';
		//	for (i = 1; i < 16; i++)
		//	{
		//		fun_var[i] = fun_name->stringVal[i - 1];
		//	}
		//	SYMBOL sym = searchst(fun_var);
		//	switch (sym->basicType)
		//	{
		//	case DATA_INT:
		//	{
		//		offs = sym->offset - stkframesize;
		//		asmld(MOVL, offs, EAX, sym->nameString);
		//	}
		//	break;
		//	case DATA_REAL:
		//	{
		//		offs = sym->offset - stkframesize;
		//		asmld(MOVSD, offs, EAX, sym->nameString);
		//	}
		//	break;
		//	}
		//}
		//cannedcode(funBotCode);
		break;
	}
	}
}

void reset_regs()
{
	int i;
	for (i = 0; i < NUM_REGS; i++)
	{
		used_regs[i] = 0;
	}
}

void free_reg(int reg_num)
{
	if (reg_num < 0 || reg_num >= NUM_REGS)
	{
		printf("Error: cannot free register number %d\n", reg_num);
		return;
	}
	used_regs[reg_num] = 0;
}

int at_least_one_float(int lhs_reg, int rhs_reg)
{
	if ((lhs_reg >= NUM_INT_REGS && lhs_reg < NUM_REGS) ||
		(rhs_reg >= NUM_INT_REGS && rhs_reg < NUM_REGS))
	{
		return 1;
	}
	return 0;
}

int both_float(int lhs_reg, int rhs_reg)
{
	if ((lhs_reg >= NUM_INT_REGS && lhs_reg < NUM_REGS) &&
		(rhs_reg >= NUM_INT_REGS && rhs_reg < NUM_REGS))
	{
		return 1;
	}
	return 0;
}

void mark_reg_unused(int reg_num)
{
	if (reg_num < 0 || reg_num >= NUM_REGS)
	{
		printf("1 Error: register %d out of bounds\n", reg_num);
		return;
	}
	used_regs[reg_num] = 0;
}

void mark_reg_used(int reg_num)
{
	if (reg_num < 0 || reg_num >= NUM_REGS)
	{
		printf("2 Error: register %d out of bounds\n", reg_num);
		return;
	}
	used_regs[reg_num] = 1;
}

int funcallin(TOKEN code)
{
	int num = num_funcalls_in_tree(code, 0);
	if (num > 0)
	{
		return 1;
	}
	return 0;
}

int num_funcalls_in_tree(TOKEN tok, int num)
{
	if (tok == NULL)
	{
		return num;
	}

	if (tok->whichToken == OP_FUNCALL)
	{
		num++;
	}
	if (tok->next != NULL)
	{
		num = num_funcalls_in_tree(tok->next, num);
	}
	if (tok->operands != NULL)
	{
		num = num_funcalls_in_tree(tok->operands, num);
	}

	return num;
}

int search_tree_str(TOKEN tok, char str[])
{
	if (tok == NULL)
	{
		return 0;
	}

	int found = 0;
	if (strcmp(tok->stringVal, str) == 0)
	{
		return 1;
	}
	if (tok->next != NULL)
	{
		found = search_tree_str(tok->next, str);
	}
	if (tok->operands != NULL)
	{
		found = search_tree_str(tok->operands, str);
	}

	return found;
}

void print_used_regs()
{
	printf("\nUsed registers: %d", used_regs[0]);

	for (int i = 1; i < NUM_REGS; i++)
	{
		printf(" %d", used_regs[i]);
	}
	printf("\n\n");
}

int symbol_is_null_int(char *str)
{
	if (str)
	{
		printf("Error: NULL symbol (\"%s\")\n", str);
	}
	return 0;
}

int is_equal(TOKEN a, TOKEN b)
{
	if (!a || !b)
	{
		return 0;
	}

	if ((long)a == (long)b)
	{
		return 1;
	}
	return 0;
}

int is_gen_purpose_reg(int reg_num)
{
	if (reg_num < 0 || reg_num >= NUM_INT_REGS)
	{
		return 0;
	}
	return 1;
}

int is_fp_reg(int reg_num)
{
	if (reg_num < NUM_INT_REGS || reg_num >= NUM_REGS)
	{
		return 0;
	}
	return 1;
}


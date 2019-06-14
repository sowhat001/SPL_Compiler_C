#define _CRT_SECURE_NO_WARNINGS
#include "parsef.h"
#pragma warning(disable:4996)

extern int yylineno;
extern int lineCount;
extern int curLevel;					/* current block level */
extern int blocknumber;       			/* Totle number of blocks */
extern int outLevel[MAXBLOCKS];			/* out layer */
extern int blockoffs[MAXBLOCKS];  		/* Storage offsets for each block */
extern int basicsizes[5];
extern int lineCount;					/* line count */
extern char* yytext;
int labelNumber = 1; 					/* the label order */

/* Arrayref token, like a[2], a is arrayToken, 2 is refExp */
TOKEN arrayRef(TOKEN arrayToken, TOKEN refExp)
{
	if (refExp->dataType != DATA_INT)
	{
		semanticError("The index of array must be integer");
		return NULL;
	}
	TOKEN arrRefToken = tokenAlloc();
	SYMBOL arraySymbol = searchst(arrayToken->stringVal);
	if (!arraySymbol)
	{
		char s[64];
		sprintf(s, "array \"%s\" not defined", arrayToken->stringVal);
		semanticError(s);
		return NULL;
	}
	arrRefToken->tokenType = TYPE_OPERATOR;
	arrRefToken->operands = arrayToken;
	arrRefToken->whichToken = OP_ARRAYREF;
	arrRefToken->dataType = arraySymbol->basicType;
	TOKEN offsetToken = createConst((refExp->intVal - arraySymbol->dataType->lowBound) * basicsizes[arraySymbol->basicType - 1]);
	arrayToken = link(arrayToken, offsetToken);
	return arrRefToken;
	/* arrayRef

	   arrayToken->offset
	*/
}

/* Create a token with const int value. Used in for loop (i = i + 1), array and record(offset) */
TOKEN createConst(int constInt)
{
	TOKEN ret = tokenAlloc();
	ret->tokenType = TYPE_DATA;
	ret->whichToken = INTEGER;
	ret->dataType = DATA_INT;
	ret->intVal = constInt;
	return ret;
}

/* Create a token with labelNum. Used in loop. Jump */
TOKEN createGoto(TOKEN labelToken)
{
	TOKEN ret = tokenAlloc();
	ret->tokenType = TYPE_OPERATOR;
	ret->whichToken = OP_GOTO;
	ret->operands = createConst(labelToken->operands->intVal);
	/* ret

	   constToken
	*/
	return ret;
}

/* Create a label. This function will use the system default lableNum and add itself, because it is anonymous label in loop parse, not the user's define label */
TOKEN createLabel()
{
	TOKEN ret = tokenAlloc();
	ret->tokenType = TYPE_OPERATOR;
	ret->whichToken = OP_LABEL;
	ret->operands = createConst(labelNumber++);
	/* ret

	   constToken
	*/
	return ret;
}

/* A ID token. check this token in symbol table.
symType and symEntry are changed.
dataType will be changed if it is a const token. */
TOKEN findId(TOKEN token)
{
	SYMBOL idSymbol = searchst(token->stringVal);

	if (!idSymbol)
	{
		char s[64];
		sprintf(s, "var \"%s\" not defined", token->stringVal);
		semanticError(s);
		return NULL;
	}

	if (idSymbol->kind == SYM_FUNCTION)
	{
		for (int i = MAX_STR_LENGTH; i > 0; i--)
		{
			token->stringVal[i] = token->stringVal[i - 1];
		}
		token->stringVal[0] = '_';
		idSymbol = searchst(token->stringVal);
	}
	if (idSymbol->kind == SYM_CONST)
	{
		token->tokenType = TYPE_DATA;
		switch (idSymbol->basicType)
		{
		case DATA_INT:
		{
			token->dataType = DATA_INT;
			token->intVal = idSymbol->constval.intNum;
			break;
		}
		case DATA_REAL:
		{
			token->dataType = DATA_REAL;
			token->realVal = idSymbol->constval.realNum;
			break;
		}
		case DATA_CHAR:
		{
			token->dataType = DATA_CHAR;
			token->charVal = idSymbol->constval.charConst;
			break;
		}
		case DATA_STRING:
		{
			token->dataType = DATA_STRING;
			for (int i = 0; i <= MAX_STR_LENGTH; i++)
			{
				token->stringVal[i] = idSymbol->constval.stringConst[i];
			}
			break;
		}
		default:
			break;
		}
	}
	else
	{
		token->symEntry = idSymbol;
		token->symType = idSymbol->dataType;
		if (token->symType == NULL)
		{
			token->dataType = idSymbol->basicType;
		}
		else if ((token->symType)->kind == SYM_BASIC)
		{
			token->dataType = token->symType->basicType;
		}
	}
	return token;
}

/* Link list and newItem */
TOKEN link(TOKEN list, TOKEN newItem)
{
	if (list == NULL)
	{
		return newItem;
	}
	TOKEN temp = list;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newItem;
	return list;

	/* list->newItem */
}

/* Make the assign expression like a := 2
op's dataType is changed */
TOKEN makeAssign(TOKEN op, TOKEN leftValue, TOKEN rightValue)
{
	int leftType = leftValue->dataType;
	int rightType = rightValue->dataType;
	if (leftType == 0 || rightType == 0)
	{
		semanticError("There exists an operand which is not data type.");
		return NULL;
	}
	else
	{
		if (leftType != rightType)
		{
			//type fix
			semanticWarning("Inconsistent type of operands.");
			if (leftType == DATA_INT && rightType == DATA_REAL)
			{
				//int = real
				rightValue->whichToken = OP_REAL_TO_INT;
				leftValue = link(leftValue, rightValue);
				op->operands = leftValue;
				op->dataType = leftType;
			}
			else if (leftType = DATA_REAL && rightType == DATA_INT)
			{
				//real = int
				rightValue->whichToken = OP_INT_TO_REAL;
				leftValue = link(leftValue, rightValue);
				op->operands = leftValue;
				op->dataType = leftType;
			}
			else if (leftType = DATA_CHAR && rightType == DATA_STRING)
			{
				//char = string
				rightValue->whichToken = OP_STRING_TO_CHAR;
				leftValue = link(leftValue, rightValue);
				op->operands = leftValue;
				op->dataType = leftType;
			}
			else
			{
				semanticError("There exists illegal assignment.");
				return NULL;
			}
		}
		else
		{
			leftValue = link(leftValue, rightValue);
			op->operands = leftValue;
			op->dataType = leftType;
		}
	}
	return op;
	/* op

	   leftValue->rightValue
	*/
}

/* make a begin statement with BEGIN sign or other sign. beginToken's type is changed to OP_PROGN. */
TOKEN makeBeginStmt(TOKEN beginToken, TOKEN stmt)
{
	beginToken->operands = stmt;
	beginToken->whichToken = OP_PROGN;
	beginToken->tokenType = TYPE_OPERATOR;
	return beginToken;
	/* beginToken(OP_PROGN)

	   stmt
	*/
}

/* make a binary operation expression include calculating and comparing like a + b or a > b
op's dataType is changed */
TOKEN makeBinOp(TOKEN op, TOKEN leftOperand, TOKEN rightOperand)
{
	int leftType = leftOperand->dataType;
	int rightType = rightOperand->dataType;
	if (leftType == 0 || rightType == 0 || leftType > DATA_CHAR || rightType > DATA_CHAR)
	{
		semanticError("There exists an operand which is not data type.");
		return NULL;
	}
	else
	{
		if (leftType != rightType)
		{
			//type fix
			semanticWarning("Inconsistent type of operands.");
			if (leftType == DATA_INT && rightType == DATA_REAL)
			{
				// int + real
				leftOperand->whichToken = OP_INT_TO_REAL;
			}
			else
			{
				// real + int
				rightOperand->whichToken = OP_INT_TO_REAL;
			}
			op->dataType = DATA_REAL;
		}
		else
		{
			op->dataType = leftType;
		}
		op->operands = leftOperand;
		leftOperand = link(leftOperand, rightOperand);
	}
	return op;
	/* op

	   leftOperand->rightOperand
	*/
}

/* switch case */
TOKEN makeCase(TOKEN caseToken, TOKEN judgeExp, TOKEN choices)
{
	caseToken->operands = judgeExp;
	judgeExp = link(judgeExp, choices);
	return caseToken;

	/* caseToken

	   judgeExp->choice->choice->choice ...

				 stmt	 stmt	 stmt ...
	*/
}

/* For loop. */
TOKEN makeFor(TOKEN forToken, TOKEN initAssign, TOKEN direction, TOKEN finalAssign, TOKEN beginToken, TOKEN loopStmt)
{
	if (initAssign->dataType != DATA_INT)
	{
		semanticError("Loop control variable should be integer.");
		return NULL;
	}
	//     for i:=2 to n do
	// 　　　　s:=s*i;
	TOKEN labelToken = createLabel();
	TOKEN gotoToken = createGoto(labelToken);
	TOKEN ifToken = tokenAlloc(); //if
	TOKEN comOp = tokenAlloc();
	TOKEN comID = tokenAlloc();
	TOKEN dirAssign = tokenAlloc();//i = i + 1, '='
	TOKEN dirCalOp = tokenAlloc();//i = i + 1, '+'
	TOKEN assID = tokenAlloc();// i = i + 1, first i
	TOKEN calID = tokenAlloc();//i = i + 1, //second i
	TOKEN constToken = createConst(1);//this is 1

	forToken = makeBeginStmt(forToken, initAssign);
	//initAssign本身是一个完整的赋值算式(i := 2)，在makeAssign里已经做好
	initAssign = link(initAssign, labelToken);
	labelToken = link(labelToken, ifToken);

	ifToken->tokenType = TYPE_OPERATOR;
	ifToken->whichToken = IF;

	comOp->tokenType = TYPE_OPERATOR;
	if (direction->whichToken == TO)
	{
		comOp->whichToken = LE;
	}
	else if (direction->whichToken == DOWNTO)
	{
		comOp->whichToken = GE;
	}
	comOp->dataType = DATA_INT;

	comID = copyToken(initAssign->operands);
	comOp = makeBinOp(comOp, comID, finalAssign);
	//但是finalAssign只是个表达式(n)，需要自己做好(makeBinOp)

	beginToken = makeBeginStmt(beginToken, loopStmt);

	ifToken = makeIf(ifToken, comOp, beginToken, NULL);
	//有了comop(if里的expression)和beginToken(thenstmt)，并且else不做任何操作，makeIf
	loopStmt = link(loopStmt, dirAssign);

	dirAssign->tokenType = TYPE_OPERATOR;
	dirAssign->whichToken = ASSIGN;
	dirAssign->dataType = DATA_INT;

	assID = copyToken(initAssign->operands);

	dirCalOp->tokenType = TYPE_OPERATOR;
	if (direction->whichToken == TO)
	{
		dirCalOp->whichToken = PLUS;
	}
	else if (direction->whichToken == DOWNTO)
	{
		dirCalOp->whichToken = MINUS;
	}
	dirCalOp->dataType = DATA_INT;
	dirAssign = makeAssign(dirAssign, assID, dirCalOp);
	dirAssign = link(dirAssign, gotoToken);

	calID = copyToken(initAssign->operands);

	dirCalOp = makeBinOp(dirCalOp, calID, constToken);
	return forToken;

	/* forToken(OP_PROGN)

	   initAssign(makeAssignStmt)->labelToken->ifToken

											   comOp->beginToken(OP_PROGN)

													  loopStmt->dirAssign(makeAssignStmt)

																assID->dirCalOp(PLUS/MINUS)

																	   calID->constToken(1)->gotoToken
	*/
}

/* A function call. get its arguments and check it is avaliable function name or not.
funcName's tokenType, whichToken, dataType are changed. dataType is return value's type
???是不是还要检查一下是不是和声明的参数一样
*/
TOKEN makeFuncall(TOKEN lpToken, TOKEN funcName, TOKEN arguments)
{
	funcName->tokenType = TYPE_OPERATOR;
	funcName->whichToken = OP_FUN_CALL;
	SYMBOL funSymbol = NULL;
	char fname[16];
	fname[0] = '_';
	strcpy(fname + 1, funcName->stringVal);
	funSymbol = searchst(fname);
	if (!funSymbol)
	{
		char s[64];
		sprintf(s, "function/procedure \"%s\" not defined", funcName->stringVal);
		semanticError(s);
		return NULL;
	}
	if (funSymbol->dataType == NULL)
		funcName->dataType = funSymbol->basicType;
	else
		funcName->dataType = funSymbol->dataType->basicType;
	// check type
	//TOKEN a;
	//SYMBOL fatype, atype;
	//if (funSymbol->args != NULL)
	//{
	//	fatype = funSymbol->args->args;			// The first args is return val
	//}
	//else
	//	fatype = funSymbol->args;
	//for (a = arguments; a != NULL; a = a->next)
	//{
	//	atype = a->symType;
	//	// only check simple types
	//	if (atype->basicType != fatype->basicType)
	//	{
	//		semanticError("function arguments don't match");
	//		return NULL;
	//	}
	//}
	funcName->operands = lpToken;				//???有什么用
	lpToken = link(lpToken, arguments);

	return funcName;
	/* funcName

	   lpToken->arguments
	*/
}

/* goto Token with user's given number */
TOKEN makeGoto(TOKEN intToken)
{
	/*return createGoto(get_internal_label_num(intToken->intVal));*/
	return intToken;
}

/* if Token */
TOKEN makeIf(TOKEN ifToken, TOKEN expression, TOKEN thenStmt, TOKEN elseStmt)
{
	ifToken->operands = expression;
	ifToken->tokenType = TYPE_OPERATOR;
	expression = link(expression, thenStmt);
	expression = link(expression, elseStmt);
	return ifToken;
	/* ifToken

	   expression->thenStmt->elseStmt
	*/
}

/* label token with user's given number */
TOKEN makeLabel(TOKEN labelNum, TOKEN stmt)
{
	//TOKEN labelToken = createLabel();
	//labelToken->operands = createConst(get_internal_label_num(labelNum->intVal));
	//labelToken = link(labelToken, stmt);
	//labelNum = makeBeginStmt(labelNum, labelToken);
	return labelNum;
	/* labelNum(OP_PROGN)

	   labelToken->stmt

	   constToken(user's number)
	*/
}

/* program make */
TOKEN makeProgram(TOKEN NameToken, TOKEN routine)
{
	NameToken->operands = routine;
	return NameToken;
}

/* repeat loop */
TOKEN makeRepeat(TOKEN repeatToken, TOKEN stmt, TOKEN untilToken, TOKEN expression)
{
	TOKEN outLabelToken = createLabel();
	TOKEN outGotoToken = createGoto(outLabelToken);
	TOKEN labelToken = createLabel();
	TOKEN gotoToken = createGoto(labelToken);
	TOKEN ifToken = tokenAlloc();
	repeatToken = makeBeginStmt(repeatToken, labelToken);
	repeatToken = link(repeatToken, outLabelToken);
	labelToken = link(labelToken, stmt);

	ifToken->tokenType = TYPE_OPERATOR;
	ifToken->whichToken = IF;
	stmt = link(stmt, ifToken);
	untilToken->whichToken = OP_PROGN;//???
	ifToken = makeIf(ifToken, expression, outGotoToken, gotoToken);

	return repeatToken;
	/* repeatToken(OP_PROGN)->outLabelToken

	   labelToken->stmt->ifToken

						 expression->outGotoToken->gotoToken
	*/
	//     repeat
	// 　　　　r:=a mod b;
	// 　　　　a:=b;b:=r;
	// 　　　until r=0;
}

/* make a signal case. Used in makeCase*/
TOKEN makeSignalCase(TOKEN judgeResult, TOKEN stmt)
{
	judgeResult->operands = stmt;
	return judgeResult;
}

/* unary op
op's dataType is changed. */
TOKEN makeUnaryOp(TOKEN op, TOKEN operand)
{
	if (operand->dataType == 0)
	{
		semanticError("There exists an operand which is not data type.");
	}
	op->dataType = operand->dataType;
	op->operands = operand;
	return op;
	/* op

	   operand
	*/
}

/* while loop */
TOKEN makeWhile(TOKEN whileToken, TOKEN expression, TOKEN doToken, TOKEN stmt)
{
	TOKEN labelToken = createLabel();
	TOKEN gotoToken = createGoto(labelToken);
	TOKEN ifToken = tokenAlloc();
	whileToken = makeBeginStmt(whileToken, labelToken);
	labelToken = link(labelToken, ifToken);

	ifToken->tokenType = TYPE_OPERATOR;
	ifToken->whichToken = IF;
	ifToken = makeIf(ifToken, expression, doToken, NULL);

	doToken = makeBeginStmt(doToken, stmt);
	stmt = link(stmt, gotoToken);

	return whileToken;
	/* whileLoken(OP_PROGN)

	   labelToken->ifToken

				  expression->doToken(OP_PROGN)

							  stmt->gotoToken
	*/
	//     while s<=10 do｛当s的值还未超过10时｝
	// 　　　　begin
	// 　　　　　n:=n+1;｛项数加1｝
	// 　　　　　s:=s+1/n;｛将下一项值累加到s｝
	// 　　　　end;
}

// token id's symType field is filled in with a newly created symbol table entry
void regConst(TOKEN id, TOKEN constok)
{
	SYMBOL sym;
	sym = insertsym(id->stringVal, SYM_CONST);
	sym->basicType = constok->dataType;		// DATA_INT DATA_REAL ...
	if (constok->tokenType == TYPE_DATA)		// check if the token is a data token 
	{
		// copy the data according to the type 
		switch (constok->dataType)
		{
		case DATA_INT:
			sym->constval.intNum = constok->intVal;
			sym->size = basicsizes[DATA_INT - 1];
			break;
		case DATA_REAL:
			sym->constval.realNum = constok->realVal;
			sym->size = basicsizes[DATA_REAL - 1];
			break;
		case DATA_CHAR:
			sym->constval.charConst = constok->charVal;
			sym->size = basicsizes[DATA_CHAR - 1];
			break;
		case DATA_STRING:
			strcpy(sym->constval.stringConst, constok->stringVal);
			sym->size = strlen(constok->stringVal);
			break;
		}
		id->symEntry = sym;		// fill in the symEntry field 
	}
	else
	{
		char s[64] = "incorrect const definition ";
		semanticError(s);
	}
}

// put new variables into symbol table
// e.g.: a,b,c : integer   create symbol table entry for a,b,c
// isvar=1: 参数引用传递  isvar=0: 参数值传递 isvar=2: 普通变量
void regVar(TOKEN varlist, TOKEN type, int isvar)
{
	TOKEN v;
	SYMBOL sym, typesym;
	sym = NULL;
	typesym = type->symType;		// typesym points to the symbol table entry of this type 
	for (v = varlist; v != NULL; v = v->next)
	{
		// get the pointer of the symbol entry of the token: 
		if (isvar == 1)
			sym = insertsym(v->stringVal, SYM_ARGVAR);
		else if (isvar == 0)
			sym = insertsym(v->stringVal, SYM_ARGLIST);
		else
			sym = insertsym(v->stringVal, SYM_VAR);
		
		sym->basicType = typesym->basicType;
		sym->dataType = typesym;		// here may have problems
		sym->size = typesym->size;
		// offset
		sym->offset = blockoffs[curLevel];
		blockoffs[curLevel] += sym->size;
		v->symEntry = sym; 	// record the symbol table entry in the token struct
	}
}

// get the type in symbol table by the string in a token, fill it in the symType of the token
TOKEN getType(TOKEN typetok)
{
	SYMBOL typesym;
	// search the symbol table for the type's symbol entry
	typesym = searchst(typetok->stringVal);

	if (typesym == NULL)
	{
		char s[64];
		sprintf(s, "type %s is used but not defined", typetok->stringVal);
		semanticError(s);
		return NULL;
	}
	else
	{
		// symType points to the type in symbol table 
		typetok->symType = typesym;
		typetok->symEntry = typesym;
	}
	return typetok;
}

// put a type definition into symbol table 
/* sym->name = alias->string
 *
 */
void regType(TOKEN alias, TOKEN type)
{
	SYMBOL typeSym;		// symbol table entry for the type 
	typeSym = type->symType;
	// treat it as an alias
	copyAndInsert(alias->stringVal, typeSym);
}

// make a subrange type token. 
// not a subrange varible but the type. 
// low and high can be CONST NUMBER or CONST ID defined before 
// return a token, whose symType points to the symbol table entry of the subrange type. 
TOKEN makeSubrange(TOKEN low, TOKEN high)
{
	TOKEN rangeTok;		// this token only symType field is used.
	SYMBOL rangeSym;
	rangeTok = tokenAlloc();
	char name[16] = "";	// the name of this type is still not known, or may be there is no name
	rangeSym = insertsym(name, SYM_SUBRANGE);

	// CONST NUMBER
	if (low->tokenType == TYPE_DATA && high->tokenType == TYPE_DATA)
	{
		if (low->dataType == high->dataType)
		{
			int lowbound, highbound;
			rangeSym->basicType = low->dataType;	// e.g. 3..9 should be an integer between 3 and 9
			switch (low->dataType)
			{
			case DATA_INT:
				lowbound = low->intVal;
				highbound = high->intVal;
				break;
			case DATA_CHAR:
				lowbound = low->charVal;
				highbound = high->charVal;
				break;
			default:
				semanticError("wrong type for subrange boundary");
				return NULL;
				break;
			}
			if (lowbound <= highbound)
			{
				rangeSym->lowBound = lowbound;
				rangeSym->highBound = highbound;
			}
			else
			{
				char s[64] = "low boundary is larger than high boundary";
				semanticError(s);
				return NULL;
			}
		}
		else
		{
			char s[64] = "bondaries of subrange must be the same type";
			semanticError(s);
			return NULL;
		}

	}
	// id of const
	else if (low->tokenType == TYPE_ID && high->tokenType == TYPE_ID)
	{
		SYMBOL lowsym, highsym;
		lowsym = searchst(low->stringVal);		// look for ID in symbol table. they should be pre-defined const.
		highsym = searchst(high->stringVal);
		// if id are not in the symbol table, error:
		if (lowsym == NULL)
		{
			char s[64];
			sprintf(s, "%s is not defined.", low->stringVal);
			semanticError(s);
			return NULL;
		}
		if (highsym == NULL)
		{
			char s[64];
			sprintf(s, "%s is not defined.", high->stringVal);
			semanticError(s);
			return NULL;
		}
		// low id and high id are both found: 
		// check if they are const
		if (lowsym->kind == SYM_CONST && highsym->kind == SYM_CONST)
		{
			double lowbound, highbound;
			if (lowsym->basicType == highsym->basicType)
			{
				rangeSym->basicType = lowsym->basicType;
				switch (lowsym->basicType)
				{
				case DATA_CHAR:
					lowbound = lowsym->constval.charConst;
					highbound = highsym->constval.charConst;
					break;
				case DATA_INT:
					lowbound = lowsym->constval.intNum;
					highbound = highsym->constval.intNum;
					break;
				default:
					semanticError("wrong type for subrange boundary");
					return NULL;
					break;
				}
				if (lowbound <= highbound)
				{
					rangeSym->lowBound = lowbound;
					rangeSym->highBound = highbound;
				}
				else
				{
					char s[64] = "low boundary is larger than high boundary";
					semanticError(s);
					return NULL;
				}

			}
			else
			{
				char s[64] = "subrange boundaries should be the same type";
				semanticError(s);
				return NULL;
			}

		}
		else
		{
			char s[64] = "subrange boundaries should be const";
			semanticError(s);
			return NULL;
		}


	}
	else
	{
		char s[64] = "incorrect subrange definition, range has to be const";
		semanticError(s);
		return NULL;
	}
	rangeTok->symType = rangeSym;
	rangeTok->symEntry = rangeSym; 		// for a token of type, symType and symEntry are the same. 
	return rangeTok;
}

// make an enum type token. The symType filed in this token points to this enum type's symtbl entry. 
// elements is the head of the element id link. 
TOKEN makeEnum(TOKEN elements)
{
	TOKEN enumtok;
	SYMBOL enumsym;
	enumtok = tokenAlloc();			// the token to return 
	char enumname[16] = "";
	enumsym = insertsym(enumname, SYM_ENUM);		// the symbol entry of this enum type
	enumsym->basicType = DATA_INT;
	enumsym->size = basicsizes[DATA_INT - 1];
	TOKEN p;
	SYMBOL pre = enumsym;
	int i = 0;
	for (p = elements; p != NULL; p = p->next)
	{
		SYMBOL elementSym;
		// create symbol entry for element in enum list, as const 
		elementSym = insertsym(p->stringVal, SYM_CONST);
		elementSym->basicType = DATA_INT;	// actually is an const integer
		elementSym->dataType = enumsym; 	// dataType points the symbol table entry of the enum type
		elementSym->size = basicsizes[DATA_INT - 1];
		elementSym->constval.intNum = i;
		pre->members = elementSym;		// link the symbol entrys of elements together 
		pre = elementSym;
		i++;		// enum value increases 
	}
	enumtok->symType = enumsym;
	enumtok->symEntry = enumsym;
	return enumtok;
}

// make an array token
// range is the token of the subrange, and datatype is the type of the elements in the array
// return a newly created token, which symType points to the array type in symbol entry
TOKEN makeArray(TOKEN range, TOKEN datatype)
{
	TOKEN arraytok;
	SYMBOL rangeSym, typeSym, arraySym;
	char name[16] = "";		// still do not have a name
	// if datatype is null, it means the getType function cannot find this type in symbol table, return NULL
	if (datatype == NULL)
	{
		return NULL;
	}
	arraytok = tokenAlloc();		// new a token to repersent the type declaration
	arraySym = insertsym(name, SYM_ARRAY);		// new a symbol entry to store the type definition
	rangeSym = range->symType;	// fetch the symbol table entry of the subrange
	typeSym = datatype->symType;	// fetch the symbol table entry of the element's type
	if (rangeSym->kind == SYM_SUBRANGE)
	{
		int low, high;
		int subt;
		arraySym->basicType = typeSym->basicType;		// basic type of elements
		arraySym->dataType = typeSym->dataType;		// dataType field is not array, but the complicated type of elements
		subt = rangeSym->basicType;			// type of subs. should be DATA_CHAR or DATA_INT
		if (subt == DATA_INT || subt == DATA_CHAR)
		{
			arraySym->subtype = subt;
			low = rangeSym->lowBound;			// ascii of char or integer
			high = rangeSym->highBound;
			arraySym->size = (high - low + 1)*basicsizes[arraySym->basicType - 1];
			arraySym->lowBound = low;
			arraySym->highBound = high;
		}
		else
		{
			char s[64] = "incorrect array range";
			semanticError(s);
			return NULL;
		}
	}
	else
	{
		char s[64] = "incorrect array range";
		semanticError(s);
		return NULL;
	}
	arraytok->symType = arraySym;		// fill in the symbol entry field in array token. 
	arraytok->symEntry = arraySym;
	return arraytok;
}

// return a token, whose symType points to the symbol table entry of this type
TOKEN makeRecord(TOKEN fields)
{
	TOKEN rectok;
	SYMBOL recsym;
	rectok = tokenAlloc();
	char name[16] = "";
	recsym = insertsym(name, SYM_RECORD);
	int size = 0;
	TOKEN f;
	SYMBOL fieldSym, pre;
	pre = recsym;
	for (f = fields; f != NULL; f = f->next)
	{
		fieldSym = f->symType;
		size += fieldSym->size;
		pre->members = fieldSym;		// link all field's symbol entries after the record's entry as members
		pre = pre->members;
	}
	recsym->size = size;
	rectok->symEntry = recsym;
	rectok->symType = recsym;			// token's symType pointer points to the symbol table entry
	printf("debug: %d\n", curLevel);
	return rectok;
}

/* create symbol table entries for these fields.
 * different from var declaration because they need to be linked together in symbol tabel
 * varlist: token link		type: token of type
 */
TOKEN makeField(TOKEN varlist, TOKEN type)
{
	TOKEN v;
	SYMBOL typeSym;
	// type is NULL means the type_decl has errors
	if (type == NULL)
		return NULL;

	typeSym = type->symType;		// symbol talbe entry for type 
	SYMBOL fieldSym, pre;
	pre = NULL;
	for (v = varlist; v != NULL; v = v->next)
	{
		fieldSym = insertsym(v->stringVal, SYM_FIELD);
		fieldSym->basicType = typeSym->basicType;
		fieldSym->dataType = typeSym;
		fieldSym->size = typeSym->size;
		fieldSym->offset = blockoffs[curLevel];
		blockoffs[curLevel] += fieldSym->size;
		if (pre != NULL)
			pre->members = fieldSym;			// link fields in symbol table together
		pre = fieldSym;
		v->symType = fieldSym;		// fill in the symType in token v 
		v->symEntry = fieldSym;
	}
	return varlist;
}

// deal with record.field, find the Record member 
// return a token DOT->recordvar->field's offset, DOT's type is the field's  type
TOKEN makeRecordMember(TOKEN recordVar, TOKEN field)
{
	TOKEN dotToken;
	TOKEN offsetToken = NULL;
	SYMBOL recvarSym, rectypeSym;
	int offset = 0;
	dotToken = tokenAlloc();
	// find the record variable in the symbol table
	recvarSym = searchst(recordVar->stringVal);
	// if not found, recordVar is a not defined ID
	if (recvarSym == NULL)
	{
		char s[64];
		sprintf(s, "%s is not defined.", recordVar->stringVal);
		semanticError(s);
		return NULL;
	}
	rectypeSym = recvarSym->dataType;		// find the record type in symbol type 
	recordVar->symType = rectypeSym;
	recordVar->symEntry = recvarSym;
	SYMBOL s;
	for (s = rectypeSym->members; s != NULL; s = s->members)		// fields are linked together by symbol->members
	{
		if (strcmp(field->stringVal, s->nameString) == 0)
		{
			offsetToken = createConst(offset);
			dotToken->dataType = s->basicType;		// token->dataType is an int. what about complicated type?
			break;
		}
		else
		{
			offset += s->size;
		}
	}
	if (offsetToken == NULL)	// no name match the argument field->stringVal
	{
		char s[64];
		sprintf(s, "%s is not defined.", field->stringVal);
		semanticError(s);
		return NULL;
	}
	dotToken->operands = link(recordVar, offsetToken);
	dotToken->whichToken = OP_RECORDREF;
	dotToken->tokenType = TYPE_OPERATOR;
	return dotToken;
}

TOKEN endDecl(TOKEN decl)
{
	return decl;
}

/* makeFunDcl: make function declaration, link the body to head*/
TOKEN makeFunDcl(TOKEN head, TOKEN body)
{
	TOKEN fundcl_tok = tokenAlloc();
	fundcl_tok->tokenType = TYPE_OPERATOR;
	fundcl_tok->whichToken = OP_FUN_DCL;
	if (!fundcl_tok)
	{
		return NULL;
	}

	fundcl_tok->operands = head;
	if(head->operands != NULL)
		head->operands->next = body;
	else
		head = link(head,body);

	//curLevel = blocknumber;	// current block level, = last block
	//blockoffs[blocknumber] = 0;
	//blocknumber++;				// may be another function block
	//outLevel[blocknumber] = outLevel[curLevel];

	return fundcl_tok;
}

/* makeFunHead: make function head*/
TOKEN makeFunHead(TOKEN head, TOKEN name, TOKEN argtok, TOKEN retype)
{
	// for function
	if (strcmp(head->stringVal, "function") == 0)
	{
		if (retype == NULL)
		{
			semanticError("sorry, the TYPE is not supported! ");
			return NULL;
		}
		SYMBOL arglist;
		SYMBOL a;
		arglist = argtok->symEntry;
		a = arglist;
		while (argtok && argtok->next)
		{
			argtok = argtok->next;
			if (argtok->symEntry != NULL)
			{
				a->args = argtok->symEntry;
			}
			else
			{
				semanticError("Missing argument type.");
			}
			a = a->args;
		}

		insertfnx(name->stringVal, retype->symType, arglist);

		// insert "_funname" variable  (dyx: res is inserted in isertfnx, maybe problem:
		//TOKEN new_var = tokenAlloc();
		//int i;
		//new_var->stringVal[0] = '_';
		//for (i = 1; i < 16; i++)
		//{
		//	new_var->stringVal[i] = fun_name->stringVal[i - 1];
		//}
		//new_var->tokenType = TYPE_ID; // TOKEN_ID

		//regVar(new_var, getType(funtype_tok));
	}
	// for procedure
	else
	{
		SYMBOL arglist;
		SYMBOL a;
		arglist = argtok->symEntry;
		a = arglist;
		while (argtok)
		{
			argtok = argtok->next;
			if (argtok->symEntry != NULL)
			{
				a->args = argtok->symEntry;
			}
			else
			{
				semanticError("Missing argument type.");
			}
			a = a->args;
		}
		insertfnx(name->stringVal, NULL, arglist);
	}

	//TOKEN fun_block = createConst(blocknumber);
	//head->operands = link(fun_block, name);
	head->operands = name;
	return head;
}

void upLevel()
{
	blocknumber++;		// total number of blocks 
	outLevel[blocknumber] = curLevel;		// remember the out level 
	curLevel = blocknumber;		// up 
}

void downLevel()
{
	curLevel = outLevel[curLevel];
}
/* yy parse error*/
void yyerror(char* s)
{
	fprintf(stderr, "%s\n", yytext);
	fprintf(stderr, "Parser Error at line %d: %s\n", lineCount, s);
}

/* error prompt */
void semanticError(char* errorMessage)
{
	fprintf(stderr, "Error: Semantic error at line %d: %s\n", lineCount, errorMessage);
}

/* warning prompt*/
void semanticWarning(char* warningMessage)
{
	fprintf(stderr, "Warning: Semantic warning at line %d: %s\n", lineCount, warningMessage);
}
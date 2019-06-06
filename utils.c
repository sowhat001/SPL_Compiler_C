# include "utils.h"

TOKEN totalTree[10000] = { 0 };
int size = 0;
char *NUM_TO_NAME[500] = { 0 };
char *TYPE_NUM_TO_NAME[10] = { 0 };
char *DATA_NUM_TO_NAME[10] = { 0 };

void printTokenDetail(TOKEN token)
{
	switch (token->tokenType)
	{
	case TYPE_OPERATOR:
	case TYPE_DELIMITER:
	case TYPE_RESERVED:
	case TYPE_ID:
	{
		printf("tokenType: %-16s   whichToken: %-16s   dataType: %-16s   literalValue: %-16s", TYPE_NUM_TO_NAME[token->tokenType], NUM_TO_NAME[token->whichToken],DATA_NUM_TO_NAME[token->dataType], token->stringVal);
		break;
	}
	case TYPE_DATA:
	{
		switch (token->dataType)
		{
		case DATA_INT:
		{
			printf("tokenType: %-16s   whichToken: %-16s   dataType: %-16s   literalValue: %-16d", TYPE_NUM_TO_NAME[token->tokenType], NUM_TO_NAME[token->whichToken], DATA_NUM_TO_NAME[token->dataType], token->intVal);
			break;
		}
		case DATA_CHAR:
		{
			printf("tokenType: %-16s   whichToken: %-16s   dataType: %-16s   literalValue: %-16c", TYPE_NUM_TO_NAME[token->tokenType], NUM_TO_NAME[token->whichToken], DATA_NUM_TO_NAME[token->dataType], token->charVal);
			break;
		}
		case DATA_REAL:
		{
			printf("tokenType: %-16s   whichToken: %-16s   dataType: %-16s   literalValue: %-16lf", TYPE_NUM_TO_NAME[token->tokenType], NUM_TO_NAME[token->whichToken], DATA_NUM_TO_NAME[token->dataType], token->realVal);
			break;
		}
		case DATA_STRING:
		{
			printf("tokenType: %-16s   whichToken: %-16s   dataType: %-16s   literalValue: %-16s", TYPE_NUM_TO_NAME[token->tokenType], NUM_TO_NAME[token->whichToken], DATA_NUM_TO_NAME[token->dataType], token->stringVal);
			break;
		}
		default:
			break;
		}
	}
	default:
		break;
	}
}

void printTokenOnlyName(TOKEN token)
{
	switch (token->tokenType)
	{
	case TYPE_OPERATOR:
	case TYPE_DELIMITER:
	case TYPE_RESERVED:
	case TYPE_ID:
	{
		if (token->stringVal[0] == 0)
		{
			printf("%s", NUM_TO_NAME[token->whichToken]);
		}
		else
		{
			printf("%s", token->stringVal);
		}
		break;
	}
	case TYPE_DATA:
	{
		switch (token->dataType)
		{
		case DATA_INT:
		{
			printf("%d", token->intVal);
			break;
		}
		case DATA_CHAR:
		{
			printf("%c", token->charVal);
			break;
		}
		case DATA_REAL:
		{
			printf("%lf", token->realVal);
			break;
		}
		case DATA_STRING:
		{
			printf("%s", token->stringVal);
			break;
		}
		default:
			break;
		}
	}
	default:
		break;
	}
}

TOKEN tokenAlloc()
{
	TOKEN token;
	if ((token = (TOKEN)calloc(1, sizeof(struct _token))))
	{
		token->tokenType = 0;
		token->whichToken = 0;
		token->dataType = 0;
		token->symType = NULL;
		token->symEntry = NULL;
		token->operands = NULL;
		token->next = NULL;
		return token;
	}

	else
	{
		printf("token malloc failed.\n");
		return NULL;
	}
}

TOKEN copyToken(TOKEN copy)
{
	TOKEN empty = tokenAlloc();
	empty->tokenType = copy->tokenType;
	empty->dataType = copy->dataType;
	empty->whichToken = copy->whichToken;
	empty->tokenVal = copy->tokenVal;
	empty->next = NULL;
	empty->symEntry = NULL;
	empty->symType = NULL;
	empty->operands = NULL;
	return empty;
}

void printTree(TOKEN token, int level)
{
	if (token == NULL)
	{
		printf ("ERROR: NULL TOKEN.\n");
	}
	else
	{
		if (token->operands != NULL)
		{
			for (int i = 0; i < level; i++)
			{
				if (i == level - 1)
				{
					printf("©À  ");
				}
				else
				{
					printf("  ");
				}
			}
			printTokenOnlyName(token);
			printf("\n");
			TOKEN temp = token->operands;
			while (temp != NULL)
			{
				printTree(temp, level + 1);
				temp = temp->next;
			}
		}
		else
		{
			for (int i = 0; i < level; i++)
			{
				if (i == level - 1)
				{
					printf("©À  ");
				}
				else
				{
					printf("  ");
				}
			}
			printTokenOnlyName(token);
			printf("\n");
		}
	}
}

void initPrint()
{
	TYPE_NUM_TO_NAME[TYPE_OPERATOR] = "TYPE_OPERATOR";
	TYPE_NUM_TO_NAME[TYPE_DELIMITER] = "TYPE_DELIMITER";
	TYPE_NUM_TO_NAME[TYPE_RESERVED] = "TYPE_RESERVED";
	TYPE_NUM_TO_NAME[TYPE_ID] = "TYPE_ID";
	TYPE_NUM_TO_NAME[TYPE_DATA] = "TYPE_DATA";

	DATA_NUM_TO_NAME[DATA_INT] = "DATA_INT";
	DATA_NUM_TO_NAME[DATA_REAL] = "DATA_REAL";
	DATA_NUM_TO_NAME[DATA_CHAR] = "DATA_CHAR";
	DATA_NUM_TO_NAME[DATA_STRING] = "DATA_STRING";

	NUM_TO_NAME[OP_INT_TO_REAL] = "OP_INT_TO_REAL";
	NUM_TO_NAME[OP_REAL_TO_INT] = "OP_REAL_TO_INT";
	NUM_TO_NAME[OP_STRING_TO_CHAR] = "OP_STRING_TO_CHAR";
	NUM_TO_NAME[OP_FUNCALL] = "OP_FUNCALL";
	NUM_TO_NAME[OP_LABEL] = "OP_LABEL";
	NUM_TO_NAME[OP_GOTO] = "OP_GOTO";
	NUM_TO_NAME[OP_PROGN] = "OP_PROGN";
	NUM_TO_NAME[OP_ARRAYREF] = "OP_ARRAYREF";
	NUM_TO_NAME[OP_RECORDREF] = "OP_RECORDREF";

	NUM_TO_NAME[ID] = "ID";
	NUM_TO_NAME[INTEGER] = "INTEGER";
	NUM_TO_NAME[REAL] = "REAL";
	NUM_TO_NAME[CHAR] = "CHAR";
	NUM_TO_NAME[STRING] = "STRING";
	NUM_TO_NAME[LP] = "LP";
	NUM_TO_NAME[RP] = "RP";
	NUM_TO_NAME[LB] = "LB";
	NUM_TO_NAME[RB] = "RB";
	NUM_TO_NAME[DOTDOT] = "DOTDOT";
	NUM_TO_NAME[COMMA] = "COMMA";
	NUM_TO_NAME[COLON] = "COLON";
	NUM_TO_NAME[SEMI] = "SEMI";
	NUM_TO_NAME[DOT] = "DOT";
	NUM_TO_NAME[PLUS] = "PLUS";
	NUM_TO_NAME[MINUS] = "MINUS";
	NUM_TO_NAME[MUL] = "MUL";
	NUM_TO_NAME[LT] = "LT";
	NUM_TO_NAME[LE] = "LE";
	NUM_TO_NAME[EQ] = "EQ";
	NUM_TO_NAME[NE] = "NE";
	NUM_TO_NAME[GT] = "GT";
	NUM_TO_NAME[GE] = "GE";
	NUM_TO_NAME[ASSIGN] = "ASSIGN";
	NUM_TO_NAME[AND] = "AND";
	NUM_TO_NAME[OR] = "OR";
	NUM_TO_NAME[NOT] = "NOT";
	NUM_TO_NAME[REAL_DIV] = "REAL_DIV";
	NUM_TO_NAME[DIV] = "DIV";
	NUM_TO_NAME[MOD] = "MOD";
	NUM_TO_NAME[ARRAY] = "ARRAY";
	NUM_TO_NAME[BEGIN_] = "BEGIN_";
	NUM_TO_NAME[CASE] = "CASE";
	NUM_TO_NAME[CONST] = "CONST";
	NUM_TO_NAME[DO] = "DO";
	NUM_TO_NAME[DOWNTO] = "DOWNTO";
	NUM_TO_NAME[ELSE] = "ELSE";
	NUM_TO_NAME[END] = "END";
	NUM_TO_NAME[FOR] = "FOR";
	NUM_TO_NAME[FUNCTION] = "FUNCTION";
	NUM_TO_NAME[GOTO] = "GOTO";
	NUM_TO_NAME[IF] = "IF";
	NUM_TO_NAME[OF] = "OF";
	NUM_TO_NAME[PROCEDURE] = "PROCEDURE";
	NUM_TO_NAME[PROGRAM] = "PROGRAM";
	NUM_TO_NAME[READ] = "READ";
	NUM_TO_NAME[RECORD] = "RECORD";
	NUM_TO_NAME[REPEAT] = "REPEAT";
	NUM_TO_NAME[THEN] = "THEN";
	NUM_TO_NAME[TO] = "TO";
	NUM_TO_NAME[TYPE] = "TYPE";
	NUM_TO_NAME[UNTIL] = "UNTIL";
	NUM_TO_NAME[VAR] = "VAR";
	NUM_TO_NAME[WHILE] = "WHILE";
	NUM_TO_NAME[SYS_CON] = "SYS_CON";
	NUM_TO_NAME[SYS_FUNCT] = "SYS_FUNCT";
	NUM_TO_NAME[SYS_PROC] = "SYS_PROC";
	NUM_TO_NAME[SYS_TYPE] = "SYS_TYPE";
}

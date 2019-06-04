# include "utils.h"

void printTokenDetail(TOKEN token)
{
	switch (token->tokenType)
	{
	case TYPE_OPERATOR:
	case TYPE_DELIMITER:
	case TYPE_RESERVED:
	case TYPE_ID:
	{
		printf("%d   %4d   %d   %16s", token->tokenType, token->whichToken, token->dataType, token->stringVal);
		break;
	}
	case TYPE_DATA:
	{
		switch (token->dataType)
		{
		case DATA_INT:
		{
			printf("%d   %4d   %d   %16d", token->tokenType, token->whichToken, token->dataType, token->intVal);
			break;
		}
		case DATA_CHAR:
		{
			printf("%d   %4d   %d   %16c", token->tokenType, token->whichToken, token->dataType, token->charVal);
			break;
		}
		case DATA_REAL:
		{
			printf("%d   %4d   %d   %16lf", token->tokenType, token->whichToken, token->dataType, token->realVal);
			break;
		}
		case DATA_STRING:
		{
			printf("%d   %4d   %d   %16s", token->tokenType, token->whichToken, token->dataType, token->stringVal);
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
		printf("%16s", token->stringVal);
		break;
	}
	case TYPE_DATA:
	{
		switch (token->dataType)
		{
		case DATA_INT:
		{
			printf("%16d", token->intVal);
			break;
		}
		case DATA_CHAR:
		{
			printf("%16c", token->charVal);
			break;
		}
		case DATA_REAL:
		{
			printf("%16lf", token->realVal);
			break;
		}
		case DATA_STRING:
		{
			printf("%16s", token->stringVal);
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
		//Initialize
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
	// empty->next = copy->next;
	// empty->symEntry = copy->symEntry;
	// empty->symType = copy->symType;
	// empty->operands = copy->operands;
	empty->whichToken = copy->whichToken;
	empty->tokenVal = copy->tokenVal;
	empty->next = NULL;
	empty->symEntry = NULL;
	empty->symType = NULL;
	empty->operands = NULL;
	return empty;
}

void printTree(TOKEN token)
{
	TOKEN totalTree[10000] = {0};
	int size = 0;
	int endIndex = 0;
	int beginIndex = 0;
	int nextLevel = 0;
	int nowLevel = 0;
	if (token == NULL)
	{
		printf ("ERROR: NULL TOKEN.\n");
	}
	else
	{
		totalTree[endIndex++] = token;
		size++;
		nowLevel++;
		while (size != 0)
		{
			TOKEN temp = totalTree[beginIndex];
			totalTree[beginIndex++] = 0;
			size--;
			printTokenOnlyName(temp);
			nowLevel--;
			if (nowLevel == 0)
			{
				printf ("\n\n");
			}
			TOKEN t = temp->operands;
			while (t != NULL)
			{
				totalTree[endIndex++] = t;
				t = t->next;
				size++;
				nextLevel++;
			}
			nowLevel = nextLevel;
			nextLevel = 0;
		}
	}
}

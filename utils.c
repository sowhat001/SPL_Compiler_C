# include "utils.h"

TOKEN totalTree[10000] = { 0 };
int parent[10000] = { 0 };
int size = 0;

void printTokenDetail(TOKEN token)
{
	switch (token->tokenType)
	{
	case TYPE_OPERATOR:
	case TYPE_DELIMITER:
	case TYPE_RESERVED:
	case TYPE_ID:
	{
		printf("tokenType: %d   whichToken: %-4d   dataType: %d   literalValue: %-16s", token->tokenType, token->whichToken, token->dataType, token->stringVal);
		break;
	}
	case TYPE_DATA:
	{
		switch (token->dataType)
		{
		case DATA_INT:
		{
			printf("tokenType: %d   whichToken: %-4d   dataType: %d   literalValue: %-16d", token->tokenType, token->whichToken, token->dataType, token->intVal);
			break;
		}
		case DATA_CHAR:
		{
			printf("tokenType: %d   whichToken: %-4d   dataType: %d   literalValue: %-16c", token->tokenType, token->whichToken, token->dataType, token->charVal);
			break;
		}
		case DATA_REAL:
		{
			printf("tokenType: %d   whichToken: %-4d   dataType: %d   literalValue: %-16lf", token->tokenType, token->whichToken, token->dataType, token->realVal);
			break;
		}
		case DATA_STRING:
		{
			printf("tokenType: %d   whichToken: %-4d   dataType: %d   literalValue: %-16s", token->tokenType, token->whichToken, token->dataType, token->stringVal);
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

void printTokenOnlyName(TOKEN token, int index)
{
	switch (token->tokenType)
	{
	case TYPE_OPERATOR:
	case TYPE_DELIMITER:
	case TYPE_RESERVED:
	case TYPE_ID:
	{
		printf("%4d: literalValue: %-16s parent: %d", index, token->stringVal, parent[index]);
		break;
	}
	case TYPE_DATA:
	{
		switch (token->dataType)
		{
		case DATA_INT:
		{
			printf("%4d: literalValue: %-16d parent: %d", index, token->intVal, parent[index]);
			break;
		}
		case DATA_CHAR:
		{
			printf("%4d: literalValue: %-16c parent: %d", index, token->charVal, parent[index]);
			break;
		}
		case DATA_REAL:
		{
			printf("%4d: literalValue: %-16lf parent: %d", index, token->realVal, parent[index]);
			break;
		}
		case DATA_STRING:
		{
			printf("%4d: literalValue: %-16s parent: %d", index, token->stringVal, parent[index]);
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
	if (token == NULL)
	{
		printf ("ERROR: NULL TOKEN.\n");
	}
	else
	{
		totalTree[size++] = token;
		int index = 0;
		TOKEN now = totalTree[index];
		while (now != NULL)
		{
			printTokenOnlyName(now, index);
			printf("\n");
			TOKEN temp = now->operands;
			while (temp != NULL)
			{
				totalTree[size] = temp;
				parent[size++] = index;
				temp = temp->next;
			}
			now = totalTree[++index];
		}
	}
}

/**********************************************************
 *  File:     symtab.c
 *  Project:  SPL-compiler
 *  Author:   Execution
 *  Modified: Jun 3, 2017
 **********************************************************/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include "token.h"

#pragma warning(disable:4996)

 // TOKENNODE user_labels = NULL;
 // TOKENNODE curr_label = NULL;

 /* BASEOFFSET is the offset for the first variable */
#define BASEOFFSET 0

int	curLevel = 0;			/* current block level */
int	blocknumber = 0;       	/* Totle number of blocks */
int outLevel[MAXBLOCKS] = { 0 };	/* out layer */
int blockoffs[MAXBLOCKS] = { 0 };  		/* Storage offsets for each block */
SYMBOL symtb[MAXBLOCKS][HASH_SIZE] = { NULL };     /* Symbol table for each block */

/* Sizes of basic types  INTEGER  REAL    	BOOL      CHAR    	 STRING   */
int basicsizes[5] = { 4,       8,       4,         1,        16 };

char* symprint[10] = { "ARGM", "BASIC", "CONST", "VAR", "SYM_SUBRANGE",
					   "FUNCTION", "ARRAY", "RECORD", "TYPE", "ARGLIST" };
int symsize[10] = { 1, 5, 5, 3, 8, 8, 5, 6, 4, 7 };

/* allocate a new symbol record */
SYMBOL symalloc()
{
	return((SYMBOL)malloc(sizeof(struct symtbr)));
}

/* Make a symbol table entry with the given name */
SYMBOL makesym(char name[], int kind)
{
	SYMBOL sym;
	int i;
	sym = symalloc();
	for (i = 0; i < 16; i++)
		sym->nameString[i] = name[i];
	sym->next = NULL;
	sym->kind = kind;
	sym->basicType = -1;
	sym->dataType = NULL;
	sym->args = NULL;
	sym->members = NULL;
	sym->subtype = 0;
	return sym;
}

/* Insert a name in the symbol table at current value of blocknumber */
/* Returns pointer to the new symbol table entry, which is empty     */
/* except for the name.                                              */
SYMBOL insertsym(char name[], int kind)
{
	return insertsymat(name, kind, curLevel);
}
SYMBOL insertsymat(char name[], int kind, int level)
{
	SYMBOL sym;
	sym = makesym(name, kind);
	sym->nestLevel = level;
	int pos = hash_f(name);
	if (symtb[level][pos] == NULL)
	{
		symtb[level][pos] = sym;
	}
	else
	{
		/* insert at the head of this record */
		sym->next = symtb[level][pos];
		symtb[level][pos] = sym;
	}
	return sym;
}

int hash_f(char name[])
{
	int ans = 0;
	// hi = alpha * hi-1 + ci 
	for (unsigned int i = 0; i < strlen(name); i++)
	{
		ans = (ans << HASH_SHIFT) + (name[i] - '0');
	}
	ans = ans % HASH_SIZE;
	return ans;
}

// 05.26 new copy and insert function:
SYMBOL copyAndInsert(char name[], SYMBOL source)
{
	SYMBOL newsym;
	newsym = insertsym(name, source->kind);		// only nest level may be different, set in this call 
	newsym->basicType = source->basicType;
	newsym->dataType = source->dataType;
	newsym->size = source->size;
	newsym->offset = source->offset;
	newsym->constval = source->constval;		// can union directly assign? 
	newsym->args = source->args;
	newsym->members = source->members;
	return newsym;
}

/* Search one level of the symbol table for the given name.         */
/* Result is a pointer to the symbol table entry or NULL            */
SYMBOL searchlev(char name[], int level)
{
	int pos = hash_f(name);
	SYMBOL sym = NULL;
	sym = symtb[level][pos];

	while (sym != NULL)
	{
		// only the same level needs to be checked 
		if (sym->nestLevel == level)
		{
			if (strcmp(name, sym->nameString) == 0)
				break;
		}
		sym = sym->next;
	}
	return sym;		/* pointer to the symbol struct or NULL */
}

/* Search all levels of the symbol table for the given name.        */
/* Result is a pointer to the symbol table entry or NULL            */
SYMBOL searchst(char name[])
{
	SYMBOL sym = NULL;
	int level = curLevel;
	// problem 
	while (sym == NULL && level >= 0)
	{
		sym = searchlev(name, level);
		if (level > 0)
			level = outLevel[curLevel]; 	/* try outer level */
		else level = -1;                      /* until all are tried  */
	}
	// printf("searchst %8s %ld at level %d\n",name, (long)sym, level);
	return sym;
}

/* Get the alignment boundary for a type  */
int alignsize(SYMBOL sym)
{
	int asize = 0;
	switch (sym->kind)
	{
	case SYM_BASIC:
		asize = sym->size;
		break;
	case SYM_SUBRANGE:
		asize = sym->size;
		break;
	case SYM_ARRAY:
		asize = sym->size;
		break;
	case SYM_RECORD:
		return 16;
		break;
	default:
		return 8; 	// ????
		break;
	}
	return asize;
}

/* Insert a basic type into the symbol table, use for init system symbol tabel */
SYMBOL insertbt(char name[], int basictp, int size)
{
	SYMBOL sym = insertsym(name, SYM_BASIC);
	sym->basicType = basictp;
	sym->dataType = NULL;
	sym->size = size;
	return sym;
}

/* Insert a one-argument function in the symbol table. Used in initsyms */
SYMBOL insertfn(char name[], SYMBOL resulttp, SYMBOL argtp)
{
	SYMBOL fsym, arg;
	char fname[16];
	fname[0] = '_';
	strcpy(fname + 1, name);
	fsym = insertsym(fname, SYM_FUNCTION);

	arg = insertsym(name, SYM_ARGM);	// argument 
	if (argtp != NULL)
	{
		arg->basicType = argtp->basicType;
		if (argtp->kind = SYM_BASIC)
			arg->dataType = NULL;
		else
			arg->dataType = argtp->dataType;
	}
	fsym->args = arg;

	if (resulttp != NULL)
	{
		fsym->basicType = resulttp->basicType;
		if (resulttp->kind == SYM_BASIC)
			fsym->dataType = NULL;
		else
			fsym->dataType = resulttp;
	}
	return fsym;
}

// insert function with argument list
// result variable has the same name with the function 
SYMBOL insertfnx(char name[], SYMBOL resulttp, SYMBOL arglist)
{
	SYMBOL fsym, res;
	char funcname[16];
	funcname[0] = '_';		// name in the function's symbol table is '_name' to differ from the return variable
	strcpy(funcname + 1, name);
	fsym = insertsym(funcname, SYM_FUNCTION);
	blocknumber++;
	outLevel[blocknumber] = curLevel;
	curLevel = blocknumber;		// change the level 
	res = insertsym(name, SYM_VAR);
	if (resulttp != NULL)
	{
		fsym->basicType = resulttp->basicType;
		if (resulttp->kind == SYM_BASIC)
			fsym->dataType = NULL;
		else
			fsym->dataType = resulttp;
	}
	// link the result and arglist to fsym->args
	fsym->args = res;
	res->args = arglist;
	return fsym;
}

/* Call this to initialize symbols provided by the compiler */
void initsyms()
{
	SYMBOL realsym, intsym, charsym, boolsym;
	blocknumber = 0;               /* Put compiler symbols in block 0 */
	blockoffs[0] = BASEOFFSET;     /* offset of first variable */
	realsym=insertbt("real", DATA_REAL, 8);
	intsym=insertbt("integer", DATA_INT, 4);
	charsym=insertbt("char", DATA_CHAR, 1);
	boolsym=insertbt("boolean", DATA_INT, 4);

	insertfn("abs", realsym, realsym);
	insertfn("sqr", realsym, realsym);
	insertfn("sqrt", realsym, realsym);
	insertfn("ord", intsym, intsym);
	insertfn("chr", charsym, intsym);
	insertfn("pred", charsym, charsym);
	insertfn("succ", charsym, charsym);
	insertfn("odd", boolsym, intsym);

	insertfn("write", NULL, charsym);
	insertfn("writeln", NULL, charsym);
	insertfn("read", NULL, NULL);
	insertfn("readln", NULL, NULL);

	blocknumber = 1;             /* Start the user program in block 1 */
	curLevel = 1;
	outLevel[1] = 0;
}

// Following: Not know what for: 
// int user_label_exists(TOKEN label_tok) {
// 	if (label_tok->intVal < 0) {
// 		printf("Warning: searching for user label with negative value (%d)\n", label_tok->intval);
// 	}

// 	int exists = get_internal_label_num(label_tok->intVal);
// 	if (exists == -1) {
// 		return 0;
// 	}
// 	return 1;
// }

// // do NOT return ->token for reuse, otherwise the label can only be goto'd once
// int get_internal_label_num(int external_label_num) {
// 	if (external_label_num < 0) {
// 		printf("Error: cannot find negative label number %d\n", external_label_num);
// 		return -1;
// 	}
// 	else {
// 		TOKENNODE temp = user_labels;
// 		while (temp) {
// 			if (temp->token->intval == external_label_num) {
// 				return (temp->internal_label_num);
// 			}
// 			temp = temp->next;
// 		}
// 		return -1;
// 	}
// }
// void insert_label(int internal_label_num, TOKEN label_tok) {
// 	if (label_tok->intval < 0) {
// 		// ??? should be allowed
// 	}
// 	else if (internal_label_num < 0) {
// 		// ???
// 	}
// 	else if (user_label_exists(label_tok)) {
// 		return;
// 	}	// check to see if label num already exists?
// 	else {
// //		dbugprinttok(label_tok);
// 		if (!user_labels) {
// 			user_labels = malloc(sizeof(struct toknode));
// 			user_labels->internal_label_num = internal_label_num;
// 			user_labels->token = label_tok;
// 			user_labels->next = NULL;
// 			curr_label = user_labels;
// 		}
// 		else {
// 			TOKENNODE curr = malloc(sizeof(struct toknode));
// 			curr->internal_label_num = internal_label_num;
// 			curr->token = label_tok;
// 			curr->next = NULL;
// 			curr_label->next = curr;
// 			curr_label = curr;
// 		}
// 	}
// }

// for debug :
/* Print one symbol table entry for debugging      */
void dbprsymbol(SYMBOL sym)
{
	if (sym != NULL)
		printf(" %ld  %10s knd %1d %1d  typ %ld lvl %1d  siz %5d  off %5d lnk %ld\n",
		(long)sym, sym->nameString, sym->kind, sym->basicType, (long)sym->dataType,
			sym->nestLevel, sym->size, sym->offset, (long)sym->next);
}
/* print type expression in prefix form */
void pprintsym(SYMBOL sym, int col)
{
	SYMBOL opnds; int nextcol, start, done, i;
	if (sym == NULL)
	{
		printf("pprintsym: called with sym = NULL\n");
		return;
	}
	if (PPSYMDEBUG != 0)
	{
		printf("pprintsym: col %d\n", col);
		dbprsymbol(sym);
	}
	switch (sym->kind)
	{
	case SYM_BASIC:
		printf("%s", sym->nameString);
		nextcol = col + 1 + strlen(sym->nameString);
		break;
	case SYM_SUBRANGE:
		printf("%3lf ..%4lf", sym->lowBound, sym->highBound);
		nextcol = col + 10;
		break;

	case SYM_FUNCTION:
	case SYM_ARRAY:
	case SYM_RECORD:
		printf("(%s", symprint[sym->kind]);
		nextcol = col + 2 + symsize[sym->kind];
		if (sym->kind == SYM_ARRAY)
		{
			printf(" %3lf ..%4lf", sym->lowBound, sym->highBound);
			nextcol = nextcol + 11;
		}
		opnds = sym->dataType;
		start = 0;
		done = 0;
		while (opnds != NULL && done == 0)
		{
			if (start == 0) printf(" ");
			else
			{
				printf("\n");
				for (i = 0; i < nextcol; i++) printf(" ");
			}
			if (sym->kind == SYM_RECORD)
			{
				printf("(%s ", opnds->nameString);
				pprintsym(opnds, nextcol + 2 + strlen(opnds->nameString));
				printf(")");
			}
			else pprintsym(opnds, nextcol);
			start = 1;
			if (sym->kind == SYM_ARRAY) done = 1;
			opnds = opnds->next;
		}
		printf(")");
		break;
	default:
		if (sym->dataType != NULL) pprintsym(sym->dataType, col);
		else printf("NULL");
		break;
	}
}
/* print a type expression in prefix form */
void ppsym(SYMBOL sym)
{
	pprintsym(sym, 0);
	printf("\n");
}

/* Print one symbol table entry       */
void printsymbol(SYMBOL sym)
{
	if (sym == NULL)
	{
		printf("printsymbol: called with sym = NULL\n");
		return;
	}
	switch (sym->kind)
	{
	case SYM_FUNCTION:
	case SYM_ARRAY:
	case SYM_RECORD:
		printf(" %ld  %10s  knd %1d %1d  typ %ld  lvl %2d  siz %5d  off %5d\n",
			(long)sym, sym->nameString, sym->kind, sym->basicType, (long)sym->dataType,
			sym->nestLevel, sym->size, sym->offset);
		ppsym(sym);
		break;
	case SYM_VAR:
		if (sym->dataType == NULL)
		{
			printf(" %ld  %10s  VAR    %1d typ    NULL  lvl %2d  siz %5d  off %5d\n",
				(long)sym, sym->nameString, sym->basicType, sym->nestLevel, sym->size, sym->offset);
		}
		else if (sym->dataType->kind == SYM_BASIC)
			printf(" %ld  %10s  VAR    %1d typ %7s  lvl %2d  siz %5d  off %5d\n",
			(long)sym, sym->nameString, sym->basicType, sym->dataType->nameString,
				sym->nestLevel, sym->size, sym->offset);
		else
		{
			printf(" %ld  %10s  VAR    %1d typ %ld  lvl %2d  siz %5d  off %5d\n",
				(long)sym, sym->nameString, sym->basicType, (long)sym->dataType,
				sym->nestLevel, sym->size, sym->offset);
			ppsym(sym->dataType);
		}
		break;
	case SYM_TYPE:
		printf(" %ld  %10s  TYPE   typ %ld  lvl %2d  siz %5d  off %5d\n",
			(long)sym, sym->nameString, (long)sym->dataType,
			sym->nestLevel, sym->size, sym->offset);
		if (sym->dataType->kind != SYM_BASIC) ppsym(sym->dataType);
		break;
	case SYM_BASIC:
		printf(" %ld  %10s  BASIC  basicType %3d          siz %5d\n",
			(long)sym, sym->nameString, sym->basicType, sym->size);
		break;
	case SYM_SUBRANGE:
		printf(" %ld  %10s  SUBRA  typ %7d  val %5lf .. %5lf\n",
			(long)sym, sym->nameString, sym->basicType, sym->lowBound, sym->highBound);
		break;
	case SYM_CONST:
		switch (sym->basicType)
		{
		case DATA_INT:
			printf(" %ld  %10s  CONST  typ INTEGER  val  %d\n",
				(long)sym, sym->nameString, sym->constval.intNum);
			break;
		case DATA_REAL:
			printf(" %ld  %10s  CONST  typ    REAL  val  %12e\n",
				(long)sym, sym->nameString, sym->constval.realNum);
			break;
		case DATA_STRING:
			printf(" %ld  %10s  CONST  typ  STRING  val  %12s\n",
				(long)sym, sym->nameString, sym->constval.stringConst);
			break;
		case DATA_CHAR:
			printf(" %ld  %10s  CONST  typ  STRING  val  %c\n",
				(long)sym, sym->nameString, sym->constval.charConst);
			break;
		}
		break;
	};
}

/* Print entries on one level of symbol table */
void printstlevel(int level)
{
	printf("Symbol table level %d\n", level);
	int i;
	for (i = 0; i < HASH_SIZE; i++)
	{
		printf("%2d: ", i);
		if (symtb[level][i] != NULL) printsymbol(symtb[level][i]);
		else printf("NULL\n");
	}
}

/* Print all entries in the symbol table */
void printst()
{
	int level;
	for (level = 0; level <= blocknumber; level++)
		printstlevel(level);
}

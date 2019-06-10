/**********************************************************
 *	File:		symtab.h
 *	Project:	SPL-compiler
 *	Author:		Execution
 *	Modified:	Jun 6, 2017
 **********************************************************/

#ifndef SYMTAB_H
#define SYMTAB_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

 /* Define kinds of symbols.  The kind field should be one of these. */
#define SYM_ARGVAR		0		// 引用传递参数
#define SYM_BASIC		1
#define SYM_CONST		2
#define SYM_VAR			3
#define SYM_SUBRANGE	4
#define SYM_FUNCTION	5
#define SYM_ARRAY		6   
#define SYM_RECORD		7
#define SYM_TYPE		8
#define SYM_POINTER		9
#define SYM_ARGLIST		10		// 值传递参数
#define SYM_ENUM		11
#define SYM_FIELD		12 		

#define PPSYMDEBUG 0

#define MAXBLOCKS 50          /* Max number of program blocks           */

/* struct of one symbol table record */
typedef struct symtbr
{
	struct symtbr *next; 		/* point to the next token with the same hash value */
	char   nameString[16];		/* name */
	int    kind;                /* kind of symbol -- see defines. */
	// if function:  type is return type, as well as the type of function name in function. 
	int    basicType;             /* type code for basic data types       */
	struct symtbr *dataType;    /* pointer for more complex data types  */
	int    nestLevel;			/* nest level */
	int    size;
	int    offset;
	union
	{
		char  stringConst[16];
		int   intNum;			// also store boolean value
		double realNum;
		char charConst;
	} constval;
	int    lowBound;			// for array 
	int    highBound;
	// for function: the first argument, for an argument: the next argument
	struct symtbr *args;
	// for enum or record, list of members
	struct symbtr *members;
	// type of array subs. can only be DATA_CHAR or DATA_INT
	int subtype;
	// only valied for SYM_FUNCTION symbol, remembers the level of the function's block. 
	int flevel;
} *SYMBOL;

/* symalloc makes a new symbol table record and returns a pointer to it.
   Essentially     new Symbol()   */
SYMBOL symalloc(void);

/* makesym makes a new symbol table record and puts a name into it.
   Use makesym e.g. for record field names. */
SYMBOL makesym(char name[], int kind);

/* insertsym makes a new symbol table record, puts a name into it,
   and puts it into the symbol table.
   Use insertsym e.g. for variables and type names. */
SYMBOL insertsym(char name[], int kind);

SYMBOL searchlev(char name[], int level);

/* search the symbol table for the given name.
   Returns a pointer to the symbol table entry if found. */
SYMBOL searchst(char name[]);

/* Print one symbol table entry for debugging      */
void dbprsymbol(SYMBOL sym);

void pprintsym(SYMBOL sym, int col);

/* pretty-print a type in the symbol table */
void ppsym(SYMBOL sym);

/* Print one symbol table entry       */
void printsymbol(SYMBOL sym);

/* Print entries on one level of symbol table */
void printstlevel(int level);

/* Print all entries in the symbol table */
void printst(void);

SYMBOL insertbt(char name[], int basictp, int siz);
SYMBOL insertfn(char name[], SYMBOL resulttp, SYMBOL argtp);
void initsyms(void);    /* initializes pre-defined symbols */
SYMBOL insertfnx(char name[], SYMBOL resulttp, SYMBOL arglist);
SYMBOL insertsymat(char name[], int kind, int level);


/* alignsize returns the required alignment boundary for a type  */
int alignsize(SYMBOL sym);

#define DEBUG_SYMTAB 0

// int user_label_exists(TOKEN label_tok);
// int get_internal_label_num(int external_label_num);
// void insert_label(int internal_label_num, TOKEN label_tok);

#define HASH_SIZE 31	// prime 
#define HASH_SHIFT 3 	// alpha is 8 = 2^3, shift 3 bits
int hash_f(char name[]);

// 05.26 new
// copy a symbol with new name and insert into symbol table
SYMBOL copyAndInsert(char name[], SYMBOL source);

#endif	/* SYMTAB_H */
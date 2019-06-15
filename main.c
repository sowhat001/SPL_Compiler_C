#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "token.h"
#include "symtab.h"
#include "utils.h"

extern int lineCount;
extern int curLevel;					/* current block level */
extern int blocknumber;       			/* Totle number of blocks */
extern int outLevel[MAXBLOCKS];			/* out layer */
extern int blockoffs[MAXBLOCKS];  		/* Storage offsets for each block */
extern int basicsizes[5];
extern int lineCount;					/* line count */
extern TOKEN parseResult;
extern TOKEN yylval;
extern int labelNumber;

int yylex(void);

int main()
{
	printf(";BEGIN\n");
	initPrint();
	initsyms();
	yyparse();
	//printst();
	//printTree(parseResult, 0);
	curLevel = 1;
	genCode(parseResult, blockoffs[curLevel], labelNumber - 1);
	while (1);
	return 0;
}
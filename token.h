#ifndef TOKEN_H
#define TOKEN_H

/* token data structure */
typedef struct _token
{
	int tokenType;
	int whichToken;
	int dataType;
	struct symtbr *symType;
	struct symtbr *symEntry;
	struct _token *operands;
	struct _token *next;
	union tokenVal
	{
		char stringVal[16];
		int intVal;
		char charVal;
		double realVal;
	} tokenVal;
} *TOKEN;

#define intVal    	tokenVal.intVal
#define realVal   	tokenVal.realVal
#define stringVal 	tokenVal.stringVal
#define charVal 	tokenVal.charVal

//token types
#define TYPE_OPERATOR	1
#define TYPE_DELIMITER	2
#define TYPE_RESERVED	3
#define TYPE_ID			4
#define TYPE_DATA		5

//data types
#define DATA_INT		1
#define DATA_REAL		2
#define DATA_BOOL		3
#define DATA_CHAR		4
#define DATA_STRING		5

//tokens
#define OP_INT_TO_REAL		1
#define OP_REAL_TO_INT		2
#define OP_STRING_TO_CHAR	3
#define OP_FUNCALL			4
#define OP_LABEL			5
#define OP_GOTO				6
#define OP_PROGN			7

#define ID				258
#define INTEGER			259
#define REAL			260
#define CHAR			261
#define STRING			262
#define LP				263
#define RP				264
#define LB				265
#define RB				266
#define DOTDOT			267
#define COMMA			268
#define COLON			269
#define SEMI			270
#define DOT				271
#define PLUS			272
#define MINUS			273
#define MUL				274
#define LT				275
#define LE				276
#define EQ				277
#define NE				278
#define GT				279
#define GE				280
#define ASSIGN			281
#define AND				282
#define OR				283
#define NOT				284
#define REAL_DIV		285
#define DIV				286
#define MOD				287
#define ARRAY			288
#define BEGIN_			289
#define CASE			290
#define CONST			291
#define DO				292
#define DOWNTO			293
#define ELSE			294
#define END				295
#define FOR				296
#define FUNCTION		297
#define GOTO			298
#define IF				299
#define OF				300
#define PROCEDURE		301
#define PROGRAM			302
#define READ			303
#define RECORD			304
#define REPEAT			305
#define THEN			306
#define TO				307
#define TYPE			308
#define UNTIL			309
#define VAR				310
#define WHILE			311
#define SYS_CON			312
#define SYS_FUNCT		313
#define SYS_PROC		314
#define SYS_TYPE		315

#ifndef YYTOKENTYPE
#define YYTOKENTYPE 0
#endif

#endif	/* TOKEN_H */


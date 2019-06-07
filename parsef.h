#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "token.h"
#include "symtab.h"
#include "utils.h"

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
TOKEN arrayRef(TOKEN arrayToken, TOKEN refExp);

/* Create a token with const int value. Used in for loop (i = i + 1), array and record(offset) */
TOKEN createConst(int constInt);

/* Create a token with labelNum. Used in loop. Jump */
TOKEN createGoto(TOKEN labelToken);

/* Create a label. This function will use the system default lableNum and add itself, because it is anonymous label in loop parse, not the user's define label */
TOKEN createLabel();

/* A ID token. check this token in symbol table.
symType and symEntry are changed.
dataType will be changed if it is a const token. */
TOKEN findId(TOKEN token);

/* Link list and newItem */
TOKEN link(TOKEN list, TOKEN newItem);

/* Make the assign expression like a := 2
op's dataType is changed */
TOKEN makeAssign(TOKEN op, TOKEN leftValue, TOKEN rightValue);

/* make a begin statement with BEGIN sign or other sign. beginToken's type is changed to OP_PROGN. */
TOKEN makeBeginStmt(TOKEN beginToken, TOKEN stmt);

/* make a binary operation expression include calculating and comparing like a + b or a > b
op's dataType is changed */
TOKEN makeBinOp(TOKEN op, TOKEN leftOperand, TOKEN rightOperand);

/* switch case */
TOKEN makeCase(TOKEN caseToken, TOKEN judgeExp, TOKEN choices);

/* For loop. */
TOKEN makeFor(TOKEN forToken, TOKEN initAssign, TOKEN direction, TOKEN finalAssign, TOKEN beginToken, TOKEN loopStmt);

/* A function call. get its arguments and check it is avaliable function name or not.
funcName's tokenType, whichToken, dataType are changed. dataType is return value's type
???是不是还要检查一下是不是和声明的参数一样
*/
TOKEN makeFuncall(TOKEN lpToken, TOKEN funcName, TOKEN arguments);

/* goto Token with user's given number */
TOKEN makeGoto(TOKEN intToken);

/* if Token */
TOKEN makeIf(TOKEN ifToken, TOKEN expression, TOKEN thenStmt, TOKEN elseStmt);

/* label token with user's given number */
TOKEN makeLabel(TOKEN labelNum, TOKEN stmt);

/* program make */
TOKEN makeProgram(TOKEN NameToken, TOKEN routine);

/* repeat loop */
TOKEN makeRepeat(TOKEN repeatToken, TOKEN stmt, TOKEN untilToken, TOKEN expression);

/* make a signal case. Used in makeCase*/
TOKEN makeSignalCase(TOKEN judgeResult, TOKEN stmt);

/* unary op
op's dataType is changed. */
TOKEN makeUnaryOp(TOKEN op, TOKEN operand);

/* while loop */
TOKEN makeWhile(TOKEN whileToken, TOKEN expression, TOKEN doToken, TOKEN stmt);

// token id's symType field is filled in with a newly created symbol table entry
void regConst(TOKEN id, TOKEN constok);

// put new variables into symbol table
// e.g.: a,b,c : integer   create symbol table entry for a,b,c
void regVar(TOKEN varlist, TOKEN type);

// get the type in symbol table by the string in a token, fill it in the symType of the token
TOKEN getType(TOKEN typetok);

// put a type definition into symbol table 
/* new sym->name = alias->string, for definition like type haha=integer
 * type->sym->name = alias->string, for definition like type haha=array[2..9] of integer
 * complicated, can ask dyx.
 */
void regType(TOKEN alias, TOKEN type);

// make a subrange type token. 
// not a subrange varible but the type. 
// low and high can be CONST NUMBER or CONST ID defined before 
// return a token, whose symType points to the symbol table entry of the subrange type. 
TOKEN makeSubrange(TOKEN low, TOKEN high);

// make an enum type token. The symType filed in this token points to this enum type's symtbl entry. 
// elements is the head of the element id link. 
TOKEN makeEnum(TOKEN elements);

// make an array token
// range is the token of the subrange, and datatype is the type of the elements in the array
// return a newly created token, which symType points to the array type in symbol entry
TOKEN makeArray(TOKEN range, TOKEN datatype);

// return a token, whose symType points to the symbol table entry of this type
TOKEN makeRecord(TOKEN fields);

/* create symbol table entries for these fields.
 * different from var declaration because they need to be linked together in symbol tabel
 * varlist: token link		type: token of type
 */
TOKEN makeField(TOKEN varlist, TOKEN type);

// deal with record.field, find the Record member 
// return a token DOT->recordvar->field's offset, DOT's type is the field's  type
TOKEN makeRecordMember(TOKEN recordVar, TOKEN field);

TOKEN endDecl(TOKEN decl);

/* makeFunDcl: make function declaration, link the body to head*/
TOKEN makeFunDcl(TOKEN head, TOKEN body);

/* makeFunHead: make function head*/
TOKEN makeFunHead(TOKEN head);

/* yy parse error*/
void yyerror(char* s);

/* error prompt */
void semanticError(char* errorMessage);

/* warning prompt*/
void semanticWarning(char* warningMessage);
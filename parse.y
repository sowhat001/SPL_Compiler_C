%{
	#pragma warning(disable:4996)
	#define YYSTYPE TOKEN
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

	TOKEN parseResult;
%}

//order can not be changed
//data types
%token ID INTEGER REAL CHAR STRING
//delimiters
%token LP RP LB RB DOTDOT COMMA COLON SEMI
//operator
%token DOT PLUS MINUS MUL LT LE EQ NE GT GE ASSIGN
%token AND OR NOT DIV REAL_DIV MOD 
//reserved
%token ARRAY BEGIN_ CASE CONST DO DOWNTO ELSE END FOR FUNCTION GOTO
//IN PACKED SET
%token IF OF PROCEDURE PROGRAM READ RECORD REPEAT THEN
//WITH
%token TO TYPE UNTIL VAR WHILE
%token SYS_CON SYS_FUNCT SYS_PROC SYS_TYPE

%%
program				: program_head routine DOT								{ parseResult = makeProgram($1, $2); }
					;
program_head		: PROGRAM ID SEMI										{ $$ = $2; }
					;
routine				: routine_head routine_body								{ $$ = link($1, $2); }
					;
sub_routine			: routine_head routine_body								{ $$ = link($1, $2); }
					;
routine_head		: label_part const_part type_part var_part routine_part	{ $$ = endDecl($5); }
					;
label_part			: 	
					;
// const part 
const_part			: CONST const_expr_list 								{ $$ = NULL;}
					| 
					;
const_expr_list		: const_expr_list ID EQ const_value SEMI				{ regConst($2, $4); }
					| ID EQ const_value SEMI								{ regConst($1, $3); }
					;
const_value			: INTEGER												{ $$ = $1; }
					| REAL													{ $$ = $1; }
					| CHAR													{ $$ = $1; }
					| STRING												{ $$ = $1; }
					| SYS_CON												{ $$ = $1; }			// return the const token
					;
// type define part 
type_part			: TYPE type_decl_list									{ $$ = NULL; }
					| 
					;
type_decl_list		: type_decl_list type_definition 						{ $$ = NULL; }
					| type_definition										{ $$ = NULL; }
					;
type_definition		: ID EQ type_decl SEMI									{ regType($1, $3); }
					;
type_decl			: simple_type_decl										{ $$ = $1; }
					| array_type_decl										{ $$ = $1; }
					| record_type_decl										{ $$ = $1; }
					;
simple_type_decl	: SYS_TYPE 												{ $$ = getType($1); }	// integer, real ....					
					| ID													{ $$ = getType($1); } 	
					| LP id_list RP											{ $$ = makeEnum($2); }	// enum 
					| const_value DOTDOT const_value						{ $$ = makeSubrange($1, $3); }	// subrange
					| ID DOTDOT ID											{ $$ = makeSubrange($1, $3); }
					;

array_type_decl		: ARRAY LB simple_type_decl RB OF type_decl				{ $$ = makeArray($3, $6); }
					;
record_type_decl	: RECORD field_decl_list END							{ $$ = makeRecord($2); }
					;
field_decl_list		: field_decl_list field_decl							{ $$ = link($1,$2); }
					| field_decl											{ $$ = $1; }
					;
field_decl			: id_list COLON type_decl SEMI							{ $$ = makeField($1, $3); }
					;
id_list				: id_list COMMA ID 										{ $$ = link($1, $3);  } // link ID to the name list
					| ID													{ $$ = $1; }
					;
// var part
var_part			: VAR var_decl_list 									{ $$ = NULL; }
					| 														{ $$ = NULL; }
					;
var_decl_list		: var_decl_list var_decl 								{ $$ = NULL; }			
					| var_decl												{ $$ = NULL; }
					;
var_decl			: id_list COLON type_decl SEMI							{ regVar($1, $3, 2);	 } // register vars in $1 as $3 type
					;
// routine part (w)
routine_part		: routine_part function_decl  							{ $$ = link($1, $2); }
					| routine_part procedure_decl							{ $$ = link($1, $2); }
					| function_decl 										{ $$ = $1; }
					| procedure_decl										{ $$ = $1; }
					| /* empty */											{ $$ = NULL; }
					;
function_decl		: function_head SEMI sub_routine SEMI 					{ $$ = makeFunDcl($1, $3);}
					;
function_head		: FUNCTION { upLevel(); } ID parameters COLON simple_type_decl			{ $$ = makeFunHead($1, $3, $4, $6); } // FUNCTION, ID, para, type
					;
procedure_decl		: procedure_head SEMI sub_routine SEMI 					{ $$ = makeFunDcl($1, $4); }
					;
procedure_head		: PROCEDURE { upLevel(); } ID parameters 				{ $$ = makeFunHead($1, $2, $3, NULL);}	// PROCEDURE, ID, para 
					;
parameters			: LP para_decl_list RP  								{ $$ = $2; }
					|  /*empty*/											{ $$ = NULL; }
					;
para_decl_list		: para_decl_list SEMI para_type_list 					{ $$ = link($1, $3); }
					| para_type_list  										{ $$ = $1; }
					;
para_type_list		: var_para_list COLON simple_type_decl 					{ $$ = $1; regVar($1, $3, 1); }
					| val_para_list COLON simple_type_decl  				{ $$ = $1; regVar($1, $3, 0); }
					;
var_para_list		: VAR id_list											{ $$ = $2; }
					;
val_para_list		: id_list												{ $$ = $1; }
					;
//(w)		
routine_body		: compound_stmt											{ $$ = $1; }
					;
compound_stmt		: BEGIN_ stmt_list END									{ $$ = makeBeginStmt($1, $2); }
					;
stmt_list			: stmt_list stmt SEMI									{ $$ = link($1, $2); }
					| 														{ $$ = NULL; }
					;
stmt				: INTEGER COLON non_label_stmt							{ $$ = makeLabel($1, $3); }
					| non_label_stmt										{ $$ = $1; }
					;
non_label_stmt		: assign_stmt											{ $$ = $1; }
					| proc_stmt												{ $$ = $1; }
					| compound_stmt											{ $$ = $1; }
					| if_stmt												{ $$ = $1; }
					| repeat_stmt											{ $$ = $1; }
					| while_stmt											{ $$ = $1; }
					| for_stmt												{ $$ = $1; }
					| case_stmt												{ $$ = $1; }
					| goto_stmt												{ $$ = $1; }
					;
assign_stmt			: ID ASSIGN expression									{ $$ = makeAssign($2, findId($1), $3); }
					| ID LB expression RB ASSIGN expression					{ $$ = makeAssign($5, arrayRef($1, $3), $6); }
					| ID DOT ID ASSIGN expression							{ $$ = makeAssign($4, makeRecordMember($1, $3), $5); }
					;
proc_stmt			: ID													{ $$ = makeFuncall($1, NULL, NULL); }
					| ID LP args_list RP									{ $$ = makeFuncall($2, $1, $3); }
					| SYS_PROC												{ $$ = NULL; }
					| SYS_PROC LP expression_list RP						{ $$ = makeFuncall($2, $1, $3); }
					| READ LP factor RP										{ $$ = makeFuncall($2, $1, $3); }
					;
if_stmt				: IF expression THEN stmt else_clause					{ $$ = makeIf($1, $2, $4, $5); }
					;
else_clause			: ELSE stmt												{ $$ = $2; }
					| 
					;
repeat_stmt			: REPEAT stmt_list UNTIL expression						{ $$ = makeRepeat($1, $2, $3, $4); }
					;
while_stmt			: WHILE expression DO stmt								{ $$ = makeWhile($1, $2, $3, $4); }
					;
for_stmt			: FOR ID ASSIGN expression direction expression DO stmt	{ $$ = makeFor($1, makeAssign($3, findId($2), $4), $5, $6, $7, $8); }
					;
direction			: TO													{ $$ = $1; }
					| DOWNTO												{ $$ = $1; }
					;
case_stmt			: CASE expression OF case_expr_list END					{ $$ = makeCase($1, $2, $4); }
					;
case_expr_list		: case_expr_list case_expr								{ $$ = link($1, $2); }
					| case_expr												{ $$ = $1; }
					;
case_expr			: const_value COLON stmt SEMI							{ $$ = makeSignalCase($1, $3); }
					| ID COLON stmt SEMI									{ $$ = makeSignalCase(findId($1), $3); }
					;
goto_stmt			: GOTO INTEGER											{ $$ = makeGoto($2); }
					;
expression_list		: expression_list COMMA expression						{ $$ = link($1, $2); }
					| expression											{ $$ = $1; }
					;
expression			: expression GE expr									{ $$ = makeBinOp($2, $1, $3); }
					| expression GT expr									{ $$ = makeBinOp($2, $1, $3); }
					| expression LE expr									{ $$ = makeBinOp($2, $1, $3); }
					| expression LT expr									{ $$ = makeBinOp($2, $1, $3); }
					| expression EQ expr									{ $$ = makeBinOp($2, $1, $3); }
					| expression NE expr									{ $$ = makeBinOp($2, $1, $3); }
					| expr													{ $$ = $1; }
					;
expr				: expr PLUS term										{ $$ = makeBinOp($2, $1, $3); }
					| expr MINUS term										{ $$ = makeBinOp($2, $1, $3); }
					| expr OR term											{ $$ = makeBinOp($2, $1, $3); }
					| term													{ $$ = $1; }
					;
term				: term MUL factor										{ $$ = makeBinOp($2, $1, $3); }
					| term DIV factor										{ $$ = makeBinOp($2, $1, $3); }
					| term REAL_DIV factor									{ $$ = makeBinOp($2, $1, $3); }
					| term MOD factor										{ $$ = makeBinOp($2, $1, $3); }
					| term AND factor										{ $$ = makeBinOp($2, $1, $3); }
					| factor												{ $$ = $1; }
					;
factor				: ID													{ $$ = findId($1); }
					| ID LP args_list RP									{ $$ = makeFuncall($2, $1, $3); }								
					| SYS_FUNCT												{ $$ = NULL; }
					| SYS_FUNCT LP args_list RP								{ $$ = makeFuncall($2, $1, $3); }
					| const_value											{ $$ = $1; }
					| LP expression RP										{ $$ = $2; }
					| NOT factor											{ $$ = makeUnaryOp($1, $2); }
					| MINUS factor											{ $$ = makeUnaryOp($1, $2); }
					| ID LB expression RB									{ $$ = arrayRef($1, $3); }
					| ID DOT ID												{ $$ = makeRecordMember($1, $3); }
					;
args_list			: args_list COMMA expression							{ $$ = link($1, $3); }
					| expression											{ $$ = $1; }
%%

%{
#define YYSTYPE TOKEN
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

extern TOKEN yylval;

/* read comment1, like {} and {* *} */
void readComments();

/* make a token, update tokenType, whichiToken and dataType if this is a data token */
int makeToken(int tokenType, int whichToken);

/* make a id token */
int instId();

/* make a const real token */
int instReal();

/* make a const int token */
int instInt();

/* make a const string token */
int instStr();

int yywrap();
void lexError();

#undef YYLMAX
/* a token's literal value is no longer than 256 characters */
#define YYLMAX 256

/* line count, when an error or warning is reported, it is used */
int lineCount = 1;
%}

delim		[ \t]
ws			{delim}+
letter		[A-Za-z]
digit		[0-9]
id			{letter}(_|{letter}|{digit})*
integer		[+-]?{digit}+
real		[+-]?{digit}+(\.{digit}+)?(([E|e])[+\-]?{digit}+)?
string		\'.*\'
comment1	\{
comment2	\/\/.*\n
A [Aa]
B [Bb]
C [Cc]
D [Dd]
E [Ee]
F [Ff]
G [Gg]
H [Hh]
I [Ii]
J [Jj]
K [Kk]
L [Ll]
M [Mm]
N [Nn]
O [Oo]
P [Pp]
Q [Qq]
R [Rr]
S [Ss]
T [Tt]
U [Uu]
V [Vv]
W [Ww]
X [Xx]
Y [Yy]
Z [Zz]

%%

{ws}		{ }
{comment1}	{ readComments(); }
{comment2}	{ lineCount++; }
"\n"		{ lineCount++; }

"("			{ return makeToken(TYPE_DELIMITER, LP); }
")"			{ return makeToken(TYPE_DELIMITER, RP); }
"["			{ return makeToken(TYPE_DELIMITER, LB); }
"]"			{ return makeToken(TYPE_DELIMITER, RB); }
".."		{ return makeToken(TYPE_DELIMITER, DOTDOT); }
","			{ return makeToken(TYPE_DELIMITER, COMMA); }
":"			{ return makeToken(TYPE_DELIMITER, COLON); }
";"			{ return makeToken(TYPE_DELIMITER, SEMI); }

"."			{ return makeToken(TYPE_OPERATOR, DOT); }
"+"			{ return makeToken(TYPE_OPERATOR, PLUS); }
"-"			{ return makeToken(TYPE_OPERATOR, MINUS); }
"*"			{ return makeToken(TYPE_OPERATOR, MUL); }
"/"			{ return makeToken(TYPE_OPERATOR, REAL_DIV); }
"<"			{ return makeToken(TYPE_OPERATOR, LT); }
"<="		{ return makeToken(TYPE_OPERATOR, LE); }
"="			{ return makeToken(TYPE_OPERATOR, EQ); }
"<>"		{ return makeToken(TYPE_OPERATOR, NE); }
">"			{ return makeToken(TYPE_OPERATOR, GT); }
">="		{ return makeToken(TYPE_OPERATOR, GE); }
":="		{ return makeToken(TYPE_OPERATOR, ASSIGN); }
{A}{N}{D}			{ return makeToken(TYPE_OPERATOR, AND); }
{O}{R}				{ return makeToken(TYPE_OPERATOR, OR); }
{N}{O}{T}			{ return makeToken(TYPE_OPERATOR, NOT); }
{D}{I}{V}			{ return makeToken(TYPE_OPERATOR, DIV); }
{M}{O}{D}			{ return makeToken(TYPE_OPERATOR, MOD); }

{A}{R}{R}{A}{Y}				{ return makeToken(TYPE_RESERVED, ARRAY); }
{B}{E}{G}{I}{N}				{ return makeToken(TYPE_RESERVED, BEGIN_); }
{C}{A}{S}{E}				{ return makeToken(TYPE_RESERVED, CASE); }
{C}{O}{N}{S}{T}				{ return makeToken(TYPE_RESERVED, CONST); }
{D}{O}						{ return makeToken(TYPE_RESERVED, DO); }
{D}{O}{W}{N}{T}{O}			{ return makeToken(TYPE_RESERVED, DOWNTO); }
{E}{L}{S}{E}				{ return makeToken(TYPE_RESERVED, ELSE); }
{E}{N}{D}					{ return makeToken(TYPE_RESERVED, END); }
{F}{O}{R}					{ return makeToken(TYPE_RESERVED, FOR); }
{F}{U}{N}{C}{T}{I}{O}{N}	{ return makeToken(TYPE_RESERVED, FUNCTION); }
{G}{O}{T}{O}				{ return makeToken(TYPE_RESERVED, GOTO); }
{I}{F}						{ return makeToken(TYPE_RESERVED, IF); }
{O}{F}						{ return makeToken(TYPE_RESERVED, OF); }
{P}{R}{O}{C}{E}{D}{U}{R}{E}	{ return makeToken(TYPE_RESERVED, PROCEDURE);}
{P}{R}{O}{G}{R}{A}{M}		{ return makeToken(TYPE_RESERVED, PROGRAM); }
{R}{E}{A}{D}				{ return makeToken(TYPE_RESERVED, READ); }
{R}{E}{C}{O}{R}{D}			{ return makeToken(TYPE_RESERVED, RECORD); }
{R}{E}{P}{E}{A}{T}			{ return makeToken(TYPE_RESERVED, REPEAT); }
{T}{H}{E}{N}				{ return makeToken(TYPE_RESERVED, THEN); }
{T}{O}						{ return makeToken(TYPE_RESERVED, TO); }
{T}{Y}{P}{E}				{ return makeToken(TYPE_RESERVED, TYPE); }
{U}{N}{T}{I}{L}				{ return makeToken(TYPE_RESERVED, UNTIL); }
{V}{A}{R}					{ return makeToken(TYPE_RESERVED, VAR); }
{W}{H}{I}{L}{E}				{ return makeToken(TYPE_RESERVED, WHILE); }

true|false|maxint { return makeToken(TYPE_RESERVED, SYS_CON); }
abs|chr|odd|ord|pred|sqr|sqrt|succ { return makeToken(TYPE_RESERVED, SYS_FUNCT); }
write|writeln { return makeToken(TYPE_RESERVED, SYS_PROC); }
integer|boolean|char|real|string { return makeToken(TYPE_RESERVED, SYS_TYPE); }

{string}	{ return instStr(); }
{integer}	{ return instInt(); }
{real}		{ return instReal(); }
{id}		{ return instId(); }

.			{ lexError(); }

%%

/* read comment1, like {} and {* *} */
void readComments()
{
	char c;
	while ((c = input()) != '}') 
	{
		if (c == '\n') lineCount++;
	}
}

/* make a token, update tokenType, whichiToken and dataType if this is a data token */
/* a token's literal value is stored in token->stringVal */
/* true and false is int type, with value 1 and 0 */
int makeToken(int tokenType, int whichToken)
{
	yylval = tokenAlloc();
	yylval->tokenType = tokenType;
	yylval->whichToken = whichToken;
	for (int i = 0; i < yyleng; i++)
	{
		yylval->stringVal[i] = tolower(yytext[i]);
	}
	yylval->stringVal[yyleng] = 0;

	if (whichToken == SYS_CON)
	{
		yylval->tokenType = TYPE_DATA;
		yylval->dataType = DATA_INT;
		if (strcmp(yytext, "maxint") == 0)
		{
			yylval->intVal = INT_MAX;
		}
		else if (strcmp(yytext, "true") == 0)
		{
			yylval->intVal = 1;
		}
		else if (strcmp(yytext, "false") == 0)
		{
			yylval->intVal = 0;
		}
	}
	return whichToken;
}

/* make a id token */
int instId()
{
	yylval = tokenAlloc();
	yylval->whichToken = ID;
	yylval->tokenType = TYPE_ID;
	// printf ("from id: %s\n", yytext);
	int totalLength = (yyleng > MAX_STR_LENGTH ? MAX_STR_LENGTH : yyleng);
	for (int i = 0; i < totalLength; i++) 
	{
		yylval->stringVal[i] = yytext[i];
	}
	yylval->stringVal[totalLength] = 0;

	return ID;
}

/* make a const real token */
int instReal()
{
	yylval = tokenAlloc();
	yylval->whichToken = REAL;
	yylval->tokenType = TYPE_DATA;
	yylval->dataType = DATA_REAL;
	
	double num;
	sscanf(yytext, "%lf", &num);
	yylval->realVal = num;
	return REAL;
}

/* make a const int token */
int instInt()
{
	yylval = tokenAlloc();
	yylval->whichToken = INTEGER;
	yylval->tokenType = TYPE_DATA;
	yylval->dataType = DATA_INT;
	
	int num;
	sscanf(yytext, "%d", &num);
	yylval->intVal = num;
	return INTEGER;
}

/* make a const string token */
int instStr()
{
	yylval = tokenAlloc();
	yylval->tokenType = TYPE_DATA;
	// printf ("from string: %s\n", yytext);
	int totalLength = (yyleng > (MAX_STR_LENGTH + 2) ? MAX_STR_LENGTH : yyleng - 2); //
	// printf ("from string: totalLength %d\n", totalLength);
	if (totalLength == 1)
	{
		yylval->whichToken = CHAR;
		yylval->charVal = yytext[1];
		yylval->dataType = DATA_CHAR;
		return CHAR;
	}
	else
	{
		yylval->whichToken = STRING;
		for (int i = 0; i < totalLength; i++)
		{
			// printf ("%c ", yytext[i + 1]);
			yylval->stringVal[i] = yytext[i + 1];
		}
		yylval->stringVal[totalLength] = 0;
		yylval->dataType = DATA_STRING;
		return STRING;
	}
}

void lexError() 
{
	printf("Lexical Analysis Error at line %d\n", lineCount);
}

int yywrap() 
{  
	return 1;  
} 

#ifndef UTILS_H
#define UTILS_H

# include "token.h"
# include <stdio.h>
# include <ctype.h>
# include <stdlib.h>
# include <string.h>

#define MAX_STR_LENGTH 15
#define DOUBLE_MAX 1.7976931348623157e+308
#define DOUBLE_MIN 2.2250738585072014e-308
#define FLOAT_MAX 3.40282347e+38F
#define FLOAT_MIN 1.17549435e-38F

#define INT_MAX 2147483647
#define INT_MIN -2147483648

/* print a detail token*/
void printTokenDetail(TOKEN token);

/* print a token only name*/
void printTokenOnlyName(TOKEN token);

/* create a new empty token */
TOKEN tokenAlloc();

/* Copy token, only value, not pointer */ 
TOKEN copyToken(TOKEN copy);

/* Level order print syntax tree */
void printTree(TOKEN token, int level);

/* init Print */
void initPrint();

#endif

#ifndef UTILS_H
#define UTILS_H

# include "token.h"
# include <stdio.h>
# include <ctype.h>
# include <stdlib.h>
# include <string.h>

#define MAX_STR_LENGTH 15
#define INT_MAX 2147483647

/* print a detail token*/
void printTokenDetail(TOKEN token);

/* print a token only name*/
void printTokenOnlyName(TOKEN token, int index);

/* create a new empty token */
TOKEN tokenAlloc();

/* Copy token, only value, not pointer */ 
TOKEN copyToken(TOKEN copy);

/* Level order print syntax tree */
void printTree(TOKEN token);

#endif

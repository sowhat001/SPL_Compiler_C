#include <stdio.h>
#include <ctype.h>
#include "token.h"
#include "symtab.h"
#include "genasm.h"

/* Print strings for registers */
char* regpr[] = { "eax", "ebx", "ecx", "edx",
				 "esi", "edi", "esp", "ebp",
				 "r8d", "r9d", "r10d", "r11d",
				 "r12d", "r13d", "r14d", "r15d",
				 "%xmm0",  "%xmm1",   "%xmm2",  "%xmm3",
				 "%xmm4",  "%xmm5",  "%xmm6",  "%xmm7",
				 "%xmm8",  "%xmm9",  "%xmm10", "%xmm11",
				 "%xmm12", "%xmm13", "%xmm14", "%xmm15" };

/* Print strings for 64-bit versions of registers */
char* dregpr[] = { "rax", "rbx", "rcx", "rdx",
				  "rsi", "rdi", "rsp", "rbp",
				  "r8", "r9", "r10", "r11",
				  "r12", "r13", "r14", "r15" };

/* Define jump op codes */

char* jumppr[] = { "jmp", "jne", "je", "jge", "jl", "jg", "jle" };

/* Define jump comments */

char* jumpcompr[] = { "", "if     !=", "if     ==", "if     >=", "if     <",
					  "if     >", "if     <=" };

/* Define op codes for other instructions */

char* instpr[] =
/*   0        1       2       3      4       5      6        7  */
{ "mov", "movsd", "movq", "cltq", "add", "sub", "mul", "div",
/*   8     9     10       11     12     13       14      15  */
  "and", "neg", "or", "not", "cmp", "addsd", "subsd", "mulsd",
	/*   16       17      18      19      */
	  "divsd", "negsd", "cmpq", "cmpsd",
	/*   20      21       22      23      24      25     26     27	*/
	   "addq", "subq", "imulq", "andq", "negq", "orq", "notq", "lea"
};

/*                    0     1      2       3        4    5    6    7  */
char* instcompr[] = { "->", "->",  "->", "sign-extend", "+", "-", "*", "/",
/*                     8     9     10     11     12        13   14   15  */
					 " and", "-", "or", "notl", "compare", "+", "-", "*",
	/*                     16    17      18      19      */
						 "/", "-", "compare", "compare",
	/*   20      21       22      23      24      25     26     */
		"+",     "-",     "*",    "&",   "negq", "orq", "notq" };
char* toparseResult[] = {
  "; ---------------------- Beginning of Generated Code --------------------",
  "" };

/* Tables of literal constants */

static int   stackframesize;  /* size of stack frame variables */

/* Print a section of canned code.  Quits on an empty string.  */
void directPrint(char* lines[])
{
	int i;
	i = 0;
	while (lines[i][0] != 0)
	{
		printf("%s\n", lines[i]); 
		i++;
	}
}

/* Round up n to be a multiple of m */
int roundup(int n, int m)
{
	int ans;
	ans = n + m - 1;
	ans = ans / m;
	ans = ans * m;
	return ans;
}

/* Make entry code for a program. */
/* name is entry name, size is size of local storage on stack frame. */
/* returns actual stack frame size */
int asmentry(char name[], int size)
{
	/*     GCC requires stack aligned to 16-byte boundary */
	stackframesize = roundup(size, 16);
	directPrint(toparseResult);
	printf("extern writeln\n");			/* writeln realised by C */
	printf("global _start:\n");
	printf("_start:\n");
	printf("\tpush rbp\n");			/* create stack */
	printf("\tmov rbp, rsp\n");
	printf("\tsub rsp, %d\n", stackframesize);
	printf("\tmov rbx, r9\n");
	return stackframesize;
}

/* Make exit code for a program. 
 * call system call: exit 
 */
void asmexit(char name[])
{
	printf("mov ebx, 0\n");
	printf("mov eax, 1\n");
	printf("int 80h;exit\n");
}

/* Make a label */
void asmlabel(int labeln)
{
	printf("L%d:\n", labeln);
}
void asmlabelstr(char name[])
{
	printf("%s:\n", name);
}


/* Subroutine call */
/* Example:  asmcall(code->stringval);    Call function */
void asmcall(char name[])
{
	printf("\tcall\t%s              \t;  %s()\n", name, name);
}

/* Generate a jump instruction.  Example:  asmjump(JG, 17);   */
void asmjump(int code, int labeln)
{
	printf("\t%s\tL%d \t\t\t;  jump %s\n",
		jumppr[code], labeln, jumpcompr[code]);
}

/* Generate an immediate instruction: move an int to a register   */
/* Example:  asmimmed(MOVL, 3, EAX);   Moves 3 to EAX  */
/* Example:  asmimmed(ADDL, 1, EAX);   Adds 1 to EAX  */
void asmimmed(int inst, int ival, int reg)
{
	printf("\t%s\t%s,%d", instpr[inst], regpr[reg], ival);
	if (inst == MOV)
		printf("         \t;  %d -> %s\n", ival, regpr[reg]);
	else printf("         \t;  %s %s %d -> %s\n", regpr[reg], instcompr[inst], ival, regpr[reg]);
}

/* Generate a register to register instruction. 
 * op rs,rd     ADD  
 * Example:  asmrr(ADD, ECX, EAX);  EAX + ECX -> EAX  add EAX, ECX in intel
 */
void asmrr(int inst, int srcreg, int dstreg)
{
	printf("\t%s\t%s,%s", instpr[inst], regpr[dstreg], regpr[srcreg]);
	if (inst == CMP)
		printf("           \t;  compare %s - %s\n", regpr[srcreg], regpr[dstreg]);
	else if (inst == MOV)
		printf("         \t;  %s -> %s\n", regpr[srcreg], regpr[dstreg]);
	else printf("         \t;  %s %s %s -> %s\n",
		regpr[dstreg], instcompr[inst], regpr[srcreg], regpr[dstreg]);
}

void asmrr64(int inst, int srcreg, int dstreg)
{
	printf("\t%s\t%s,%s", instpr[inst], dregpr[dstreg], dregpr[srcreg]);
	if (inst == CMP)
		printf("           \t;  compare %s - %s\n", dregpr[dstreg], dregpr[srcreg]);
	else if (inst == MOV)
		printf("         \t;  %s -> %s\n", dregpr[srcreg], dregpr[dstreg]);
	else printf("         \t;  %s %s %s -> %s\n",
		dregpr[dstreg], instcompr[inst], dregpr[srcreg], dregpr[dstreg]);
}

/* Generate a load instruction relative to RBP: 
 * Example:  if code points to an integer variable,
 *	  asmld(MOV, -code->symentry->offset, 0, code->stringval);   
 */
void asmld(int inst, int off, int reg, char str[])
{
	if (off == 0)
		printf("\t%s\t%s, [rbp]", instpr[inst], regpr[reg]);
	else
		printf("\t%s\t%s, [rbp%d]", instpr[inst], regpr[reg], off);
	printf("     \t;  %s -> %s\n", str, regpr[reg]);
}

void asmld64(int inst, int off, int reg, char str[])
{
	if (off == 0)
		printf("\t%s\t%s, [rbp]", instpr[inst], dregpr[reg]);
	else
		printf("\t%s\t%s, [rbp%d]", instpr[inst], dregpr[reg], off);
	printf("     \t;  %s -> %s\n", str, dregpr[reg]);
}

/* Generate a store instruction relative to RBP: 
 * Example:  asmst(MOV, EAX, -code->symentry->offset, code->stringval);  
 */
void asmst(int inst, int reg, int off, char str[])
{
	printf("\t%s\t[rbp%d], %s ", instpr[inst], off, regpr[reg]);
	printf("     \t;  %s -> %s\n", regpr[reg], str);
}

/* store a 64bit val relative to RBP; */
void asmst64(int inst, int reg, int off, char str[])
{
	printf("\t%s\t[rbp%d], %s ", instpr[inst], off, dregpr[reg]);
	printf("     \t;  %s -> %s\n", dregpr[reg], str);
}

/* Generate a load instruction using offset and a register: */
/* Example:  asmldr(MOV, 0, RAX, ECX, code->stringval);  [rax] -> ecx  */
void asmldr(int inst, int offset, int reg, int dstreg )
{
	if (offset == 0)
		printf("\t%s\t%s, [%s]", instpr[inst], dregpr[dstreg], dregpr[reg]);
	else
		printf("\t%s\t%s, [%s%d]", instpr[inst], dregpr[dstreg], dregpr[reg], offset);
	printf("         \t;  [%d+%s] -> %s\n", offset, dregpr[reg], dregpr[dstreg]);
}

/* Generate a store instruction relative to a register: */
/* Example:  asmstr(MOVL, ECX, 4, RAX, code->stringval);  ecx -> [rax+4]  mov [rax+4], ecx*/
void asmstr(int inst, int srcreg, int offset, int reg)
{
	if (offset == 0)
		printf("\t%s\t[%s], %s", instpr[inst], dregpr[reg], regpr[srcreg]);
	else
		printf("\t%s\t[%s %d], %s", instpr[inst], dregpr[reg], offset, regpr[srcreg]);
	printf("         \t;  %s -> [ %s + %d]\n", dregpr[srcreg], dregpr[reg], offset );
}

/* instruction with one reg, e.g. mul, div 
 */
void asm1r(int inst, int reg)
{
	printf("\t%s\t%s\t\t", instpr[inst], regpr[reg]);
	if (inst == _DIV)
		printf("\t;  %s / %s -> %s\n", regpr[EAX], regpr[reg], regpr[EAX]);
	else
		printf("\t;  %s * %s -> %s\n", regpr[EAX], regpr[reg], regpr[EAX]);
}

/* push a reg into stack */
void asmpush(int reg)
{
	printf("\tpush\t%s\t\t", dregpr[reg]);
	printf("\t;  push  %s\n", dregpr[reg]);
}

/* pop value from stack into a reg */
void asmpop(int reg)
{
	printf("\tpop\t%s\t\t", dregpr[reg]);
	printf("\t;  pop  %s\n", dregpr[reg]);
}
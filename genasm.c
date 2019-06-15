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

static int   iliterals[100];  /* integer literals */
static int   ilabels[100];
static float fliterals[100];  /* floating literals */
static int   flabels[100];
static char  bliterals[1000]; /* byte literals */
static int   blindex[100];    /* index to byte literals */
static int   blabels[100];
static int   nilit = 0;
static int   nflit = 0;
static int   nblit = 0;
static int   floatconst = 0;  /* literal constant needed for floating */

static int   fnegused = 0;    /* constant for floating negation is used */

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
	printf("extern writeln\n");
	printf("global _start:\n");
	printf("_start:\n");
	printf("\tpush rbp\n");
	printf("\tmov rbp, rsp\n");
	printf("\tsub rsp, %d\n", stackframesize);
	printf("\tmov rbx, r9\n");
	return stackframesize;
}

/* Make exit code for a program. */
/* This is just canned code following calling conventions for target machine */
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

/* Get the right register name depending on instruction */
char* regnm(int reg, int instr)
{
	return (instr == MOVQ || instr == CMPQ) ? dregpr[reg] : regpr[reg];
}

/* Generate an immediate instruction: move an int to a register   */
/* Example:  asmimmed(MOVL, 3, EAX);   Moves 3 to EAX  */
/* Example:  asmimmed(ADDL, 1, EAX);   Adds 1 to EAX  */
void asmimmed(int inst, int ival, int reg)
{
	printf("\t%s\t%s,%d", instpr[inst], regnm(reg, inst), ival);
	if (inst == MOV || inst == MOVSD || inst == MOVQ)
		printf("         \t;  %d -> %s\n", ival, regnm(reg, inst));
	else printf("         \t;  %s %s %d -> %s\n",
		regnm(reg, inst), instcompr[inst], ival, regnm(reg, inst));
}

/* Generate an instruction with just the op. */
/* Example:  asmop(CLTQ) */
void asmop(int inst)
{
	printf("\t%s\t                  \t;  %s\n", instpr[inst], instcompr[inst]);
}

/* Generate a register to register instruction. */
/* op rs,rd     ADDL  */
/* Example:  asmrr(ADDL, ECX, EAX);  EAX + ECX -> EAX  add EAX, ECX in intel*/
void asmrr(int inst, int srcreg, int dstreg)
{
	printf("\t%s\t%s,%s", instpr[inst], regnm(dstreg, inst), regnm(srcreg, inst));
	if (inst == CMP || inst == CMPQ || inst == CMPSD)
		printf("           \t;  compare %s - %s\n", regnm(dstreg, inst),
			regnm(srcreg, inst));
	else if (inst == MOV || inst == MOVQ || inst == MOVSD)
		printf("         \t;  %s -> %s\n", regpr[srcreg], regpr[dstreg]);
	else printf("         \t;  %s %s %s -> %s\n",
		regpr[dstreg], instcompr[inst], regpr[srcreg], regpr[dstreg]);
}

void asmrr64(int inst, int srcreg, int dstreg)
{
	printf("\t%s\t%s,%s", instpr[inst], dregpr[dstreg], dregpr[srcreg]);
	if (inst == CMP || inst == CMPQ || inst == CMPSD)
		printf("           \t;  compare %s - %s\n", regnm(dstreg, inst),
			regnm(srcreg, inst));
	else if (inst == MOV || inst == MOVQ || inst == MOVSD)
		printf("         \t;  %s -> %s\n", dregpr[srcreg], dregpr[dstreg]);
	else printf("         \t;  %s %s %s -> %s\n",
		regpr[dstreg], instcompr[inst], dregpr[srcreg], dregpr[dstreg]);
}

/* Generate a load instruction relative to RBP: */
/* Example:  if code points to an integer variable,
	  asmld(MOVL, -code->symentry->offset, 0, code->stringval);   */
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

/* Generate a store instruction relative to RBP: */
/* Example:  asmst(MOVL, EAX, -code->symentry->offset, code->stringval);  */
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

/* Generate a floating store into a temporary on stack */
/* Example:  asmst(MOVL, EAX, -code->symentry->offset, code->stringval);  */
void asmsttemp(int reg)
{
	asmst(MOVSD, reg, -8, "temp");
}

/* Generate a floating from a temporary on stack */
/* Example:  asmst(MOVL, EAX, -code->symentry->offset, code->stringval);  */
void asmldtemp(int reg)
{
	asmld(MOVSD, -8, reg, "temp");
}

/* Generate a load instruction using offset and a register: */
/* Example:  asmldr(MOVL, 0, RAX, ECX, code->stringval);  [rax] -> ecx  */
void asmldr(int inst, int offset, int reg, int dstreg )
{
	if (offset == 0)
		printf("\t%s\t%s, [%s]", instpr[inst], regnm(dstreg, inst), dregpr[reg]);
	else
		printf("\t%s\t%s, [%s%d]", instpr[inst], regnm(dstreg, inst), dregpr[reg], offset);
	printf("         \t;  [%d+%s] -> %s\n", offset, dregpr[reg],regnm(dstreg, inst));
}

/* Generate a load instruction using offset, RBP and another register: */
/* Example:
   asmldrr(MOVL, -8, RAX, ECX, code->stringval);  -8(%rbp,%rax) --> %ecx */
void asmldrr(int inst, int offset, int reg, int dstreg, char str[])
{
	printf("\t%s\t%d(%%rbp,%s),%s", instpr[inst], offset, dregpr[reg],
		regnm(dstreg, inst));
	printf("         \t;  %s[%d] -> %s\n", str, offset, regnm(dstreg, inst));
}

/* Generate a load instruction using offset, RBP and
   another register with multiplier (2, 4 or 8): */
   /* Example:
	  asmldrrm(MOVL, -8, RAX, 4, ECX, code->stringval); -8(%rbp,%rax,4) --> %ecx */
void asmldrrm(int inst, int offset, int reg, int mult, int dstreg, char str[])
{
	printf("\t%s\t%d(%%rbp,%s,%d),%s", instpr[inst], offset, dregpr[reg], mult,
		regnm(dstreg, inst));
	printf("    \t;  %s[%d+%%rbp+%s*%d] -> %s\n", str, offset, dregpr[reg], mult,
		regnm(dstreg, inst));
}

/* Generate a store instruction relative to a register: */
/* Example:  asmstr(MOVL, ECX, 4, RAX, code->stringval);  ecx -> [rax+4]  mov [rax+4], ecx*/
void asmstr(int inst, int srcreg, int offset, int reg)
{
	if (offset == 0)
		printf("\t%s\t[%s], %s", instpr[inst], dregpr[reg], regnm(srcreg, inst));
	else
		printf("\t%s\t[%s %d], %s", instpr[inst], dregpr[reg], offset, regnm(srcreg, inst));
	printf("         \t;  %s -> [ %s + %d]\n", regnm(srcreg, inst), dregpr[reg], offset );
}

/* Generate a store instruction using offset, RBP and another register: */
/* Example:
   asmstrr(MOVL, ECX, -8, RAX, code->stringval);  %ecx --> -8(%rbp,%rax) */
void asmstrr(int inst, int srcreg, int offset, int reg, char str[])
{
	printf("\t%s\t%s,%d(%%rbp,%s)", instpr[inst], regnm(srcreg, inst), offset,
		dregpr[reg]);
	printf("\t;  %s -> %s[%s]\n", regnm(srcreg, inst), str,
		dregpr[reg]);
}

/* Generate a store instruction using offset, RBP and
   another register with multiplier (2, 4 or 8): */
   /* Example:
	  asmstrrm(MOVL, ECX, -8, RAX, 4, code->stringval); %ecx --> -8(%rbp,%rax,4) */
void asmstrrm(int inst, int srcreg, int offset, int reg, int mult, char str[])
{
	printf("\t%s\t%s,%d(%%rbp,%s,%d)", instpr[inst], regnm(srcreg, inst), offset,
		dregpr[reg], mult);
	printf("   \t;  %s -> %s[%d+%%rbp+%s*%d]\n", regnm(srcreg, inst), str,
		offset, dregpr[reg], mult);
}

/* Load float literal into specified register */
/* Example:  asmldflit(MOVSD, 7, XMM0);  literal with label .LC7 --> XMM0 */
void asmldflit(int inst, int label, int dstreg)
{
	int i;
	double d = 0.0;
	for (i = 0; i < nflit; i++)
		if (label == flabels[i])  d = fliterals[i];
	printf("\t%s\t.LC%d(%%rip),%s   \t;  %f -> %s\n", instpr[inst],
		label, regpr[dstreg], d, regpr[dstreg]);
}

/* Set up a literal address argument for subroutine call */
/* Example:  asmlitarg(8, EDI);   addr of literal 8 --> %edi */
void asmlitarg(int labeln, int dstreg)
{
	printf("\tmovl\t$.LC%d,%s       \t;  addr of literal .LC%d\n",
		labeln, regpr[dstreg], labeln);
}

/* Generate instructions to float data from an integer register to F reg. */
/* reg is integer source, freg is double float destination register. */
void asmfloat(int reg, int freg)
{
	printf("\tcvtsi2sd\t%s,%s    \t;  float %s -> %s\n", regpr[reg],
		regpr[freg], regpr[reg], regpr[freg]);
}

/* Generate instruction to fix data from float register freg to int reg. */
/* freg is double float source, reg is integer destination register. */
void asmfix(int freg, int reg)
{
	printf("\tcvttsd2si\t%s,%s    \t;  fix %s -> %s\n", regpr[freg],
		regpr[reg], regpr[freg], regpr[reg]);
}

/* Generate instructions to negate a float reg. */
/* reg is value to be negated, extrareg is another float register. */
void asmfneg(int reg, int extrareg)
{
	fnegused = 1;
	asmldflit(MOVSD, 666, extrareg);
	printf("\txorpd\t%s,%s           \t;  negate %s\n",
		regpr[extrareg], regpr[reg], regpr[reg]);
}

/* Make a literal for integer n with label number labeln */
void makeilit(int n, int labeln)
{
	iliterals[nilit] = n;
	ilabels[nilit] = labeln;
	nilit++;
}

/* Make a literal for float f with label number labeln */
void makeflit(float f, int labeln)
{
	fliterals[nflit] = f;
	flabels[nflit] = labeln;
	nflit++;
}

/* Make a byte literal for string s with label number labeln */
void makeblit(char s[], int labeln)
{
	int indx, i, done;
	if (nblit == 0)
	{
		indx = 0;
		blindex[0] = 0;
	}
	else indx = blindex[nblit];
	i = 0;
	done = 0;
	while (i < 16 && done == 0)
	{
		bliterals[indx++] = s[i];
		if (s[i] == '\0') done = 1;
		i++;
	};
	blabels[nblit] = labeln;
	nblit++;
	blindex[nblit] = indx;
}

typedef struct dtoi
{
	union
	{
		double dbl; int iarr[2];
	} val;
} Dtoi;

Dtoi dtoitmp;

/* Get half words of a double float */
/* Note: the [0] and [1] below are correct for Linux;
	 you may need to switch for other machine or OS. */
int lefth(d)
double d;
{
	dtoitmp.val.dbl = d;
	return (dtoitmp.val.iarr[1]);
} /* [0] for Sun, [1] for Linux */

int righth(d)
double d;
{
	dtoitmp.val.dbl = d;
	return (dtoitmp.val.iarr[0]);
} /* [1] for Sun, [0] for Linux */


void asm1r(int inst, int reg)
{
	printf("\t%s\t%s\t\t", instpr[inst], regpr[reg]);
	printf("\t;  %s / %s -> %s\n", regpr[EAX], regpr[reg], regpr[EAX]);
}

void asmpush(int reg)
{
	printf("\tpush\t%s\t\t", dregpr[reg]);
	printf("\t;  push  %s\n", dregpr[reg]);
}

void asmpop(int reg)
{
	printf("\tpop\t%s\t\t", dregpr[reg]);
	printf("\t;  pop  %s\n", dregpr[reg]);
}
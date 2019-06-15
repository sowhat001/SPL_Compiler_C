#ifndef GENASM_H
#define GENASM_H

#define RBASE 0         /* First local register to use = %eax */
#define RMAX  3         /* Last  local register to use */
#define FBASE 16        /* First F register to use = %xmm0 */
#define FMAX  31        /* Last  F register to use */

/* Define register names */
#define  EAX   0        /* General integer register */
#define  RAX   0
#define  EBX   1
#define  RBX   1
#define  ECX   2        /* General integer register */
#define  RCX   2
#define  EDX   3        /* General integer register */
#define  RDX   3
#define  ESI   4        /* Source Index for string */
#define  RSI   4
#define  EDI   5        /* Destination Index for string */
#define  RDI   5
#define  ESP   6        /* Stack Pointer */
#define  RBP   7
#define  EBP   7        /* Base Pointer */
#define  R8	   8
#define  R9	   9
#define  R10   10
#define  R11   11
#define  R12   12
#define  R13   13
#define  R14   14
#define  R15   15

#define  XMM0  16       /* Float register: function result */

#define MINIMMEDIATE -2147483648   /* Minimum value of immediate constant */
#define MAXIMMEDIATE  2147483647   /* Maximum value of immediate constant */

/* Define symbolic constants for kind of data */

#define BYTE     0
#define HALFWORD 1
#define WORD     2
#define FLOAT    3
#define ADDR     4

#define WORDSIZE      4             /* Integer */
#define FLOATSIZE     8             /* double float */
#define POINTERSIZE  16             /*  */

/* Define op code constants */

#define  JMP  0        /*  jump                  */
#define  JNE  1        /*  jump not equal        */
#define  JE   2        /*  jump equal            */
#define  JGE  3        /*  jump greater or equal */
#define  JL   4        /*  jump less             */
#define  JG   5        /*  jump greater          */
#define  JLE  6        /*  jump less or equal    */

#define MOV   0      /* Move long (32 bits) */
#define ADD		4      /* Add integer */
#define SUB		5      /* Subtract */

/* Define op codes for other instructions */
#define _MUL		6      /* Multiply */
#define _DIV		7
#define _AND		8
#define _OR		10    /* OR */

#define NEG		9
#define CMP   12
#define MOVSD  1      /* Move double */
#define MOVQ   2      /* Move quad (64 bits) */
#define CLTQ   3      /* sign-extend eax to rax */
#define ADDSD  13
#define SUBSD  14
#define MULSD  15
#define DIVSD  16
#define NEGSD  17
#define CMPQ   18    /* cmpq s2,s1 compares based on (s1 - s2) */
#define CMPSD  19
#define ADDQ   20
#define SUBQ   21
#define IMULQ  22
#define ANDQ   23
#define NEGQ   24
#define ORQ    25    /* OR */
#define NOTQ   26
#define LEA    27


/* Round up n to be a multiple of m */
int roundup(int n, int m);
/* Make entry code for a program. */
/* name is entry name, size is size of local storage on stack frame. */
/* returns actual stack frame size */
int asmentry(char name[], int size);
/* Make a label */
void asmlabel(int labeln);
/* Subroutine call */
/* Example:  asmcall(code->stringval);    Call function */
void asmcall(char name[]);
/* Generate a jump instruction.  Example:  asmjump(JG, 17);   */
void asmjump(int code, int labeln);
/* Generate an immediate instruction: move an int to a register   */
/* Example:  asmimmed(MOVL, 3, EAX);   Moves 3 to EAX  */
/* Example:  asmimmed(ADDL, 1, EAX);   Adds 1 to EAX  */
void asmimmed(int inst, int ival, int dstreg);
/* Generate an instruction with just the op. */
/* Example:  asmop(CLTQ) */
void asmop(int inst);
/* Generate a register to register instruction. */
/* op rs,rd     ADDL  */
/* Example:  asmrr(ADDL, ECX, EAX);  EAX + ECX -> EAX */
void asmrr(int inst, int srcreg, int dstreg);
/* Generate a load instruction relative to RBP: */
/* Example:  if code points to an integer variable,
   asmld(MOVL, -code->symentry->offset, 0, code->stringval);   */
void asmrr64(int inst, int srcreg, int dstreg);
	
void asmld(int inst, int off, int reg, char str[]);
/* Generate a store instruction relative to RBP: */
/* Example:  asmst(MOVL, EAX, -code->symentry->offset, code->stringval);  */
void asmld64(int inst, int off, int reg, char str[]);

void asmst(int inst, int reg, int off, char str[]);
/* Generate a floating store into a temporary on stack */
/* Example:  asmst(MOVL, EAX, -code->symentry->offset, code->stringval);  */
void asmst64(int inst, int reg, int off, char str[]);

void asmsttemp(int reg);
/* Generate a floating from a temporary on stack */
/* Example:  asmst(MOVL, EAX, -code->symentry->offset, code->stringval);  */
void asmldtemp(int reg);
/* Generate a load instruction using offset and a register: */
/* Example:  asmldr(MOVL, 4, RAX, ECX, code->stringval);  4(%rax) --> %ecx */
void asmldr(int inst, int offset, int reg, int dstreg);
/* Generate a load instruction using offset, RBP and another register: */
/* Example:
   asmldrr(MOVL, -8, RAX, ECX, code->stringval);  -8(%rbp,%rax) --> %ecx */
void asmldrr(int inst, int offset, int reg, int dstreg, char str[]);
/* Generate a load instruction using offset, RBP and
   another register with multiplier (2, 4 or 8): */
   /* Example:
	  asmldrrm(MOVL, -8, RAX, 4, ECX, code->stringval); -8(%rbp,%rax,4) --> %ecx */
void asmldrrm(int inst, int offset, int reg, int mult, int dstreg, char str[]);
/* Generate a store instruction relative to a register: */
/* Example:  asmstr(MOVL, ECX, 4, RAX, code->stringval);  %ecx --> 4(%rax) */
void asmstr(int inst, int srcreg, int offset, int reg);
/* Generate a store instruction using offset, RBP and another register: */
/* Example:
   asmstrr(MOVL, ECX, -8, RAX, code->stringval);  -8(%rbp,%rax) --> %ecx */
void asmstrr(int inst, int srcreg, int offset, int reg, char str[]);
/* Generate a store instruction using offset, RBP and
   another register with multiplier (2, 4 or 8): */
   /* Example:
	  asmstrrm(MOVL, ECX, -8, RAX, 4, code->stringval); %ecx --> -8(%rbp,%rax,4) */
void asmstrrm(int inst, int srcreg, int offset, int reg, int mult, char str[]);
/* Load float literal into specified register */
/* Example:  asmldflit(MOVSD, 7, XMM0);  literal with label .LC7 --> XMM0 */
void asmldflit(int inst, int label, int dstreg);
/* Set up a literal address argument for subroutine call, e.g. writeln('*') */
/* Example:  asmlitarg(8, EDI);   addr of literal 8 --> %edi */
void asmlitarg(int labeln, int dstreg);
/* Generate a left-shift instruction to shift left n bits, zero fill.   */
/* Example:  asmlshift(L1, 3, L1);     L1 shifted left 3 bits --> L1 */
void asmlshift(int srcreg, int n, int dstreg);
/* Generate instructions to float data from an integer register to F reg. */
/* reg is integer source, freg is double float destination register. */
void asmfloat(int reg, int freg);
/* Generate instruction to fix data from float register freg to int reg. */
/* freg is double float source, reg is integer destination register. */
void asmfix(int freg, int reg);
/* Generate instructions to negate a float reg. */
/* reg is value to be negated, extrareg is another float register. */
void asmfneg(int reg, int extrareg);
/* Get half words of a double float */
/* Note: the [0] and [1] below are correct for Linux;
	 you may need to switch for other machine or OS. */
int lefth(double d);
int righth(double d);
/* Make exit code for a program. */
/* This is just canned code following calling conventions for target machine */
void asmexit(char name[]);
/* Make a literal for integer n with label number labeln */
void makeilit(int n, int labeln);
/* Make a literal for float f with label number labeln */
void makeflit(float f, int labeln);
/* Make a byte literal for string s with label number labeln */
void makeblit(char s[], int labeln);
/* Output literals and end material*/
void outlits();

/* Print a section of canned code.  Quits on an empty string.  */
void directPrint(char* lines[]);

void asmlabelstr(char name[]);
// imull
void asm1r(int inst, int reg);

void asmpush(int reg);
void asmpop(int reg);
#endif
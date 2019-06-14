#ifndef CODEGEN_H
#define CODEGEN_H

#include "symtab.h"
#include "genasm.h"
#include "token.h"
#include "utils.h"
#include "parsef.h"


#define NUM_argRegsS	4
#define NUM_INT_REGS    8
#define NUM_FP_REGS     24
#define NUM_REGS        32

const int argRegs[NUM_argRegsS] = { EDI, ESI, EDX, ECX };

char funcTopCode[] =
{
  "\tpush	rbp				; save base pointer on stack\n"
  "\tmov	rbp, rsp		; move stack pointer to base pointer\n"
  "\tsub	rsp, %d			; make space for this stack frame\n"
  "\tpush	rbx			; make space for this stack frame\n"
  "\tpush	rcx			; make space for this stack frame\n"
  "\tpush	rdx			; make space for this stack frame\n"
};
char* funBotCode[] =
{
	"	pop	rdx			; make space for this stack frame",
	"	pop	rcx			; make space for this stack frame",
	"	pop	rbx			; make space for this stack frame",
	"	mov	rsp, rbp",
	"	pop	rbp",
	"	ret",
	"",
};


extern int blocknumber;
extern int curLevel;
extern int basicsizes[5];

int nextLabel;    /* Next available label number */
int stackFrameSize;   /* total stack frame size */

int regs[NUM_REGS] = { 0 };

/* Top-level entry for code generator.
   parseResult    = pointer to code:  (program foo (output) (progn ...))
   varsize  = size of local storage in bytes
   maxlabel = maximum label number used so far

Add this line to the end of your main program:
	genCode(parseresult, blockoffs[blocknumber], labelnumber);
The generated code is printed out; use a text editor to extract it for
your .s file.
		 */

void genCode(TOKEN parseResult, int varsize, int maxlabel);

/* Trivial version: always returns RBASE + 0 */
/* Get a register.   */
/* Need a type parameter or two versions for INTEGER or REAL */
int getReg(int kind);

/* Trivial version */
/* Generate code for arithmetic expression, return a register number */
int genFunCall(TOKEN code);

int genExp(TOKEN code);

int genOp(TOKEN code, int lhs_reg, int rhs_reg);

/* Generate code for a Statement from an intermediate-code form */
void genc(TOKEN code);

void resetRegs();

int hasFloat(int lhs_reg, int rhs_reg);

int bothFloat(int lhs_reg, int rhs_reg);

void freeReg(int regNum);

void setRegUsed(int regNum);

#endif
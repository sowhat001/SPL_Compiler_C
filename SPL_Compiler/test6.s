# ---------------------- Beginning of Generated Code --------------------
        .file   "foo"
        .text
.globl hello
        .type   hello, @function
hello:
.LFB0:
	.cfi_startproc
	pushq	%rbp              # save base pointer on stack
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp        # move stack pointer to base pointer
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
        subq	$32, %rsp 	  # make space for this stack frame
	movq	%rbx, %r9        # save %rbx (callee-saved) in %r9
# ------------------------- begin Your code -----------------------------
	jmp	.L0 			#  jump 
gcd:
	pushq	%rbp			# save base pointer on stack
	pushq	%rbx			# save %rbx
	pushq	%rcx			# save %rcx
	pushq	%rdx			# save %rdx
	movq	%rsp, %rbp		# move stack pointer to base pointer
	subq	$32, %rsp		# make space for this stack frame
	mov	edi, [ebp + -32]     	#  edi -> a
	mov	esi, [ebp + -28]     	#  esi -> b
	mov	eax, [ebp - -28]     	#  b -> eax
	mov	0,ebx         	#  0 -> ebx
	cmpl	eax,ebx           	#  compare ebx - eax
	je	.L1 			#  jump if     ==
	jmp	.L2 			#  jump 
.L1:
	mov	eax, [ebp - -32]     	#  a -> eax
	mov	eax, [ebp + -24]     	#  eax -> gcd
	jmp	.L3 			#  jump 
.L2:
	mov	eax, [ebp - -28]     	#  b -> eax
	mov	eax,edi         	#  eax -> edi
	mov	eax, [ebp - -32]     	#  a -> eax
	mov	ebx, [ebp - -28]     	#  b -> ebx
	mov	0,edx         	#  0 -> edx
	divl	ebx			#  eax / ebx -> eax
	mov	edx,esi         	#  edx -> esi
	call	gcd              	#  gcd()
	mov	eax,ebx         	#  eax -> ebx
	mov	ebx, [ebp + -24]     	#  ebx -> gcd
.L3:
	mov	eax, [ebp - -24]     	#  gcd -> eax
	movq    %rbp, %rsp
	popq	%rdx
	popq	%rcx
	popq	%rbx
	popq	%rbp
	ret
.L0:
	mov	9,eax         	#  9 -> eax
	mov	eax,edi         	#  eax -> edi
	mov	36,eax         	#  36 -> eax
	mov	eax,esi         	#  eax -> esi
	call	gcd              	#  gcd()
	mov	eax,ebx         	#  eax -> ebx
	mov	3,eax         	#  3 -> eax
	mov	eax,edi         	#  eax -> edi
	mov	6,eax         	#  6 -> eax
	mov	eax,esi         	#  eax -> esi
	call	gcd              	#  gcd()
	mov	eax,ecx         	#  eax -> ecx
	mov	ebx,eax         	#  ebx -> eax
	mov	0,edx         	#  0 -> edx
	imull	ecx			#  eax / ecx -> eax
	mov	eax, [ebp + -32]     	#  eax -> ans
	mov	eax, [ebp - -32]     	#  ans -> eax
	mov	eax,edi         	#  eax -> edi
	call	writeln              	#  writeln()
# ----------------------- begin Epilogue code ---------------------------
	movq	%r9, %rbx        # restore %rbx (callee-saved) from %r9
        leave
        ret
        .cfi_endproc
.LFE0:
        .size   hello, .-hello
# ----------------- end Epilogue; Literal data follows ------------------
        .section        .rodata

        .ident  "Compiler Principle - Spring 2017"

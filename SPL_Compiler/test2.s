# ---------------------- Beginning of Generated Code --------------------
        .file   "foo"
        .text
.globl test
        .type   test, @function
test:
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
	jmp	L0 			#  jump 
go:
	pushq	%rbp			# save base pointer on stack
	pushq	%rbx			# save %rbx
	pushq	%rcx			# save %rcx
	pushq	%rdx			# save %rdx
	movq	%rsp, %rbp		# move stack pointer to base pointer
	subq	$32, %rsp		# make space for this stack frame
	mov	[ebp-32], edi      	#  edi -> a
	mov	eax, [ebp-32]     	#  a -> eax
	mov	ebx,1         	#  1 -> ebx
	sub	eax,ebx         	#  ebx - eax -> ebx
	mov	[ebp-24], eax      	#  eax -> b
	mov	eax, [ebp-32]     	#  a -> eax
	mov	ebx,2         	#  2 -> ebx
	sub	eax,ebx         	#  ebx - eax -> ebx
	mov	[ebp-20], eax      	#  eax -> c
	mov	eax, [ebp-32]     	#  a -> eax
	mov	ebx,1         	#  1 -> ebx
	cmp	eax,ebx           	#  compare ebx - eax
	je	L1 			#  jump if     ==
	jmp	L2 			#  jump 
L1:
	mov	eax,1         	#  1 -> eax
	mov	[ebp-28], eax      	#  eax -> go
	jmp	L3 			#  jump 
L2:
	mov	eax, [ebp-32]     	#  a -> eax
	mov	ebx,2         	#  2 -> ebx
	cmp	eax,ebx           	#  compare ebx - eax
	je	L4 			#  jump if     ==
	jmp	L5 			#  jump 
L4:
	mov	eax,1         	#  1 -> eax
	mov	[ebp-28], eax      	#  eax -> go
	jmp	L6 			#  jump 
L5:
	mov	eax, [ebp-24]     	#  b -> eax
	mov	eax,edi         	#  eax -> edi
	call	go              	#  go()
	mov	eax,ebx         	#  eax -> ebx
	mov	[ebp-28], ebx      	#  ebx -> go
	mov	eax, [ebp-20]     	#  c -> eax
	mov	eax,edi         	#  eax -> edi
	call	go              	#  go()
	mov	eax,ebx         	#  eax -> ebx
	mov	eax, [ebp-28]     	#  go -> eax
	add	ebx,eax         	#  eax + ebx -> eax
	mov	[ebp-28], ebx      	#  ebx -> go
L6:
L3:
	mov	eax, [ebp-28]     	#  go -> eax
	movq    %rbp, %rsp
	popq	%rdx
	popq	%rcx
	popq	%rbx
	popq	%rbp
	ret
L0:
	mov	eax,10         	#  10 -> eax
	mov	eax,edi         	#  eax -> edi
	call	go              	#  go()
	mov	eax,ebx         	#  eax -> ebx
	mov	[ebp-32], ebx      	#  ebx -> i
	mov	eax, [ebp-32]     	#  i -> eax
	mov	eax,edi         	#  eax -> edi
	call	writeln              	#  writeln()
# ----------------------- begin Epilogue code ---------------------------
	movq	%r9, %rbx        # restore %rbx (callee-saved) from %r9
        leave
        ret
        .cfi_endproc
.LFE0:
        .size   test, .-test
# ----------------- end Epilogue; Literal data follows ------------------
        .section        .rodata

        .ident  "Compiler Principle - Spring 2017"

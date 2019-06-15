; ---------------------- Beginning of Generated Code --------------------
extern writeln
global _start:
_start:
	push rbp
	mov rbp, rsp
	sub rsp, 16
	mov rbx, r9
	mov	r8,rbp         	;  rbp -> r8
	jmp	L0 			;  jump 
L0:
	mov	eax,128         	;  128 -> eax
	mov	[rbp-16], eax      	;  eax -> a
	mov	eax,72         	;  72 -> eax
	mov	[rbp-12], eax      	;  eax -> b
L2:
	mov	eax, [rbp-16]     	;  a -> eax
	mov	ebx, [rbp-12]     	;  b -> ebx
	mov	edx,0         	;  0 -> edx
	div	ebx			;  eax / ebx -> eax
	mov	[rbp-8], edx      	;  edx -> r
	mov	eax, [rbp-12]     	;  b -> eax
	mov	[rbp-16], eax      	;  eax -> a
	mov	eax, [rbp-8]     	;  r -> eax
	mov	[rbp-12], eax      	;  eax -> b
	mov	eax, [rbp-8]     	;  r -> eax
	mov	ebx,0         	;  0 -> ebx
	cmp	eax,ebx           	;  compare eax - ebx
	je	L3 			;  jump if     ==
	jmp	L5 			;  jump 
L3:
	jmp	L1 			;  jump 
	jmp	L4 			;  jump 
L5:
	jmp	L2 			;  jump 
L4:
L1:
	mov	eax, [rbp-16]     	;  a -> eax
	mov	edi,eax         	;  eax -> edi
	call	writeln              	;  writeln()
	mov	eax, [rbp-12]     	;  b -> eax
	mov	edi,eax         	;  eax -> edi
	call	writeln              	;  writeln()
	mov	eax, [rbp-8]     	;  r -> eax
	mov	edi,eax         	;  eax -> edi
	call	writeln              	;  writeln()
mov ebx, 0
mov eax, 1
int 80h;exit

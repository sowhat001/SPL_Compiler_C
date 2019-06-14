BEGIN
Symbol table level 0
 0:  15188104        sqrt  VAR    2 typ    NULL  lvl  0  siz -842150451  off -842150451
 1:  15188240        _ord  knd 5 1  typ 0  lvl  0  siz -842150451  off -842150451
(FUNCTION)
 2:  15187968       _sqrt  knd 5 2  typ 0  lvl  0  siz -842150451  off -842150451
(FUNCTION)
 3:  15212176      readln  VAR    -1 typ    NULL  lvl  0  siz -842150451  off -842150451
 4:  15188512        _chr  knd 5 4  typ 0  lvl  0  siz -842150451  off -842150451
(FUNCTION)
 5:  15211088       write  VAR    4 typ    NULL  lvl  0  siz -842150451  off -842150451
 6:  15164192     integer  BASIC  basicType   1          siz     4
 7:  15211768     _readln  knd 5 -1  typ 0  lvl  0  siz -842150451  off -842150451
(FUNCTION)
 8: NULL
 9: NULL
10: NULL
11: NULL
12: NULL
13:  15210000        _odd  knd 5 1  typ 0  lvl  0  siz -842150451  off -842150451
(FUNCTION)
14: NULL
15:  15187696        _sqr  knd 5 2  typ 0  lvl  0  siz -842150451  off -842150451
(FUNCTION)
16: NULL
17: NULL
18: NULL
19: NULL
20:  15208640        pred  VAR    4 typ    NULL  lvl  0  siz -842150451  off -842150451
21:  15211360      _write  knd 5 -1  typ 0  lvl  0  siz -842150451  off -842150451
(FUNCTION)
22:  15188784       _pred  knd 5 4  typ 0  lvl  0  siz -842150451  off -842150451
(FUNCTION)
23: NULL
24:  15188376         ord  VAR    1 typ    NULL  lvl  0  siz -842150451  off -842150451
25:  15212312        read  VAR    -1 typ    NULL  lvl  0  siz -842150451  off -842150451
26:  15210408    _writeln  knd 5 -1  typ 0  lvl  0  siz -842150451  off -842150451
(FUNCTION)
27:  15208912       _read  knd 5 -1  typ 0  lvl  0  siz -842150451  off -842150451
(FUNCTION)
28:  15211632       _succ  knd 5 4  typ 0  lvl  0  siz -842150451  off -842150451
(FUNCTION)
29: NULL
30: NULL
Symbol table level 1
 0: NULL
 1: NULL
 2: NULL
 3: NULL
 4: NULL
 5: NULL
 6: NULL
 7: NULL
 8: NULL
 9: NULL
10:  15209048         ans  VAR    1 typ integer  lvl  1  siz     4  off     0
11: NULL
12: NULL
13: NULL
14: NULL
15: NULL
16: NULL
17: NULL
18: NULL
19: NULL
20:  15209728        _gcd  knd 5 1  typ 15164192  lvl  1  siz -842150451  off -842150451
(FUNCTION integer)
21: NULL
22: NULL
23: NULL
24: NULL
25: NULL
26: NULL
27: NULL
28: NULL
29: NULL
30: NULL
Symbol table level 2
 0: NULL
 1: NULL
 2: NULL
 3: NULL
 4: NULL
 5: NULL
 6: NULL
 7: NULL
 8: NULL
 9: NULL
10: NULL
11: NULL
12:  15210136         gcd  VAR    1 typ integer  lvl  2  siz     4  off     8
13: NULL
14: NULL
15: NULL
16: NULL
17: NULL
18:  15209184           a  VAR    1 typ integer  lvl  2  siz     4  off     0
19:  15211904           b  VAR    1 typ integer  lvl  2  siz     4  off     4
20: NULL
21: NULL
22: NULL
23: NULL
24: NULL
25: NULL
26: NULL
27: NULL
28: NULL
29: NULL
30: NULL
hello
©À  OP_FUN_DCL
  ©À  function
    ©À  gcd
    ©À  begin
      ©À  if
        ©À  =
          ©À  b
          ©À  0
        ©À  begin
          ©À  :=
            ©À  gcd
            ©À  a
        ©À  begin
          ©À  :=
            ©À  gcd
            ©À  gcd
              ©À  (
              ©À  b
              ©À  %
                ©À  a
                ©À  b
©À  begin
  ©À  :=
    ©À  ans
    ©À  *
      ©À  gcd
        ©À  (
        ©À  9
        ©À  36
      ©À  gcd
        ©À  (
        ©À  3
        ©À  6
  ©À  writeln
    ©À  (
    ©À  ans
; ---------------------- Beginning of Generated Code --------------------
extern writeln
global _start:
_start:
	push rbp
	mov rbp, rsp
	sub rsp, 32
	mov rbx, r9
	jmp	L0 			;  jump 
gcd:
	push	rbp				; save base pointer on stack
	mov	rbp, rsp		; move stack pointer to base pointer
	sub	rsp, 32			; make space for this stack frame
	push	rbx			; make space for this stack frame
	push	rcx			; make space for this stack frame
	push	rdx			; make space for this stack frame
	mov	[rbp-32], edi      	;  edi -> a
	mov	[rbp-28], esi      	;  esi -> b
	mov	eax, [rbp-28]     	;  b -> eax
	mov	ebx,0         	;  0 -> ebx
	cmp	ebx,eax           	;  compare ebx - eax
	je	L1 			;  jump if     ==
	jmp	L2 			;  jump 
L1:
	mov	eax, [rbp-32]     	;  a -> eax
	mov	[rbp-24], eax      	;  eax -> gcd
	jmp	L3 			;  jump 
L2:
	mov	eax, [rbp-28]     	;  b -> eax
	mov	edi,eax         	;  eax -> edi
	mov	eax, [rbp-32]     	;  a -> eax
	mov	ebx, [rbp-28]     	;  b -> ebx
	mov	edx,0         	;  0 -> edx
	div	ebx			;  eax / ebx -> eax
	mov	esi,edx         	;  edx -> esi
	call	gcd              	;  gcd()
	mov	ebx,eax         	;  eax -> ebx
	mov	[rbp-24], ebx      	;  ebx -> gcd
L3:
	mov	eax, [rbp-24]     	;  gcd -> eax
	pop	rdx			; make space for this stack frame
	pop	rcx			; make space for this stack frame
	pop	rbx			; make space for this stack frame
	mov	rsp, rbp
	pop	rbp
	ret
L0:
	mov	eax,9         	;  9 -> eax
	mov	edi,eax         	;  eax -> edi
	mov	eax,36         	;  36 -> eax
	mov	esi,eax         	;  eax -> esi
	call	gcd              	;  gcd()
	mov	ebx,eax         	;  eax -> ebx
	mov	eax,3         	;  3 -> eax
	mov	edi,eax         	;  eax -> edi
	mov	eax,6         	;  6 -> eax
	mov	esi,eax         	;  eax -> esi
	call	gcd              	;  gcd()
	mov	ecx,eax         	;  eax -> ecx
	mov	eax,ebx         	;  ebx -> eax
	mul	ecx			;  eax / ecx -> eax
	mov	[rbp-32], eax      	;  eax -> ans
	mov	eax, [rbp-32]     	;  ans -> eax
	mov	edi,eax         	;  eax -> edi
	call	writeln              	;  writeln()
mov ebx, 0
mov eax, 1
int 80h;exit

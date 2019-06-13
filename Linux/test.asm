extern writeln
global _start:
_start:
        push rbp
        mov rbp, rsp
        sub rsp, 32
        mov rbx, r9
        jmp     L0                      ;  jump
gcd:
        push    rbp                             ; save base pointer on stack
        mov     rbp, rsp                ; move stack pointer to base pointer
        sub     rsp, 32                 ; make space for this stack frame
        push    rbx                     ; make space for this stack frame
        push    rcx                     ; make space for this stack frame
        push    rdx                     ; make space for this stack frame
        mov     [rbp-32], edi           ;  edi -> a
        mov     [rbp-28], esi           ;  esi -> b
        mov     eax, [rbp-28]           ;  b -> eax
        mov     ebx,0           ;  0 -> ebx
        cmp     ebx,eax                 ;  compare ebx - eax
        je      L1                      ;  jump if     ==
        jmp     L2                      ;  jump
L1:
        mov     eax, [rbp-32]           ;  a -> eax
        mov     [rbp-24], eax           ;  eax -> gcd
        jmp     L3                      ;  jump
L2:
        mov     eax, [rbp-28]           ;  b -> eax
        mov     edi,eax                 ;  eax -> edi
        mov     eax, [rbp-32]           ;  a -> eax
        mov     ebx, [rbp-28]           ;  b -> ebx
        mov     edx,0           ;  0 -> edx
        div  ebx                     ;  eax / ebx -> eax
        mov     esi,edx                 ;  edx -> esi
        call    gcd                     ;  gcd()
        mov     ebx,eax                 ;  eax -> ebx
        mov     [rbp-24], ebx           ;  ebx -> gcd
L3:
        mov     eax, [rbp-24]           ;  gcd -> eax
        pop     rdx                     ; make space for this stack frame
        pop     rcx                     ; make space for this stack frame
        pop     rbx                     ; make space for this stack frame
        mov     rsp, rbp
        pop     rbp
        ret
L0:
        mov     eax,9           ;  9 -> eax
        mov     edi,eax                 ;  eax -> edi
        mov     eax,36          ;  36 -> eax
        mov     esi,eax                 ;  eax -> esi
        call    gcd                     ;  gcd()
        mov     ebx,eax                 ;  eax -> ebx
        mov     eax,3           ;  3 -> eax
        mov     edi,eax                 ;  eax -> edi
        mov     eax,6           ;  6 -> eax
        mov     esi,eax                 ;  eax -> esi
        call    gcd                     ;  gcd()
        mov     ecx,eax                 ;  eax -> ecx
        mov     eax,ebx                 ;  ebx -> eax
        mul     ecx                     ;  eax / ecx -> eax
        mov     [rbp-32], eax           ;  eax -> ans
        mov     eax, [rbp-32]           ;  ans -> eax
        mov     edi,eax                 ;  eax -> edi
        call    writeln                 ;  writeln()
mov ebx, 0
mov eax, 1
int 80h;exit

extern writeln
global _start:
_start:
        push rbp
        mov rbp, rsp
        sub rsp, 16
        mov rbx, r9
        jmp     L0                      ;  jump
L0:
        mov     eax,1           ;  1 -> eax
        mov     [rbp-12], eax           ;  eax -> s
        mov     eax,0           ;  0 -> eax
        mov     [rbp-16], eax           ;  eax -> n
L1:
        mov     eax, [rbp-12]           ;  s -> eax
        mov     ebx,10          ;  10 -> ebx
        cmp     eax,ebx                 ;  compare eax - ebx
        jle     L2                      ;  jump if     <=
        jmp     L3                      ;  jump
L2:
        mov     eax, [rbp-16]           ;  n -> eax
        mov     ebx,1           ;  1 -> ebx
        add     eax,ebx                 ;  eax + ebx -> eax
        mov     [rbp-16], eax           ;  eax -> n
        mov     eax, [rbp-12]           ;  s -> eax
        mov     ebx, [rbp-16]           ;  n -> ebx
        mul     ebx                     ;  eax / ebx -> eax
        mov     [rbp-12], eax           ;  eax -> s
        jmp     L1                      ;  jump
L3:
        mov     eax, [rbp-12]           ;  s -> eax
        mov     edi,eax                 ;  eax -> edi
        call    writeln                 ;  writeln()
        mov     eax, [rbp-16]           ;  n -> eax
        mov     edi,eax                 ;  eax -> edi
        call    writeln                 ;  writeln()
mov ebx, 0
mov eax, 1
int 80h;exit
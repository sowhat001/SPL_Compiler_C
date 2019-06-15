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
        mov     [rbp-16], eax           ;  eax -> x
        mov     eax,10          ;  10 -> eax
        mov     [rbp-8], eax            ;  eax -> n
        mov     eax,2           ;  2 -> eax
        mov     [rbp-12], eax           ;  eax -> i
L1:
        mov     eax, [rbp-12]           ;  i -> eax
        mov     ebx, [rbp-8]            ;  n -> ebx
        cmp     eax,ebx                 ;  compare eax - ebx
        jle     L2                      ;  jump if     <=
        jmp     L3                      ;  jump
L2:
        mov     eax, [rbp-16]           ;  x -> eax
        mov     ebx, [rbp-12]           ;  i -> ebx
        mul     ebx                     ;  eax / ebx -> eax
        mov     [rbp-16], eax           ;  eax -> x
        mov     eax, [rbp-12]           ;  i -> eax
        mov     ebx,1           ;  1 -> ebx
        add     eax,ebx                 ;  eax + ebx -> eax
        mov     [rbp-12], eax           ;  eax -> i
        jmp     L1                      ;  jump
L3:
        mov     eax,20          ;  20 -> eax
        mov     [rbp-8], eax            ;  eax -> n
        mov     eax, [rbp-16]           ;  x -> eax
        mov     edi,eax                 ;  eax -> edi
        call    writeln                 ;  writeln()
        mov     eax, [rbp-12]           ;  i -> eax
        mov     edi,eax                 ;  eax -> edi
        call    writeln                 ;  writeln()
        mov     eax, [rbp-8]            ;  n -> eax
        mov     edi,eax                 ;  eax -> edi
        call    writeln                 ;  writeln()
mov ebx, 0
mov eax, 1
int 80h;exit
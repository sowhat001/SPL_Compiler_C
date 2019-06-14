extern writeln
global _start:
_start:
        push rbp
        mov rbp, rsp
        sub rsp, 48
        mov rbx, r9
        jmp     L0                      ;  jump
L0:
        mov     eax,5           ;  5 -> eax
        mov     [rbp-48], eax           ;  eax -> x
        mov     eax, [rbp-48]           ;  x -> eax
        mov     [rbp-28], eax           ;  eax -> y[5]
        mov     eax, [rbp-28]           ;  y[5] -> eax
        mov     edi,eax                 ;  eax -> edi
        call    writeln                 ;  writeln()
mov ebx, 0
mov eax, 1
int 80h;exit
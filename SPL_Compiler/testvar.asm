extern writeln
global _start:
_start:
        push rbp
        mov rbp, rsp
        sub rsp, 16
        mov rbx, r9
        jmp     L0                      ;  jump
go:
        push    rbp                             ; save base pointer on stack
        mov     rbp, rsp                ; move stack pointer to base pointer
        sub     rsp, 16                 ; make space for this stack frame
        push    rbx                     ; make space for this stack frame
        push    rcx                     ; make space for this stack frame
        push    rdx                     ; make space for this stack frame
        mov     [rbp-16], rdi           ;  rdi -> b
        mov     rax, [rbp-16]           ;  &b -> rax
        mov     ebx, [rax]              ;  [0+rax] -> ebx
        mov     eax,1           ;  1 -> eax
        add     ebx,eax                 ;  ebx + eax -> ebx
        mov     rax, [rbp-16]           ;  &b -> rax
        mov     [rax], ebx              ;  ebx -> [ rax + 0]
        mov     eax,1           ;  1 -> eax
        mov     [rbp-8], eax            ;  eax -> go
        mov     eax, [rbp-8]            ;  go -> eax
        pop     rdx                     ; make space for this stack frame
        pop     rcx                     ; make space for this stack frame
        pop     rbx                     ; make space for this stack frame
        mov     rsp, rbp
        pop     rbp
        ret
L0:
        mov     eax,2           ;  2 -> eax
        mov     [rbp-16], eax           ;  eax -> m
        lea     rax, [rbp-16]           ;  &go -> rax
        mov     rdi,rax                 ;  rax -> rdi
        call    go                      ;  go()
        mov     ebx,eax                 ;  eax -> ebx
        mov     eax, [rbp-16]           ;  m -> eax
        mov     edi,eax                 ;  eax -> edi
        call    writeln                 ;  writeln()
mov ebx, 0
mov eax, 1
int 80h;exit
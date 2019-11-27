extern strlen
extern print
extern exit
extern mem_alloc
extern mem_free
global basic_string__oper_equ
global main
extern ExitProcess

section .data
str5: db 'Test', 0x00
str7: db 'Window', 0x00

section .text
basic_string__oper_equ:
push rbp
mov qword rbp, rsp
sub rsp, 48
mov qword [rbp-8], rdi
mov qword [rbp-16], r8
.entry:
mov qword rax, str5
mov qword rdi, rax
call print

leave
ret

main:
push rbp
mov qword rbp, rsp
sub rsp, 48
.entry:
lea rdi, [rbp-16]
mov qword rax, str7
mov qword r8, rax
call basic_string__oper_equ
call ExitProcess
leave
ret


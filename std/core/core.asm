extern WriteFile
extern GetStdHandle
extern ExitProcess
extern HeapAlloc
extern GetProcessHeap
global strlen
global print
global exit
global mem_alloc
global mem_free

section .data

section .text
strlen:
push rbp
mov qword rbp, rsp
sub rsp, 48
mov qword [rbp-8], rdi
.entry:
mov dword [ebp - 12], 0
.L0:
mov qword rax, [rbp-8]
mov dword ebx, [ebp-12]
cmp byte [rax+rbx], 0
je .resume0
mov dword eax, [ebp-12]
add dword eax, 1
mov dword [ebp-12], eax
jmp .L0
.resume0:
mov dword eax, [ebp-12]

leave
ret

print:
push rbp
mov qword rbp, rsp
sub rsp, 48
mov qword [rbp-8], rdi
.entry:
mov dword ecx, -11
call GetStdHandle
mov qword [rbp-16], rax
mov qword rdi, [rbp-8]
call strlen
mov dword [ebp-20], eax
mov qword rcx, [rbp-16]
mov qword rdx, [rbp-8]
mov dword r8d, [ebp-20]
mov dword r9d, 0
mov dword [esp + 32], 0
call WriteFile

leave
ret

exit:
push rbp
mov qword rbp, rsp
sub rsp, 48
mov dword [ebp-4], edi
.entry:
mov dword ecx, [ebp-4]
call ExitProcess

leave
ret

mem_alloc:
push rbp
mov qword rbp, rsp
sub rsp, 48
mov dword [ebp-4], edi
.entry:
call GetProcessHeap
mov qword [rbp-16], rax
mov qword rcx, [rbp-16]
mov dword edx, 8
mov dword r8d, [ebp-4]
call HeapAlloc
mov qword [rbp-24], rax
mov qword rax, [rbp-24]

leave
ret

mem_free:
push rbp
mov qword rbp, rsp
sub rsp, 48
mov qword [rbp-8], rdi
.entry:

leave
ret


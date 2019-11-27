; Array
; 10 elements of bytes

mov rbx, [rbp - 10]

; Get first element

mov rax, [rbp - 10 - offset * (size)]

; Get second element

mov rax, [rbx + 1 * (size)]

; Append to array

mov rax, 48
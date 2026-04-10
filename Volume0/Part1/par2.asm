section .data
    a dq 0.1
    b dq 0.2
    msg db "Result:", 10, 0

section .text
    global main
    extern printf

main:
    ; Integer ALU (ADD, AND, XOR)
    mov rax, 5        ; A = 5
    mov rbx, 3        ; B = 3

    add rax, rbx      ; rax = A + B (ALU add)
    ; rax = 8

    mov rcx, 5
    and rcx, 3        ; rcx = A & B

    mov rdx, 5
    xor rdx, 3        ; rdx = A ^ B

    
    ; Floating Point (SSE2)
    movsd xmm0, [a]   ; load double 0.1
    movsd xmm1, [b]   ; load double 0.2

    addsd xmm0, xmm1  ; xmm0 = xmm0 + xmm1
    ; result ≈ 0.30000000000000004
    
    mov rax, 0
    ret
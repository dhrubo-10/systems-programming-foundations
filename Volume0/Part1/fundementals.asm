section .data
    msg_half db "Half Adder (1,1): ",0
    msg_full db "Full Adder (1,1,1): ",0
    msg_add  db "Ripple Add (5+3): ",0
    msg_mux  db "MUX (10,20,S=1): ",0
    msg_dec  db "Decoder (A1=1,A0=0): ",0
    nl db 10,0

section .bss
    buf resb 32

section .text
    global _start

; print string 
print:
    mov rax, 1
    mov rdi, 1
    syscall
    ret

;  print number (rax) 
print_num:
    mov rbx, 10
    mov rcx, buf+31
    mov byte [rcx], 0

.convert:
    dec rcx
    xor rdx, rdx
    div rbx
    add dl, '0'
    mov [rcx], dl
    test rax, rax
    jnz .convert

    mov rsi, rcx
    mov rdx, buf+31
    sub rdx, rcx
    call print
    ret

_start:

;  Half Adder: A=1, B=1 
    mov rsi, msg_half
    mov rdx, 20
    call print

    mov al, 1
    mov bl, 1

    mov cl, al
    and cl, bl      ; Carry

    xor al, bl      ; Sum

    movzx rax, al
    call print_num

    mov rsi, nl
    mov rdx, 1
    call print

;  Full Adder: A=1, B=1, Cin=1 
    mov rsi, msg_full
    mov rdx, 25
    call print

    mov al, 1
    mov bl, 1
    mov dl, 1

    mov cl, al
    xor cl, bl
    xor cl, dl      ; Sum

    mov ah, al
    and ah, bl

    mov bh, al
    xor bh, bl
    and bh, dl

    or ah, bh       ; Cout

    movzx rax, cl
    call print_num

    mov rsi, nl
    mov rdx, 1
    call print

;  Ripple Add (5 + 3) 
    mov rsi, msg_add
    mov rdx, 20
    call print

    mov rax, 5
    mov rbx, 3
    add rax, rbx

    call print_num

    mov rsi, nl
    mov rdx, 1
    call print

;  MUX: S=1 choose B 
    mov rsi, msg_mux
    mov rdx, 20
    call print

    mov eax, 10
    mov ebx, 20
    mov ecx, 1

    cmp ecx, 0
    je .useA
    mov eax, ebx
.useA:
    call print_num

    mov rsi, nl
    mov rdx, 1
    call print

;  Decoder (A1=1, A0=0) 
    mov rsi, msg_dec
    mov rdx, 28
    call print

    mov al, 1
    mov bl, 0

    ; Y2 = A1 & !A0
    mov cl, bl
    not cl
    and cl, al

    movzx rax, cl
    call print_num

    mov rsi, nl
    mov rdx, 1
    call print

    mov rax, 60
    xor rdi, rdi
    syscall
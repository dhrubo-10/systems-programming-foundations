%if 0
 Reference:
 Bootloader 0
 the bits.c rep in x86 assembly
 %endif

 section .text
global _start

_start:

	; #define IF_POW2(n) ((n) != 0 && ((n) & ((n)-1)) == 0)
	; if n == 8
    mov eax, 8         
    test eax, eax       ; check if n == 0
    jz not_pow2         ; as we knw if zero -> not power of 2

    mov ebx, eax        
    dec ebx             
    and eax, ebx        ; eax = n & (n-1)
                        ; now this clears lowst set bit

    jz is_pow2          ; if result == 0 -> power of 2

not_pow2:
 	; daydream..............
    jmp next1

is_pow2:
    ; daydrm 2

next1:

	; from C: #define ALIGN_UP(val, align) (((val) + (align) - 1) & ~((align) - 1))
    ; ALIGN_UP (17 -> 16)

    mov eax, 17         
    mov ebx, 16         

    mov ecx, ebx        
    dec ecx             
    add eax, ecx        

    mov edx, ebx       
    dec edx            
    not edx             ; edx = ~(align - 1)
                        ; so,. mask like 11110000

    and eax, edx        ; round up to next multiple

    ; eax now = 32

    ; the swap C in main
    ; XOR SWAP (a=5, b=3)
    mov eax, 5          
    mov ebx, 3          

    xor eax, ebx        ; a = a ^ b
    xor ebx, eax        ; b = b ^ (a^b) = original a
    xor eax, ebx        ; a = (a^b) ^ a = original b

    ; swapped: eax=3, ebx=5

    ; C: int count_bits(unsigned int n)
    ; COUNT SET BITS (n=14)

    mov eax, 14         
    xor ecx, ecx        

count_loop:
    test eax, eax       ; while (n != 0)
    jz done_count       ; exit if zero

    mov ebx, eax        
    dec ebx             
    and eax, ebx        ; n = n & (n-1)
                        ; removes lowest set bit

    inc ecx             
    jmp count_loop      

done_count:
    ; ecx = number of set bits (14 -> 3)

    ; from C, #define BITS(val, high, low) (((val) >> (low)) & ((1 << ((high)-(low)+1))- 1))
    ; BITS(0xAB, 5, 3)

    mov eax, 0xAB       ; 10101011
    shr eax, 3          ; shift right -> align bit 3 to LSB

    and eax, 0b111      ; mask 3 bits (width = 5-3+1 = 3)

    ; eax = 5 (0b101)


    mov eax, 1          
    xor ebx, ebx        
    int 0x80            
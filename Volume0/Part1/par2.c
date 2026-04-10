#include <stdio.h>
#include <stdint.h>

// IEEE 754 Float Inspection
void print_float_bits(float f) {
    uint32_t bits = *(uint32_t*)&f;

    uint32_t sign     = (bits >> 31) & 0x1;
    uint32_t exponent = (bits >> 23) & 0xFF;
    uint32_t mantissa = bits & 0x7FFFFF;

    printf("Float: %f\n", f);
    printf("Sign: %u\n", sign);
    printf("Exponent: %u (biased)\n", exponent);
    printf("Mantissa: 0x%06X\n\n", mantissa);
}


// Half Adder

void half_adder(int A, int B, int *sum, int *carry) {
    *sum   = A ^ B;   // XOR
    *carry = A & B;   // AND
}


// Full Adder
void full_adder(int A, int B, int Cin, int *sum, int *Cout) {
    int s1 = A ^ B;
    int c1 = A & B;
    int c2 = s1 & Cin;

    *sum  = s1 ^ Cin;
    *Cout = c1 | c2;
}


// Simple ALU

int alu(int A, int B, char op) {
    switch(op) {
        case '+': return A + B;
        case '-': return A - B;
        case '&': return A & B;
        case '|': return A | B;
        case '^': return A ^ B;
        default:  return 0;
    }
}

int main() {
    // IEEE 754 demo
    float f = 0.15625f;
    print_float_bits(f);

    // Floatingpoint precision issue
    float a = 0.1f, b = 0.2f;
    printf("0.1 + 0.2 = %.17f\n\n", a + b);

    int sum, carry;
    half_adder(1, 1, &sum, &carry);
    printf("Half Adder (1,1): Sum=%d Carry=%d\n", sum, carry);

    int Cout;
    full_adder(1, 1, 1, &sum, &Cout);
    printf("Full Adder (1,1,1): Sum=%d Carry=%d\n", sum, Cout);

    // ALU demo
    printf("ALU 5 + 3 = %d\n", alu(5, 3, '+'));
    printf("ALU 5 & 3 = %d\n", alu(5, 3, '&'));

    return 0;
}
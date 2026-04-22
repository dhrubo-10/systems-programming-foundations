#include <stdio.h>

void half_adder(int A, int B, int *Sum, int *Carry) {
    *Sum   = A ^ B;
    *Carry = A & B;
}

void full_adder(int A, int B, int Cin, int *Sum, int *Cout) {
    *Sum  = A ^ B ^ Cin;
    *Cout = (A & B) | (Cin & (A ^ B));
}

// RIPPLE CARRY ADDER (8-bit) 
int ripple_add(int a, int b) {
    int carry = 0;
    int result = 0;

    for (int i = 0; i < 8; i++) {
        int Ai = (a >> i) & 1;
        int Bi = (b >> i) & 1;

        int sum = Ai ^ Bi ^ carry;
        carry = (Ai & Bi) | (carry & (Ai ^ Bi));

        result |= (sum << i);
    }

    return result;
}

// MULTIPLEXER
int mux2(int A, int B, int S) {
    return (S == 0) ? A : B;
}

// DECODER (2→4) 
void decoder2to4(int A1, int A0) {
    int Y0 = (!A1) & (!A0);
    int Y1 = (!A1) & A0;
    int Y2 = A1 & (!A0);
    int Y3 = A1 & A0;

    printf("Decoder %d%d → [%d %d %d %d]\n", A1, A0, Y3, Y2, Y1, Y0);
}


int main() {
    int S, C;

    printf("Half Adder\n");
    half_adder(1, 1, &S, &C);
    printf("Sum=%d Carry=%d\n\n", S, C);

    printf("Full Adder\n");
    full_adder(1, 1, 1, &S, &C);
    printf("Sum=%d Cout=%d\n\n", S, C);

    printf("Ripple Adder\n");
    int res = ripple_add(5, 3);
    printf("5 + 3 = %d\n\n", res);

    printf("MUX \n");
    printf("MUX(10, 20, S=0) = %d\n", mux2(10, 20, 0));
    printf("MUX(10, 20, S=1) = %d\n\n", mux2(10, 20, 1));

    printf("Decoder \n");
    decoder2to4(0,0);
    decoder2to4(0,1);
    decoder2to4(1,0);
    decoder2to4(1,1);

    return 0;
}
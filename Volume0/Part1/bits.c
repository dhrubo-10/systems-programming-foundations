/**
 * Reference:
 * Bootloader 0
 * x86 Assembly: Volume 0
 * PRE 2 — BITWISE OPERATIONS: Page 5, 
 * Practical Bit Manipulation Patterns
 * */

#include <stdio.h>

// check if bit is set
#define BIT_CHECK(val, n) ((val) & (1 << (n)))

// set bit N
#define BIT_SET(val, n) ((val) | (1 << (n)))

// clear the bit.
#define CLEAR_SET(val, n) ((val) &~ (1 << (n)))

// toggle bit (NOT)
#define BIT_TOGGLE(val, n) ((val) ^ (1 << (n)))

// extract bits [high:low].. as we discussed offsets.
#define BITS(val, high, low) (((val) >> (low)) & ((1 << ((high)-(low)+1))- 1))

/* f.e..: extract bits [5:3] of 0xAB (1010 1011)
 Bits [5:3] = 0b101 = 5 */
// BITS(0xAB, 5, 3)
/*
	(0xAB >> 3) & ((1 << 3) - 1)
	0b00010101 & 0b00000111
	0b00000101 
	= 5
*/

// thn chek pow2
#define IF_POW2(n) ((n) != 0 && ((n) & ((n)-1)) == 0)
// 8 = 1000, 8-1 = 7 = 0111, 1000 & 0111 = 0 means.. power of 2

// round up to nxt pow2
#define ALIGN_UP(val, align) (((val) + (align) - 1) & ~((align) - 1))
// Align 17 to 16: (17 + 15) & ~15 = 32 & 0xFFFFFFF0 = 32
 
// Count set bits (Kernighan's method)
int count_bits(unsigned int n) {
	int count = 0;
	while (n) {
		n &= n - 1;
		 // clear lowest set bit
		count++;
	}
	return count;
}

int main(void) {
    int n = 8;
    int val = 17, align = 16;

    printf("Is %d power of 2? %s\n", n, IF_POW2(n) ? "Yes" : "No");

    printf("Align %d to %d: %d\n", val, align, ALIGN_UP(val, align));

    // swaps
    int a = 5, b = 3;
    a ^= b;
    b ^= a;
    a ^= b;
    printf("Swapped: a=%d, b=%d\n", a, b);

    printf("Set bits in 13: %d\n", count_bits(14));
    // we can do the same thing using this too... "only for GCC"..
    printf("Set bits in 13: %d\n", __builtin_popcount(13));
    printf("Extracted bits: %d\n", BITS(0xAB, 5, 3));

    return 0;
}
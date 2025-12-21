#include <stdio.h>
#include <stdlib.h>
#include "verilated.h"
#include "Vternary_decoder.h"

// Test vectors from the paper's Table II (left side)
// Format: {input_b7_b0, expected_t9_t0}
struct TestVector {
    int input;
    int expected;  // 10 bits: t9...t0
};

// First 14 entries from left table + first 14 from right table
TestVector test_vectors[] = {
    // Left table (b7...b0 input)
    {0b00000000, 0b0100010101},  // 0
    {0b00000001, 0b0101000001},  // 1
    {0b00000010, 0b0101000000},  // 2
    {0b00000011, 0b0101010100},  // 3
    {0b00000100, 0b0101000101},  // 4
    {0b00000101, 0b0101010001},  // 5
    {0b00000110, 0b0101010000},  // 6
    {0b00000111, 0b0101010101},  // 7
    {0b00001000, 0b0001010101},  // 8
    {0b00001001, 0b0001000000},  // 9 (paper shows 000-1001, likely 0b00001001)
    {0b00001010, 0b0100010100},  // 10
    {0b00001011, 0b0001010100},  // 11
    {0b00001100, 0b0100000101},  // 12
    {0b00001101, 0b0001000001},  // 13
    {0b00110000, 0b0100011111} // 11f
};

int main() {
    Vternary_decoder* dut = new Vternary_decoder;
    int errors = 0;
    int num_tests = sizeof(test_vectors) / sizeof(test_vectors[0]);
    
    printf("Testing %d vectors from paper...\n\n", num_tests);
    
    for (int i = 0; i < num_tests; i++) {
        dut->encoded_vals = test_vectors[i].input;
        dut->eval();
        
        int decoded = dut->decoded_vals;
        int expected = test_vectors[i].expected;
        
        if (decoded != expected) {
            printf("FAIL: input=0x%02X (%3d)\n", test_vectors[i].input, test_vectors[i].input);
            printf("      got:      ");
            for (int b = 9; b >= 0; b--) printf("%d", (decoded >> b) & 1);
            printf(" (0x%03X)\n", decoded);
            printf("      expected: ");
            for (int b = 9; b >= 0; b--) printf("%d", (expected >> b) & 1);
            printf(" (0x%03X)\n", expected);
            errors++;
        } else {
            printf("PASS: input=0x%02X -> ", test_vectors[i].input);
            for (int b = 9; b >= 0; b--) printf("%d", (decoded >> b) & 1);
            printf("\n");
        }
    }
    
    printf("\n");
    if (errors == 0) {
        printf("All %d tests PASSED!\n", num_tests);
    } else {
        printf("%d/%d tests FAILED\n", errors, num_tests);
    }
    
    // Also show a few decoded values in trit form
    printf("\nSample decoded trits (t4 t3 t2 t1 t0):\n");
    for (int i = 0; i < 255; i++) {
        dut->encoded_vals = i;
        dut->eval();
        int decoded = dut->decoded_vals;
        printf("  %3d -> ", i);
        for (int t = 4; t >= 0; t--) {
            int trit = (decoded >> (t * 2)) & 0x3;
            if (trit == 0b00) printf(" 0");
            else if (trit == 0b01) printf("+1");
            else if (trit == 0b11) printf("-1");
            else printf("??");
            if (t > 0) printf(" ");
        }
        printf("\n");
    }
    
    delete dut;
    return errors;
}

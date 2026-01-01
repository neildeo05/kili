// Pure software 64x64 ternary matrix-vector product
// Uses the same encoding/decoding scheme as the hardware

#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>
#include <chrono>

using namespace std;

// Matrix/vector dimensions
constexpr int M = 64;  // Matrix rows
constexpr int N = 64;  // Matrix columns (and vector size)

// Trit encoding: -1 → 0b11, 0 → 0b00, +1 → 0b01
constexpr uint8_t TRIT_NEG  = 0b11;
constexpr uint8_t TRIT_ZERO = 0b00;
constexpr uint8_t TRIT_POS  = 0b01;

// Software implementation of the ternary decoder (from ternary_decoder.sv)
// Takes 8-bit encoded value, returns 10-bit decoded value (5 trits × 2 bits each)
uint16_t sw_ternary_decode(uint8_t encoded) {
    // Extract individual bits
    bool b0 = (encoded >> 0) & 1;
    bool b1 = (encoded >> 1) & 1;
    bool b2 = (encoded >> 2) & 1;
    bool b3 = (encoded >> 3) & 1;
    bool b4 = (encoded >> 4) & 1;
    bool b5 = (encoded >> 5) & 1;
    bool b6 = (encoded >> 6) & 1;
    bool b7 = (encoded >> 7) & 1;

    // Intermediate signals (from SystemVerilog)
    bool z0 = (!b6) && (!b1) && b5;
    bool z1 = (!b3) && b2;
    bool z2 = (!b0) && b1;

    bool y1 = b0 && b1;
    bool y4 = !(b0 || (!b4));  // ~(b0 | (~b4))
    bool y2 = (!y4) && (b0 ^ b1) && (!b3) && (!b2);
    bool y3 = b0 && (!b1) && b3;
    bool y5 = (!b0) && (!b1);
    bool y6 = (!b0) && b3;
    bool y9 = !((!b3) || b2);  // ~((~b3) | b2)
    
    bool x2 = z2 && b3 && b2;
    bool y7 = x2 && (!b6);
    bool y8 = b0 && b7 && b6;
    bool y0 = ((!b1) && (!y9)) || (b7 && z0) || y5 || (b1 && y9 && b7);
    bool x0 = y1 && b2;
    bool x1 = (((!b0) || b5) && (!b6) && (!b1) && b2) || (!b3) || x0;

    bool x3 = ((b0 && z0) || z2) && (!b7) && y9;

    bool x4 = (y2 && (!b5)) || z1 || y1;
    bool x5 = (y3 && (!b6) && (!b5)) || (y6 && b2 && b6) || (y5 && y9);

    bool x6 = ((y8 || (b1 && (!b4))) && b2) || (y8 && (!b4) && b3) || y7 || (b0 && z1) || y1;

    bool x7 = ((!b0) && (!b2) && ((!b1) || b3)) || (y2 && b5);

    bool x8 = (((!b7) || (!y9)) && y1) || y7;

    bool x9 = (y6 && (!b2)) || (y4 && (!b3)) || (x2 && b6 && b4) || y5 || (y3 && (!b7) && b6);

    // Output bits
    uint16_t t = 0;
    t |= (x0 || y0) ? (1 << 0) : 0;
    t |= ((b4 && y0) || (b3 && x0)) ? (1 << 1) : 0;
    t |= (x8 || x9) ? (1 << 2) : 0;
    t |= ((b5 && x9) || (b4 && x8)) ? (1 << 3) : 0;
    t |= (x6 || x7) ? (1 << 4) : 0;
    t |= ((b6 && x7) || (b5 && x6)) ? (1 << 5) : 0;
    t |= (x4 || x5) ? (1 << 6) : 0;
    t |= ((b7 && x5) || (b6 && x4)) ? (1 << 7) : 0;
    t |= (x1 || x3) ? (1 << 8) : 0;
    t |= ((b4 && x3) || (b7 && x1)) ? (1 << 9) : 0;

    return t;
}

// Encoder class: builds reverse lookup table from decoder
class TernaryEncoder {
private:
    unordered_map<uint16_t, uint8_t> trit_to_byte;

public:
    TernaryEncoder() {
        // Build reverse lookup from all 256 possible encoded values
        for (int i = 0; i < 256; i++) {
            uint16_t decoded = sw_ternary_decode(i);
            trit_to_byte[decoded] = i;
        }
        // 243 = 3^5 valid trit combinations
    }

    static uint8_t trit_to_bits(int t) {
        return (t == -1) ? TRIT_NEG : (t == 1) ? TRIT_POS : TRIT_ZERO;
    }

    static int bits_to_trit(uint8_t b) {
        return (b == TRIT_NEG) ? -1 : (b == TRIT_POS) ? 1 : 0;
    }

    // Encode array of trits to packed bytes
    // Returns number of bytes used, fills 'out' buffer
    int encode(const int* trits, int num_trits, uint8_t* out) {
        const int TRIT_PACK = 5;  // 5 trits per byte
        int num_bytes = (num_trits + TRIT_PACK - 1) / TRIT_PACK;
        
        for (int byte_idx = 0; byte_idx < num_bytes; byte_idx++) {
            int start = byte_idx * TRIT_PACK;
            int end = min(start + TRIT_PACK, num_trits);
            
            uint16_t packed = 0;
            for (int i = start; i < end; ++i) {
                packed |= trit_to_bits(trits[i]) << (2 * (i - start));
            }
            
            auto it = trit_to_byte.find(packed);
            if (it == trit_to_byte.end()) {
                printf("Failed to encode, packed=0x%x (%d)\n", packed, packed);
                printf("  Trits: [");
                for (int i = start; i < end; ++i) printf("%d ", trits[i]);
                printf("]\n");
                return -1;
            }
            
            out[byte_idx] = it->second;
        }
        return num_bytes;
    }

    // Decode packed bytes back to trits
    void decode(const uint8_t* encoded, int num_bytes, int* trits, int num_trits) {
        const int TRIT_PACK = 5;
        int trit_idx = 0;
        
        for (int byte_idx = 0; byte_idx < num_bytes && trit_idx < num_trits; byte_idx++) {
            uint16_t decoded = sw_ternary_decode(encoded[byte_idx]);
            
            for (int i = 0; i < TRIT_PACK && trit_idx < num_trits; i++) {
                uint8_t bits = (decoded >> (2 * i)) & 0b11;
                trits[trit_idx++] = bits_to_trit(bits);
            }
        }
    }
};

// Software reference: multiply activation by trit
int8_t sw_tmul(uint8_t activation, int trit) {
    int8_t a = (int8_t)activation;
    if (trit == 1)  return a;
    if (trit == -1) return -a;
    return 0;
}

// Compute dot product of ternary weights with activations
int32_t sw_dot_product(const int* trits, const uint8_t* activations, int size) {
    int32_t sum = 0;
    for (int i = 0; i < size; i++) {
        sum += sw_tmul(activations[i], trits[i]);
    }
    return sum;
}

// Matrix-vector product: y = W * x
// W is MxN ternary matrix (stored as encoded bytes)
// x is N-element uint8_t activation vector
// y is M-element int32_t output vector
void matvec_encoded(TernaryEncoder& encoder, 
                    const vector<vector<uint8_t>>& W_encoded,
                    const uint8_t* x, 
                    int32_t* y) {
    const int BYTES_PER_ROW = (N + 4) / 5;  // 5 trits per byte, ceil division
    int row_trits[N];
    
    for (int i = 0; i < M; i++) {
        // Decode row i
        encoder.decode(W_encoded[i].data(), BYTES_PER_ROW, row_trits, N);
        // Compute dot product
        y[i] = sw_dot_product(row_trits, x, N);
    }
}

// Direct (unencoded) matrix-vector product for verification
void matvec_direct(const int W[M][N], const uint8_t* x, int32_t* y) {
    for (int i = 0; i < M; i++) {
        y[i] = sw_dot_product(W[i], x, N);
    }
}

int main() {
    mt19937 gen(42);  // Fixed seed for reproducibility
    uniform_int_distribution<> trit_dist(-1, 1);
    uniform_int_distribution<> act_dist(0, 255);

    printf("=== Pure Software 64x64 Ternary Matrix-Vector Product ===\n\n");

    TernaryEncoder encoder;

    // Generate random ternary weight matrix
    int W[M][N];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            W[i][j] = trit_dist(gen);
        }
    }

    // Encode the weight matrix
    const int BYTES_PER_ROW = (N + 4) / 5;  // 13 bytes for 64 trits
    vector<vector<uint8_t>> W_encoded(M, vector<uint8_t>(BYTES_PER_ROW));
    
    printf("Encoding %dx%d ternary matrix (%d bytes per row)...\n", M, N, BYTES_PER_ROW);
    for (int i = 0; i < M; i++) {
        int result = encoder.encode(W[i], N, W_encoded[i].data());
        if (result < 0) {
            printf("Failed to encode row %d\n", i);
            return 1;
        }
    }
    printf("Matrix encoded successfully.\n\n");

    // Verify encoding by decoding and comparing
    printf("Verifying encode/decode round-trip...\n");
    int decode_errors = 0;
    for (int i = 0; i < M; i++) {
        int decoded[N];
        encoder.decode(W_encoded[i].data(), BYTES_PER_ROW, decoded, N);
        for (int j = 0; j < N; j++) {
            if (decoded[j] != W[i][j]) {
                decode_errors++;
            }
        }
    }
    if (decode_errors == 0) {
        printf("Encode/decode verification PASSED.\n\n");
    } else {
        printf("Encode/decode verification FAILED: %d errors\n\n", decode_errors);
        return 1;
    }

    // Run multiple test vectors
    int num_tests = 100;
    int errors = 0;

    printf("Running %d matrix-vector products...\n", num_tests);

    auto start = chrono::high_resolution_clock::now();

    for (int test = 0; test < num_tests; test++) {
        // Generate random activation vector
        uint8_t x[N];
        for (int j = 0; j < N; j++) {
            x[j] = act_dist(gen);
        }

        // Compute using encoded matrix
        int32_t y_encoded[M];
        matvec_encoded(encoder, W_encoded, x, y_encoded);

        // Compute direct reference
        int32_t y_direct[M];
        matvec_direct(W, x, y_direct);

        // Compare results
        bool test_passed = true;
        for (int i = 0; i < M; i++) {
            if (y_encoded[i] != y_direct[i]) {
                if (test_passed) {
                    printf("Test %d: MISMATCH at row %d: encoded=%d, direct=%d\n",
                           test, i, y_encoded[i], y_direct[i]);
                }
                test_passed = false;
                errors++;
            }
        }

        if (test_passed && test < 5) {
            // Print first few results for sanity check
            printf("Test %d: y[0]=%d, y[1]=%d, y[2]=%d, ..., y[63]=%d\n",
                   test, y_encoded[0], y_encoded[1], y_encoded[2], y_encoded[63]);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    printf("\n=== Results ===\n");
    printf("Tests: %d/%d passed\n", num_tests - (errors > 0 ? 1 : 0), num_tests);
    printf("Total element mismatches: %d\n", errors);
    printf("Time for %d matvecs: %lld us (%.2f us per matvec)\n", 
           num_tests, (long long)duration.count(), (double)duration.count() / num_tests);

    // Print compression stats
    int uncompressed_bits = M * N * 2;  // 2 bits per trit naive
    int compressed_bits = M * BYTES_PER_ROW * 8;
    printf("\nCompression:\n");
    printf("  Uncompressed (2 bits/trit): %d bits = %d bytes\n", 
           uncompressed_bits, uncompressed_bits / 8);
    printf("  Compressed (5 trits/byte):  %d bits = %d bytes\n", 
           compressed_bits, compressed_bits / 8);
    printf("  Compression ratio: %.2fx\n", 
           (double)uncompressed_bits / compressed_bits);

    return errors > 0 ? 1 : 0;
}


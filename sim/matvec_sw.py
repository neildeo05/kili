#!/usr/bin/env python3
"""
Pure Python/NumPy 64x64 ternary matrix-vector product
Uses the same encoding/decoding scheme as the hardware (ternary_decoder.sv)

Matches RTL tile organization:
- 64x64 matrix = 8x8 grid of 8x8 tiles
- Each 8x8 tile = 128 bits (16 bytes)
- Each row of 8 trits = 2 bytes (5 trits per byte, ceil(8/5)=2)
"""

import numpy as np
import time

# Matrix/vector dimensions
M = 64  # Matrix rows
N = 64  # Matrix columns (and vector size)
TILE_SIZE = 8  # 8x8 tiles
TRIT_PACK = 5  # 5 trits per byte

# Derived constants (matching RTL: tmatmul.sv)
NUM_TILES_PER_ROW = (TILE_SIZE + TRIT_PACK - 1) // TRIT_PACK  # ceil(8/5) = 2 bytes per tile row
BYTES_PER_TILE = TILE_SIZE * NUM_TILES_PER_ROW  # 8 * 2 = 16 bytes = 128 bits
TILES_PER_DIM = M // TILE_SIZE  # 64/8 = 8 tiles per dimension

# Trit encoding: -1 → 0b11, 0 → 0b00, +1 → 0b01
TRIT_NEG = 0b11
TRIT_ZERO = 0b00
TRIT_POS = 0b01


def sw_ternary_decode(encoded: int) -> int:
    """
    Software implementation of the ternary decoder (from ternary_decoder.sv)
    Takes 8-bit encoded value, returns 10-bit decoded value (5 trits × 2 bits each)
    """
    # Extract individual bits
    b0 = (encoded >> 0) & 1
    b1 = (encoded >> 1) & 1
    b2 = (encoded >> 2) & 1
    b3 = (encoded >> 3) & 1
    b4 = (encoded >> 4) & 1
    b5 = (encoded >> 5) & 1
    b6 = (encoded >> 6) & 1
    b7 = (encoded >> 7) & 1

    # Intermediate signals (from SystemVerilog)
    z0 = (not b6) and (not b1) and b5
    z1 = (not b3) and b2
    z2 = (not b0) and b1

    y1 = b0 and b1
    y4 = not (b0 or (not b4))  # ~(b0 | (~b4))
    y2 = (not y4) and (b0 ^ b1) and (not b3) and (not b2)
    y3 = b0 and (not b1) and b3
    y5 = (not b0) and (not b1)
    y6 = (not b0) and b3
    y9 = not ((not b3) or b2)  # ~((~b3) | b2)

    x2 = z2 and b3 and b2
    y7 = x2 and (not b6)
    y8 = b0 and b7 and b6
    y0 = ((not b1) and (not y9)) or (b7 and z0) or y5 or (b1 and y9 and b7)
    x0 = y1 and b2
    x1 = (((not b0) or b5) and (not b6) and (not b1) and b2) or (not b3) or x0

    x3 = ((b0 and z0) or z2) and (not b7) and y9

    x4 = (y2 and (not b5)) or z1 or y1
    x5 = (y3 and (not b6) and (not b5)) or (y6 and b2 and b6) or (y5 and y9)

    x6 = ((y8 or (b1 and (not b4))) and b2) or (y8 and (not b4) and b3) or y7 or (b0 and z1) or y1

    x7 = ((not b0) and (not b2) and ((not b1) or b3)) or (y2 and b5)

    x8 = (((not b7) or (not y9)) and y1) or y7

    x9 = (y6 and (not b2)) or (y4 and (not b3)) or (x2 and b6 and b4) or y5 or (y3 and (not b7) and b6)

    # Output bits
    t = 0
    t |= (1 << 0) if (x0 or y0) else 0
    t |= (1 << 1) if ((b4 and y0) or (b3 and x0)) else 0
    t |= (1 << 2) if (x8 or x9) else 0
    t |= (1 << 3) if ((b5 and x9) or (b4 and x8)) else 0
    t |= (1 << 4) if (x6 or x7) else 0
    t |= (1 << 5) if ((b6 and x7) or (b5 and x6)) else 0
    t |= (1 << 6) if (x4 or x5) else 0
    t |= (1 << 7) if ((b7 and x5) or (b6 and x4)) else 0
    t |= (1 << 8) if (x1 or x3) else 0
    t |= (1 << 9) if ((b4 and x3) or (b7 and x1)) else 0

    return t


class TernaryEncoder:
    """Encoder class: builds reverse lookup table from decoder"""

    def __init__(self):
        # Build reverse lookup from all 256 possible encoded values
        self.trit_to_byte = {}
        for i in range(256):
            decoded = sw_ternary_decode(i)
            self.trit_to_byte[decoded] = i
        # 243 = 3^5 valid trit combinations

    @staticmethod
    def trit_to_bits(t: int) -> int:
        if t == -1:
            return TRIT_NEG
        elif t == 1:
            return TRIT_POS
        else:
            return TRIT_ZERO

    @staticmethod
    def bits_to_trit(b: int) -> int:
        if b == TRIT_NEG:
            return -1
        elif b == TRIT_POS:
            return 1
        else:
            return 0

    def encode_row(self, trits: np.ndarray) -> np.ndarray:
        """Encode a row of trits (e.g., 8 trits) to packed bytes"""
        num_trits = len(trits)
        num_bytes = (num_trits + TRIT_PACK - 1) // TRIT_PACK
        out = np.zeros(num_bytes, dtype=np.uint8)

        for byte_idx in range(num_bytes):
            start = byte_idx * TRIT_PACK
            end = min(start + TRIT_PACK, num_trits)

            packed = 0
            for i in range(start, end):
                packed |= self.trit_to_bits(int(trits[i])) << (2 * (i - start))

            if packed not in self.trit_to_byte:
                raise ValueError(f"Failed to encode, packed=0x{packed:x}")

            out[byte_idx] = self.trit_to_byte[packed]

        return out

    def decode_row(self, encoded: np.ndarray, num_trits: int) -> np.ndarray:
        """Decode packed bytes back to trits"""
        trits = np.zeros(num_trits, dtype=np.int8)
        trit_idx = 0

        for byte_idx in range(len(encoded)):
            if trit_idx >= num_trits:
                break
            decoded = sw_ternary_decode(int(encoded[byte_idx]))

            for i in range(TRIT_PACK):
                if trit_idx >= num_trits:
                    break
                bits = (decoded >> (2 * i)) & 0b11
                trits[trit_idx] = self.bits_to_trit(bits)
                trit_idx += 1

        return trits

    def encode_tile(self, tile: np.ndarray) -> np.ndarray:
        """
        Encode an 8x8 tile to 128 bits (16 bytes)
        Matches RTL: weight_fifo_in is [TILE_SIZE-1:0][NUM_TILES-1:0][7:0]
        = [8 rows][2 bytes][8 bits]
        """
        assert tile.shape == (TILE_SIZE, TILE_SIZE), f"Expected {TILE_SIZE}x{TILE_SIZE} tile"
        out = np.zeros((TILE_SIZE, NUM_TILES_PER_ROW), dtype=np.uint8)
        
        for row in range(TILE_SIZE):
            out[row] = self.encode_row(tile[row])
        
        return out  # Shape: (8, 2) = 16 bytes = 128 bits

    def decode_tile(self, encoded: np.ndarray) -> np.ndarray:
        """Decode 128-bit encoded tile back to 8x8 trits"""
        assert encoded.shape == (TILE_SIZE, NUM_TILES_PER_ROW), f"Expected ({TILE_SIZE}, {NUM_TILES_PER_ROW}) encoded tile"
        tile = np.zeros((TILE_SIZE, TILE_SIZE), dtype=np.int8)
        
        for row in range(TILE_SIZE):
            tile[row] = self.decode_row(encoded[row], TILE_SIZE)
        
        return tile


def encode_matrix_as_tiles(encoder: TernaryEncoder, W: np.ndarray):
    """
    Encode 64x64 matrix as 8x8 grid of 128-bit tiles
    Returns: (8, 8, 8, 2) array = 64 tiles, each tile is (8, 2) bytes
    
    Tile layout matches RTL local_memory: 64 tiles stored linearly
    """
    assert W.shape == (M, N), f"Expected {M}x{N} matrix"
    
    # Shape: (tiles_row, tiles_col, tile_rows, tile_bytes)
    W_tiles = np.zeros((TILES_PER_DIM, TILES_PER_DIM, TILE_SIZE, NUM_TILES_PER_ROW), dtype=np.uint8)
    
    for ti in range(TILES_PER_DIM):
        for tj in range(TILES_PER_DIM):
            # Extract 8x8 tile from matrix
            row_start = ti * TILE_SIZE
            col_start = tj * TILE_SIZE
            tile = W[row_start:row_start+TILE_SIZE, col_start:col_start+TILE_SIZE]
            
            # Encode tile to 128 bits
            W_tiles[ti, tj] = encoder.encode_tile(tile)
    
    return W_tiles


def decode_matrix_from_tiles(encoder: TernaryEncoder, W_tiles: np.ndarray) -> np.ndarray:
    """Decode 8x8 grid of tiles back to 64x64 matrix"""
    W = np.zeros((M, N), dtype=np.int8)
    
    for ti in range(TILES_PER_DIM):
        for tj in range(TILES_PER_DIM):
            tile = encoder.decode_tile(W_tiles[ti, tj])
            row_start = ti * TILE_SIZE
            col_start = tj * TILE_SIZE
            W[row_start:row_start+TILE_SIZE, col_start:col_start+TILE_SIZE] = tile
    
    return W


def tile_to_128bit(tile_encoded: np.ndarray) -> int:
    """Convert (8, 2) encoded tile to 128-bit integer (for display)"""
    val = 0
    for row in range(TILE_SIZE):
        for byte_idx in range(NUM_TILES_PER_ROW):
            bit_offset = (row * NUM_TILES_PER_ROW + byte_idx) * 8
            val |= int(tile_encoded[row, byte_idx]) << bit_offset
    return val


def tile_from_128bit(val: int) -> np.ndarray:
    """Convert 128-bit integer to (8, 2) encoded tile array"""
    tile_encoded = np.zeros((TILE_SIZE, NUM_TILES_PER_ROW), dtype=np.uint8)
    for row in range(TILE_SIZE):
        for byte_idx in range(NUM_TILES_PER_ROW):
            bit_offset = (row * NUM_TILES_PER_ROW + byte_idx) * 8
            tile_encoded[row, byte_idx] = (val >> bit_offset) & 0xFF
    return tile_encoded


def main():
    np.random.seed(42)  # Fixed seed for reproducibility

    # print("=== Pure Python/NumPy 64x64 Ternary Matrix-Vector Product ===")
    # print(f"    (RTL-compatible 128-bit tile organization)\n")

    encoder = TernaryEncoder()
    # print(f"Built lookup table with {len(encoder.trit_to_byte)} entries (expected 243 = 3^5)")
    # print(f"Tile organization: {TILE_SIZE}x{TILE_SIZE} tiles, {NUM_TILES_PER_ROW} bytes/row, {BYTES_PER_TILE} bytes/tile = 128 bits\n")

    # # Generate random ternary weight matrix
    # W = np.random.randint(-1, 2, size=(M, N), dtype=np.int8)

    # print(f"Generated {M}x{N} ternary weight matrix W")
    # print(f"  W[0:8,0:8] = {W[0:8,0:8]}  (first tile)")
    # print()

    # # Encode the weight matrix as tiles (matching RTL)
    # print(f"Encoding {M}x{N} matrix as {TILES_PER_DIM}x{TILES_PER_DIM} grid of {TILE_SIZE}x{TILE_SIZE} tiles...")
    # W_tiles = encode_matrix_as_tiles(encoder, W)
    # print(f"  W_tiles shape: {W_tiles.shape} = ({TILES_PER_DIM} tile_rows, {TILES_PER_DIM} tile_cols, {TILE_SIZE} rows, {NUM_TILES_PER_ROW} bytes)")
    # print(f"  Total size: {W_tiles.size} bytes = {W_tiles.size * 8} bits")
    # print(f"  Per tile: {BYTES_PER_TILE} bytes = 128 bits")
    # print()

    # # Show first tile encoding
    # for i in range(TILES_PER_DIM):
    #   for j in range(TILES_PER_DIM):
    #     print(f"Tile {i},{j}: W[{i*TILE_SIZE}:{i*TILE_SIZE+TILE_SIZE},{j*TILE_SIZE}:{j*TILE_SIZE+TILE_SIZE}] encoded:")
    #     tile = W_tiles[i, j]
    #     # print(f"  Tile bytes (8 rows x 2 bytes):")
    #     # for row in range(TILE_SIZE):
    #         # print(f"    Row {row}: [{tile[row, 0]:3d}, {tile[row, 1]:3d}] = 0x{tile[row, 0]:02x}{tile[row, 1]:02x}")
    #     print(f"  As 128-bit value: 0x{tile_to_128bit(tile):032x}")
    #     print()

    second_tiles = []
    for i in range(64):
      second_tiles.append(tile_from_128bit(i))

    second_tiles = (np.array(second_tiles).reshape(8,8,8,2))
    W_tiles = second_tiles

    # Verify encoding by decoding and comparing
    W = decode_matrix_from_tiles(encoder, W_tiles)
    # if np.array_equal(W, W_decoded):
    #     print("Encode/decode verification PASSED.\n")
    # else:
    #     decode_errors = np.sum(W != W_decoded)
    #     print(f"Encode/decode verification FAILED: {decode_errors} errors\n")
    #     return 1

    print(f"W_decoded = {W}")

    # Run multiple test vectors
    num_tests = 1
    errors = 0

    print(f"Running {num_tests} matrix-vector products using NumPy...\n")

    start = time.perf_counter()

    for test in range(num_tests):
        # Generate random activation vector (uint8)
        # x = np.random.randint(0, 256, size=M*N, dtype=np.uint8)
        x = np.ones(N, dtype=np.uint8) * 5


        # ============================================================
        # ACTUAL NumPy GEMV: y = W @ x
        # W is (M, N) ternary matrix with values in {-1, 0, +1}
        # x is (N,) uint8 activation vector with values in [0, 255]
        # y is (M,) uint8 output vector (masked to 8 bits)
        # ============================================================
        W_int = W.astype(np.int32)
        x_int = x.astype(np.int32)
        y_numpy = (W_int @ x_int) & 0xFF  # Mask to 8 bits (no overflow)
        for i in range(M):
            if i % 8 == 0: print()
            print(f"y[{i}] = {hex(y_numpy[i])}")

        # Compute using decoded tiles (simulating RTL flow)
        W_from_tiles = decode_matrix_from_tiles(encoder, W_tiles)
        y_tiles = (W_from_tiles.astype(np.int32) @ x_int) & 0xFF  # Mask to 8 bits

        # Compare results
        if not np.array_equal(y_numpy, y_tiles):
            mismatch_idx = np.where(y_numpy != y_tiles)[0]
            print(f"Test {test}: MISMATCH at rows {mismatch_idx[:5]}...")
            errors += len(mismatch_idx)

    end = time.perf_counter()
    duration_us = (end - start) * 1e6

    print(f"\n=== Results ===")
    print(f"Tests: {num_tests - (1 if errors > 0 else 0)}/{num_tests} passed")
    print(f"Total element mismatches: {errors}")
    print(f"Time for {num_tests} matvecs: {duration_us:.0f} us ({duration_us/num_tests:.2f} us per matvec)")

    # Print storage stats (matching RTL)
    total_tiles = TILES_PER_DIM * TILES_PER_DIM
    total_bits = total_tiles * 128
    print(f"\nStorage (RTL-compatible):")
    print(f"  {total_tiles} tiles × 128 bits = {total_bits} bits = {total_bits // 8} bytes")
    print(f"  Naive (2 bits/trit): {M * N * 2} bits = {M * N * 2 // 8} bytes")
    print(f"  Note: No compression at tile level (8 trits → 2 bytes = 16 bits)")

    return 1 if errors > 0 else 0


if __name__ == "__main__":
    exit(main())

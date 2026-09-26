"""Functional model of the fixed-size accelerator in hdl/ (standard library only).

tmatmul(weight_fifo_in, activations_in) models one complete tile operation:
    weights:     8 rows x 2 encoded bytes, 16 flat bytes, or a 128-bit integer
    activations: 8 byte values, or a 64-bit integer
    result:      8 unsigned byte values, in dot_out lane order

Array index zero is the least-significant lane of each HDL packed dimension.
Weight byte 2*r encodes columns 0..4 of row r; byte 2*r+1 encodes columns
5..7, with its final two decoded trits ignored. Encoding is the Boolean decoder
in ternary_decoder.sv, NOT ordinary base-3 encoding. All arithmetic wraps modulo
256, including negation of -128. Signed activation values (-128..127) are also
accepted as two's-complement bytes. Interpret an output b as b if b < 128 else
b - 256 when signed results are needed.

There are no clocks, valid/ready signals, FIFOs, or simulated memory accesses:
a call supplies valid operands and returns the completed result.

Example:
    >>> weights = encode_tile([[int(r == c) for c in range(8)] for r in range(8)])
    >>> tmatmul(weight_fifo_in=weights, activations_in=[1, 2, 3, 4, 5, 6, 7, -1])
    [1, 2, 3, 4, 5, 6, 7, 255]

Run ``python3 kili.py`` for functional self-tests.
"""

from operator import index

TILE_SIZE = 8
TRIT_PACK = 5
BYTES_PER_ROW = 2
BYTES_PER_TILE = TILE_SIZE * BYTES_PER_ROW


def _integer(value, low, high, name):
    """Validate integers without silently truncating floats or oversized words."""
    try:
        value = index(value)
    except TypeError:
        raise ValueError(f"{name} must be an integer") from None
    if not low <= value <= high:
        raise ValueError(f"{name} must be in [{low}, {high}]")
    return value


def _decode_bits(encoded):
    """Direct translation of hdl/ternary_decoder.sv; return five 2-bit trits."""
    b0, b1, b2, b3, b4, b5, b6, b7 = (
        bool(encoded & (1 << i)) for i in range(8)
    )
    z0 = (not b6) and (not b1) and b5
    z1 = (not b3) and b2
    z2 = (not b0) and b1
    y1 = b0 and b1
    y4 = not (b0 or (not b4))
    y2 = (not y4) and (b0 ^ b1) and (not b3) and (not b2)
    y3 = b0 and (not b1) and b3
    y5 = (not b0) and (not b1)
    y6 = (not b0) and b3
    y9 = not ((not b3) or b2)
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
    bits = (
        x0 or y0, (b4 and y0) or (b3 and x0),
        x8 or x9, (b5 and x9) or (b4 and x8),
        x6 or x7, (b6 and x7) or (b5 and x6),
        x4 or x5, (b7 and x5) or (b6 and x4),
        x1 or x3, (b4 and x3) or (b7 and x1),
    )
    return sum(int(bit) << i for i, bit in enumerate(bits))


# Include all 256 byte patterns, including aliases of the 243 trit combinations.
# Like sim/matvec_sw.py, the encoder chooses the last byte for each combination.
_DECODE = tuple(
    tuple((0, 1, 0, -1)[(_decode_bits(byte) >> (2 * i)) & 3]
          for i in range(TRIT_PACK))
    for byte in range(256)
)
_ENCODE = {trits: byte for byte, trits in enumerate(_DECODE)}


def decode_byte(encoded):
    """Return five signed trits in lane order for an encoded byte (0..255)."""
    return _DECODE[_integer(encoded, 0, 255, "encoded byte")]


def _lanes(value, count, name, *, signed=False, shape=None):
    """Unpack a little-endian HDL word or validate flat/nested byte lanes."""
    try:
        word = index(value)
    except TypeError:
        try:
            lanes = list(value)
            if shape is not None and len(lanes) == shape[0]:
                rows = [list(row) for row in lanes]
                if any(len(row) != shape[1] for row in rows):
                    raise ValueError(f"{name} must have shape {shape}")
                lanes = [byte for row in rows for byte in row]
        except TypeError:
            raise ValueError(f"{name} must be a packed integer or byte sequence") from None
        if len(lanes) != count:
            raise ValueError(f"{name} must contain {count} bytes")
        low = -128 if signed else 0
        return [_integer(byte, low, 255, f"{name} lane") & 255 for byte in lanes]
    word = _integer(word, 0, (1 << (8 * count)) - 1, name)
    return [(word >> (8 * i)) & 255 for i in range(count)]


def decode_tile(weight_fifo_in):
    """Decode a hardware-format weight tile into an 8x8 list of signed trits."""
    packed = _lanes(weight_fifo_in, BYTES_PER_TILE, "weight_fifo_in",
                    shape=(TILE_SIZE, BYTES_PER_ROW))
    return [list(_DECODE[packed[2 * r]] + _DECODE[packed[2 * r + 1]][:3])
            for r in range(TILE_SIZE)]


def encode_tile(weights):
    """Encode an 8x8 {-1, 0, +1} tile into 16 bytes in HDL lane order.

    The unused two trits in each row's second byte are padded with zeros.
    Use int.from_bytes(result, 'little') to obtain the 128-bit memory word.
    """
    try:
        rows = [list(row) for row in weights]
    except TypeError:
        raise ValueError("weights must be an 8x8 ternary matrix") from None
    if len(rows) != TILE_SIZE or any(len(row) != TILE_SIZE for row in rows):
        raise ValueError("weights must be an 8x8 ternary matrix")
    encoded = []
    for row in rows:
        row = tuple(_integer(trit, -1, 1, "weight trit") for trit in row)
        encoded.extend((_ENCODE[row[:5]], _ENCODE[row[5:] + (0, 0)]))
    return bytes(encoded)


def tmatmul(weight_fifo_in, activations_in):
    """Return dot_out for one packed weight tile and eight activation bytes.

    Argument names match hdl/tmatmul.sv. Each result lane is the corresponding
    weight row dotted with activations_in, modulo 256. The HDL wraps at every
    multiply/add; wrapping the final sum is arithmetically equivalent.
    """
    weights = decode_tile(weight_fifo_in)
    activations = _lanes(activations_in, TILE_SIZE, "activations_in", signed=True)
    return [sum(w * a for w, a in zip(row, activations)) & 255 for row in weights]


# Architecture-document spelling, with the same arguments and return type.
TMatmul = tmatmul


def _self_test():
    """Check packing, byte overflow, and lane ordering."""
    import doctest
    import itertools
    import random

    assert doctest.testmod().failed == 0
    assert len(_ENCODE) == 3 ** TRIT_PACK
    assert decode_byte(0) == (1, 1, 1, 0, 1)
    for trits in itertools.product((-1, 0, 1), repeat=TRIT_PACK):
        weights = [list(trits) + [1, -1, 0] for _ in range(TILE_SIZE)]
        assert decode_tile(encode_tile(weights)) == weights

    rng = random.Random(42)
    for _ in range(200):
        weights = [[rng.randrange(-1, 2) for _ in range(8)] for _ in range(8)]
        activations = [rng.randrange(-128, 256) for _ in range(8)]
        packed = encode_tile(weights)
        expected = [sum(w * a for w, a in zip(row, activations)) & 255
                    for row in weights]
        assert tmatmul(packed, activations) == expected
        assert tmatmul([packed[i:i+2] for i in range(0, 16, 2)], activations) == expected
        assert tmatmul(int.from_bytes(packed, "little"),
                       int.from_bytes(bytes(a & 255 for a in activations), "little")) == expected

    # Basis vectors expose transposed rows and reversed packed byte/trit order.
    packed = bytes(range(16))
    decoded = decode_tile(packed)
    for column in range(8):
        activations = [int(i == column) for i in range(8)]
        assert tmatmul(packed, activations) == [row[column] & 255 for row in decoded]
    assert tmatmul(encode_tile([[-1] * 8] * 8), [-128] + [0] * 7) == [128] * 8
    assert tmatmul(encode_tile([[1] * 8] * 8), [255] * 8) == [248] * 8
    # Changing the padding trits must not affect any result.
    first = _ENCODE[(1, -1, 0, 1, -1)]
    for padding in itertools.product((-1, 0, 1), repeat=2):
        second = _ENCODE[(1, 0, -1) + padding]
        assert decode_tile(bytes([first, second] * 8)) == [[1, -1, 0, 1, -1, 1, 0, -1]] * 8

    for weights_in, acts_in in ((bytes(15), [0] * 8), (bytes(16), [0] * 7),
                               (-1, 0), (1 << 128, 0), (0, 1 << 64),
                               (0, [256] * 8), (0, [-129] * 8),
                               (0, [1.5] * 8), ([[0]] * 8, [0] * 8)):
        try:
            tmatmul(weights_in, acts_in)
        except ValueError:
            pass
        else:
            raise AssertionError("invalid operands accepted")
    print("Passed: all 243 trit combinations, 200 random tiles, packing/overflow, "
          "padding, and invalid inputs.")


if __name__ == "__main__":
    _self_test()

from random import Random
from kili import encode_tile, tmatmul

rng = Random(42)
n = 8
weights = [[rng.choice([-1, 0, 1]) for _ in range(n)] for _ in range(n)]
activations = [[rng.randint(-128, 127) for _ in range(n)] for _ in range(n)]

packed_weights = encode_tile(weights)
result = [[0] * n for _ in range(n)]

# The accelerator processes one activation column per call.
for col in range(n):
    column = [activations[row][col] for row in range(n)]
    output = tmatmul(packed_weights, column)
    for row in range(n):
        result[row][col] = output[row]

# Reference matrix multiplication, with hardware's 8-bit wrapping.
expected = [
    [sum(weights[r][k] * activations[k][c] for k in range(n)) & 0xFF
    for c in range(n)]
    for r in range(n)
]

assert result == expected, "Matrix multiplication mismatch"
print("PASS: weights @ activations (results modulo 256)")
for row in result:
    print(row)
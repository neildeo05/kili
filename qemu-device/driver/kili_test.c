/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Guest example: an 8 -> 8 -> 8 ternary network, TMatmul -> ReLU -> TMatmul. */
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "kili-uapi.h"
#include "kili-core.h"

static uint8_t encode_five(const int8_t trits[5])
{
    uint16_t decoded = 0;
    unsigned i;

    for (i = 0; i < 5; i++) {
        unsigned bits = trits[i] < 0 ? 3 : trits[i] > 0 ? 1 : 0;
        decoded |= bits << (2 * i);
    }
    for (i = 0; i < 256; i++) {
        if (kili_decode_byte(i) == decoded) {
            return i;
        }
    }
    fprintf(stderr, "Cannot encode trits\n");
    exit(EXIT_FAILURE);
}

static void encode_tile(const int8_t tile[8][8], uint8_t packed[16])
{
    unsigned row;

    for (row = 0; row < 8; row++) {
        int8_t end[5] = { tile[row][5], tile[row][6], tile[row][7], 0, 0 };
        packed[2 * row] = encode_five(tile[row]);
        packed[2 * row + 1] = encode_five(end);
    }
}

static void run(int fd, struct kili_job *job)
{
    if (fd < 0) {
        /* Only --self-test uses the CPU reference instead of the device. */
        kili_tmatmul(job->weights, job->activations, job->output);
    } else if (ioctl(fd, KILI_IOCTL_RUN, job) < 0) {
        perror("KILI_IOCTL_RUN");
        exit(EXIT_FAILURE);
    }
}

static int signed_byte(uint8_t value)
{
    return value < 128 ? value : (int)value - 256;
}

static void print_vector(const char *label, const uint8_t values[8])
{
    unsigned i;

    printf("%s:", label);
    for (i = 0; i < 8; i++) {
        printf(" %d", signed_byte(values[i]));
    }
    putchar('\n');
}

static void network_test(int fd)
{
    /* Two fixed ternary weight matrices; no biases or training. */
    static const int8_t weights[2][8][8] = {
        {
            { 1,  0, -1,  0,  1,  0,  0,  1},
            {-1,  1,  0,  1,  0,  0,  1,  0},
            { 0, -1,  1,  0,  0,  1,  0,  0},
            { 1,  1,  0,  0, -1,  0,  0,  0},
            { 0,  0,  1, -1,  0,  0,  1,  0},
            { 0,  1,  0,  0,  1,  1,  0,  0},
            { 1,  0,  0,  1,  0, -1,  0,  0},
            { 0,  0, -1,  0,  0,  0,  0,  1},
        },
        {
            { 1,  0, -1,  0,  1,  0,  0,  1},
            {-1,  1,  0,  0,  0,  1,  0,  0},
            { 0,  0,  1,  1, -1,  0,  0,  0},
            { 1, -1,  1,  0,  0,  0,  1,  0},
            { 0,  0,  0,  1,  1,  0,  0, -1},
            { 0,  1,  0,  0,  0, -1,  1,  1},
            {-1,  0,  0,  0,  1,  0, -1,  0},
            { 0,  0, -1,  0,  0,  1,  0,  1},
        },
    };
    static const int8_t input[8] = {1, -2, 3, -4, 2, -1, 0, 4};
    struct kili_job job = { 0 };
    int reference[8];
    unsigned layer, row, col;

    for (row = 0; row < 8; row++) {
        job.activations[row] = (uint8_t)input[row];
        reference[row] = input[row];
    }
    print_vector("Input", job.activations);
    for (layer = 0; layer < 2; layer++) {
        int expected[8];

        /* Independent arithmetic reference, using the unpacked weights. */
        for (row = 0; row < 8; row++) {
            int sum = 0;
            for (col = 0; col < 8; col++) {
                sum += weights[layer][row][col] * reference[col];
            }
            expected[row] = signed_byte((uint8_t)sum);
        }
        encode_tile(weights[layer], job.weights);
        run(fd, &job); /* One device TMatmul per layer. */
        for (row = 0; row < 8; row++) {
            if (signed_byte(job.output[row]) != expected[row]) {
                fprintf(stderr, "Layer %u mismatch at [%u]: got %d, expected %d\n",
                        layer + 1, row, signed_byte(job.output[row]), expected[row]);
                exit(EXIT_FAILURE);
            }
        }
        if (layer == 0) {
            print_vector("Layer 1", job.output);
            /* CPU-side ReLU interprets the wrapped bytes as signed int8. */
            for (row = 0; row < 8; row++) {
                job.activations[row] = job.output[row] < 128 ? job.output[row] : 0;
                reference[row] = expected[row] > 0 ? expected[row] : 0;
                if (job.activations[row] != reference[row]) {
                    fprintf(stderr, "ReLU mismatch at [%u]\n", row);
                    exit(EXIT_FAILURE);
                }
            }
            print_vector("ReLU", job.activations);
        } else {
            print_vector("Output", job.output);
        }
    }
    puts("PASS: TMatmul -> ReLU -> TMatmul (8 -> 8 -> 8)");
}

int main(int argc, char **argv)
{
    const char *path = argc > 1 ? argv[1] : "/dev/kili0";
    int fd = -1;

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [/dev/kili0 | --self-test]\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (strcmp(path, "--self-test")) {
        fd = open(path, O_RDWR);
        if (fd < 0) {
            perror(path);
            return EXIT_FAILURE;
        }
    }
    network_test(fd);
    if (fd >= 0) {
        close(fd);
    } else {
        puts("Software self-test only; no device was accessed.");
    }
    return EXIT_SUCCESS;
}

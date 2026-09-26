/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Destructive test modes belong in the diskless test VM, not a busy device. */
#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <glob.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "../driver/kili-uapi.h"
#include "../kili-regs.h"

#define CALLERS 32
#define ROUNDS 64
#define DEPTH 16

static pthread_barrier_t start;
static int device_fd;
static enum { NORMAL, TIMEOUT, UNBIND } mode;

struct caller {
    unsigned id;
    int failed;
};

static void *submit_many(void *opaque)
{
    /* Identity matrix, packed using the Python gold model's encoder. */
    static const uint8_t identity[16] = {
        0xa9, 0xf9, 0x59, 0xf9, 0xc9, 0xf9, 0x19, 0xf9,
        0x29, 0xf9, 0xf9, 0xa9, 0xf9, 0x59, 0xf9, 0xc9,
    };
    struct caller *caller = opaque;
    unsigned round, lane;

    pthread_barrier_wait(&start);
    for (round = 0; round < (mode == NORMAL ? ROUNDS : 1); round++) {
        struct kili_job job = { 0 };
        int ret;

        memcpy(job.weights, identity, sizeof(identity));
        for (lane = 0; lane < 8; lane++)
            job.activations[lane] = caller->id * 7 + round * 13 + lane * 31;
        ret = ioctl(device_fd, KILI_IOCTL_RUN, &job);
        if (mode != NORMAL) {
            if (ret != -1 || (mode == UNBIND ? errno != ENODEV :
                              (errno != EIO && errno != ETIMEDOUT)))
                caller->failed = 1;
            return NULL;
        }
        if (ret || memcmp(job.output, job.activations, 8)) {
            fprintf(stderr, "Caller %u round %u: ret=%d errno=%d or wrong output\n",
                    caller->id, round, ret, errno);
            caller->failed = 1;
            return NULL;
        }
    }
    return NULL;
}

static uint32_t reg_read(volatile uint32_t *bar, unsigned offset)
{
    return bar[offset / 4];
}

static void vector_mask(volatile uint32_t *bar, uint32_t value)
{
    bar[(KILI_MSIX_TABLE + 12) / 4] = value;
    __sync_synchronize();
    (void)reg_read(bar, KILI_MSIX_TABLE + 12);
}

int main(int argc, char **argv)
{
    glob_t resources;
    pthread_t threads[CALLERS];
    struct caller callers[CALLERS] = { 0 };
    volatile uint32_t *bar;
    uint32_t original_mask, initial_tail;
    int resource_fd, failed = 0;
    unsigned i;

    if (argc == 2 && !strcmp(argv[1], "--timeout"))
        mode = TIMEOUT;
    else if (argc == 2 && !strcmp(argv[1], "--unbind"))
        mode = UNBIND;
    else if (argc != 1) {
        fprintf(stderr, "Usage: %s [--timeout | --unbind]\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (glob("/sys/bus/pci/drivers/kili_drv/????:??:??.?/resource0", 0, NULL,
             &resources) || resources.gl_pathc != 1) {
        fprintf(stderr, "Expected exactly one bound Kili device\n");
        return EXIT_FAILURE;
    }
    resource_fd = open(resources.gl_pathv[0], O_RDWR | O_SYNC);
    device_fd = open("/dev/kili0", O_RDWR);
    if (resource_fd < 0 || device_fd < 0) {
        perror("open device/resource0");
        return EXIT_FAILURE;
    }
    bar = mmap(NULL, KILI_BAR_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
               resource_fd, 0);
    if (bar == MAP_FAILED) {
        perror("mmap BAR0");
        return EXIT_FAILURE;
    }
    if (reg_read(bar, KILI_REG_SQ_SIZE) != DEPTH ||
        reg_read(bar, KILI_REG_SQ_TAIL) != reg_read(bar, KILI_REG_CQ_HEAD)) {
        fprintf(stderr, "Expected an idle device with a 16-entry queue\n");
        return EXIT_FAILURE;
    }
    initial_tail = reg_read(bar, KILI_REG_SQ_TAIL);
    original_mask = reg_read(bar, KILI_MSIX_TABLE + 12);
    if (pthread_barrier_init(&start, NULL, CALLERS + 1))
        return EXIT_FAILURE;
    vector_mask(bar, 1);
    for (i = 0; i < CALLERS; i++) {
        callers[i].id = i;
        if (pthread_create(&threads[i], NULL, submit_many, &callers[i])) {
            vector_mask(bar, original_mask);
            return EXIT_FAILURE;
        }
    }
    pthread_barrier_wait(&start);
    /* Less than the driver's 5-second timeout, even when it is serialized. */
    for (i = 0; i < 1000; i++) {
        if (reg_read(bar, KILI_REG_SQ_TAIL) - initial_tail == DEPTH)
            break;
        usleep(1000);
    }
    usleep(20000);
    if (reg_read(bar, KILI_REG_SQ_TAIL) - initial_tail != DEPTH ||
        reg_read(bar, KILI_REG_CQ_TAIL) - initial_tail != DEPTH ||
        reg_read(bar, KILI_REG_CQ_HEAD) != initial_tail) {
        fprintf(stderr, "Did not hold exactly 16 requests with MSI-X masked\n");
        failed = 1;
    } else {
        puts("PASS: 16 outstanding requests; extra callers wait for space");
    }
    if (mode == NORMAL || failed) {
        vector_mask(bar, original_mask);
    } else if (mode == UNBIND) {
        char bdf[13];
        const char *path = resources.gl_pathv[0];
        const char *device = path + strlen("/sys/bus/pci/drivers/kili_drv/");
        int fd = open("/sys/bus/pci/drivers/kili_drv/unbind", O_WRONLY);

        memcpy(bdf, device, 12);
        bdf[12] = '\0';
        if (fd < 0 || write(fd, bdf, 12) != 12) {
            perror("unbind");
            vector_mask(bar, original_mask);
            failed = 1;
        }
        if (fd >= 0)
            close(fd);
    }
    for (i = 0; i < CALLERS; i++) {
        pthread_join(threads[i], NULL);
        failed |= callers[i].failed;
    }
    if (mode == TIMEOUT)
        vector_mask(bar, original_mask);
    if (mode != NORMAL) {
        struct kili_job job = { 0 };
        if (ioctl(device_fd, KILI_IOCTL_RUN, &job) != -1 ||
            errno != (mode == UNBIND ? ENODEV : EIO))
            failed = 1;
    }
    pthread_barrier_destroy(&start);
    munmap((void *)bar, KILI_BAR_SIZE);
    close(resource_fd);
    close(device_fd);
    globfree(&resources);
    if (failed)
        return EXIT_FAILURE;
    puts(mode == NORMAL ? "PASS: 32 callers, 2048 requests, correct per-request outputs" :
         mode == TIMEOUT ? "PASS: timeout wakes active/queue-full callers and stops reuse" :
                          "PASS: unbind wakes active/queue-full callers and invalidates fd");
    return EXIT_SUCCESS;
}

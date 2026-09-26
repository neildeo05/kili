/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Minimal static init for a diskless Linux/QEMU driver smoke test. */
#define _GNU_SOURCE
#include <sys/mount.h>
#include <sys/reboot.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define main kili_test_main
#include "../driver/kili_test.c"
#undef main

static void stop(int failed)
{
    printf("KILI_GUEST_TEST_%s\n", failed ? "FAIL" : "PASS");
    fflush(stdout);
    reboot(RB_POWER_OFF);
    for (;;) {
        pause();
    }
}

static void load_driver(void)
{
    int fd = open("/kili_drv.ko", O_RDONLY);

    if (fd < 0 || syscall(SYS_finit_module, fd, "", 0)) {
        perror("finit_module");
        stop(1);
    }
    close(fd);
}

static void unload_driver(void)
{
    if (syscall(SYS_delete_module, "kili_drv", O_NONBLOCK)) {
        perror("delete_module");
        stop(1);
    }
}

static void queue_test(const char *mode)
{
    pid_t child = fork();
    int status;

    if (!child) {
        execl("/kili_queue_test", "kili_queue_test", mode, (char *)NULL);
        perror("execl queue test");
        _exit(1);
    }
    if (child < 0 || waitpid(child, &status, 0) < 0 ||
        !WIFEXITED(status) || WEXITSTATUS(status))
        stop(1);
}

int main(void)
{
    char *args[] = { "kili_test", "/dev/kili0", NULL };
    int status, i;
    pid_t children[2];

    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    mkdir("/proc", 0755);
    mkdir("/sys", 0755);
    mkdir("/dev", 0755);
    if (mount("proc", "/proc", "proc", 0, NULL) ||
        mount("sysfs", "/sys", "sysfs", 0, NULL) ||
        mount("devtmpfs", "/dev", "devtmpfs", 0, NULL)) {
        perror("mount");
        stop(1);
    }
    load_driver();
    /* Two independent networks share the device. */
    for (i = 0; i < 2; i++) {
        children[i] = fork();
        if (!children[i]) {
            _exit(kili_test_main(2, args));
        }
        if (children[i] < 0) {
            perror("fork");
            stop(1);
        }
    }
    for (i = 0; i < 2; i++) {
        if (waitpid(children[i], &status, 0) < 0 ||
            !WIFEXITED(status) || WEXITSTATUS(status)) {
            stop(1);
        }
    }
    queue_test(NULL);
    unload_driver();
    load_driver();
    queue_test("--timeout");
    unload_driver();
    load_driver();
    queue_test("--unbind");
    unload_driver();
    puts("PASS: concurrent queues, timeout, unbind, and driver unload");
    stop(0);
}

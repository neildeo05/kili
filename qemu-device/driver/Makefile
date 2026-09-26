ifneq ($(KERNELRELEASE),)
obj-m += kili_drv.o
ccflags-y += -I$(src)/..
else
KDIR ?= /lib/modules/$(shell uname -r)/build
CC ?= cc
CFLAGS ?= -O2 -Wall -Wextra -Werror -std=c11

.PHONY: all module clean
all: module kili_test kili_queue_test

module:
	$(MAKE) -C $(KDIR) M=$(CURDIR) modules

kili_test: kili_test.c kili-uapi.h ../kili-core.c ../kili-core.h
	$(CC) $(CFLAGS) -DKILI_STANDALONE -I.. -o $@ kili_test.c ../kili-core.c

kili_queue_test: ../tests/queue_test.c kili-uapi.h ../kili-regs.h
	$(CC) $(CFLAGS) -pthread -o $@ ../tests/queue_test.c

clean:
	$(MAKE) -C $(KDIR) M=$(CURDIR) clean
	$(RM) kili_test kili_queue_test
endif

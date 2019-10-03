HOST_CC = gcc
CROSS_PREFIX = mipsel-linux-
CC = ${CROSS_PREFIX}gcc
OBJDUMP = ${CROSS_PREFIX}objdump


all: image asm

SRC_BOOT 	= ./arch/mips/boot/bootblock.S

SRC_ARCH	= ./arch/mips/kernel/entry.S  ./arch/mips/pmon/common.c 
SRC_DRIVER	= ./drivers/screen.c
SRC_INIT 	= ./init/main.c
SRC_INT		= ./kernel/irq/irq.c
SRC_LOCK	= ./kernel/locking/lock.c ./kernel/locking/futex.c
SRC_MM 		= ./kernel/mm/mm.c
SRC_SCHED	= ./kernel/sched/sched.c ./kernel/sched/time.c
SRC_SYSCALL	= ./kernel/syscall/syscall.c
SRC_LIBS	= ./libs/string.c ./libs/printk.c

SRC_LIBC	= ./tiny_libc/printf.c ./tiny_libc/string.c ./tiny_libc/mthread.c ./tiny_libc/syscall.c ./tiny_libc/syscall.S ./tiny_libc/time.c

SRC_TEST	= ./test/test.c
SRC_TEST2	= ./test/test_project2/test_scheduler1.c ./test/test_project2/test_lock1.c
SRC_TEST3	= ./test/test_project2/test_scheduler2.c ./test/test_project2/test_sleep.c ./test/test_project2/test_timer.c ./test/test_project2/test_lock2.c

SRC_IMAGE	= ./tools/createimage.c

SRC_MAIN	= ${SRC_ARCH} ${SRC_INIT} ${SRC_INT} ${SRC_DRIVER} ${SRC_LOCK} ${SRC_SCHED} ${SRC_MM} ${SRC_SYSCALL} ${SRC_LIBS} ${SRC_LIBC} ${SRC_TEST} ${SRC_TEST2} ${SRC_TEST3}

bootblock: $(SRC_BOOT)
	${CC} -G 0 -O2 -fno-pic -mno-abicalls -fno-builtin -nostdinc -mips3 -Ttext=0xffffffffa0800000 -N -o bootblock $(SRC_BOOT) -nostdlib -e main -Wl,-m -Wl,elf32ltsmip -T ld.script

main : $(SRC_MAIN)
	${CC} -g -G 0 -O0 -Iinclude -Iarch/mips/include -Idrivers  -Itest -Itest/test_project2 \
	-Itiny_libc/include \
	-fno-pic -mno-abicalls -fno-builtin -nostdinc -nostdlib -mips3 \
	-Ttext=0xffffffffa0800200 -N -o main \
	$(SRC_MAIN) -Wl,-m -Wl,elf32ltsmip -T ld.script		

createimage: $(SRC_IMAGE)
	${HOST_CC} ${SRC_IMAGE} -o createimage

image: bootblock main createimage
	./createimage --extended bootblock main

clean:
	rm -rf bootblock image main createimage *.o

floppy:
	sudo fdisk -l /dev/sdb
	sudo dd if=image of=/dev/sdb conv=notrunc

asm:
	${OBJDUMP} -d main > kernel.txt

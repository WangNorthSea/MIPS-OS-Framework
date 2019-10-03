#ifndef OS_SYSCALL_H_
#define OS_SYSCALL_H_

#include <os/syscall_number.h>
#include <os/sched.h>

/* syscall function pointer */
extern int (*syscall[NUM_SYSCALLS])();
extern void system_call_helper(regs_context_t *);

#endif
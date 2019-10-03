#include <os/lock.h>
#include <os/sched.h>
#include <common.h>
#include <screen.h>
#include <os/syscall.h>

int (*syscall[NUM_SYSCALLS])();

void system_call_helper(regs_context_t * user_context)
{
    user_context -> cp0_epc = user_context -> cp0_epc + 4;
    user_context -> regs[2] = syscall[user_context -> regs[2]](user_context -> regs[4], user_context -> regs[5], user_context -> regs[6]);
}

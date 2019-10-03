#include <os/irq.h>
#include <os/time.h>
#include <os/sched.h>
#include <os/string.h>
#include <screen.h>

static void irq_timer()
{
    // TODO clock interrupt handler.
    // scheduler, time counter in here to do, emmmmmm maybe.
}

void interrupt_helper(uint32_t status, uint32_t cause)
{
    //TODO
}

void other_exception_handler()
{
    // TODO other exception handler
}
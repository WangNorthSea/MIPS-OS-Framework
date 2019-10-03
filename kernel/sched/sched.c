#include <os/list.h>
#include <os/mm.h>
#include <os/lock.h>
#include <os/sched.h>
#include <os/time.h>
#include <os/irq.h>
#include <screen.h>
#include <stdio.h>
#include <assert.h>

const void * kernel_stack = (void *)0xa0ef0000;

pcb_t pcb[NUM_MAX_TASK];

/* current running task PCB */
pcb_t * volatile current_running;

LIST_HEAD(ready_queue);
LIST_HEAD(sleeping_queue);

/* global process id */
pid_t process_id = 1;

pcb_t pid0_pcb = {
    .kernel_stack_top = 0xa0f00000,
    .user_stack_top = 0xa0ef0000,
    .pid = 0,
    .preempt_count = 0
};

void scheduler(void)
{
    //TODO

    // restore the current_runnint's cursor_x and cursor_y
    // leave these codes bottom
    vt100_move_cursor(current_running -> cursor_x, current_running -> cursor_y);
    screen_cursor_x = current_running -> cursor_x;
    screen_cursor_y = current_running -> cursor_y;
}

void do_sleep(uint32_t sleep_time)
{
   //TODO
}

void do_block(list_node_t *pcb_node, list_head *queue)
{
    //TODO
}

void do_unblock(list_node_t *pcb_node)
{
    //TODO
}

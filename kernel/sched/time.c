#include <os/time.h>
#include <os/mm.h>
#include <os/irq.h>
#include <type.h>

LIST_HEAD(timers);

uint32_t time_elapsed = 0;
uint32_t time_base = 100000000;
uint32_t MHZ = 300;

/* a small object pool for timer_t */
static LIST_HEAD(free_timers);

static timer_t* alloc_timer()
{
    // if we have free timer, then return a free timer
    // otherwise, return a new timer which is allocated by calling kmalloc
    timer_t *ret = NULL;
    if (!list_empty(&free_timers)) {
        ret = list_entry(free_timers.next, timer_t, list);
        list_del(&ret->list);
    } else {
        ret = (timer_t*)kmalloc(sizeof(timer_t));
    }

    // initialize the timer
    ret->list.next = NULL;
    ret->list.prev = NULL;
    ret->timeout_tick = 0;
    ret->callback_func = (TimerCallback) NULL;
    ret->parameter = NULL;
    return ret;
}

static void free_timer(timer_t *timer)
{
    list_add_tail(&timer->list, &free_timers);
}

void timer_create(TimerCallback func, void* parameter, uint32_t tick)
{
    disable_preempt();

    timer_t *timer = alloc_timer();
    timer->callback_func = func;
    timer->parameter = parameter;
    timer->timeout_tick = tick;

    //TODO
   
    enable_preempt();
}

void timer_check()
{
    disable_preempt();
    if (!list_empty(&timers)) {
        //TODO
    }
    enable_preempt();
}

uint32_t get_ticks()
{
    time_elapsed = get_count();
    return time_elapsed;
}

uint32_t get_timer()
{
    return get_ticks() / time_base;
}

uint32_t get_time_base()
{
    return time_base;
}

void latency(uint32_t time)
{
    uint32_t begin_time = get_timer();

    while (get_timer() - begin_time < time)
    {
    };
    return;
}

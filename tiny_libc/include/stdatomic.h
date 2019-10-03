#ifndef STDATOMIC_H
#define STDATOMIC_H

#include <stdint.h>

typedef volatile uint32_t atomic_uint32_t;
typedef volatile uint64_t atomic_uint64_t;

typedef volatile unsigned int atomic_uint;
typedef volatile int atomic_int;
typedef volatile unsigned long atomic_ulong;
typedef volatile long atomic_long;

static inline int atomic_exchange(volatile void* obj, int desired)
{
    int ret;
    __asm__ __volatile__ (
        "loop:\n\t"
        "ll %0, 0($4)\n\t"
        "sc $5, 0($4)\n\t"
        "beq    $5, $0, loop\n\t"
        "nop\n\t"
        : "=r"(ret)
        );
    return ret;
}

#endif /* ATOMIC_H */

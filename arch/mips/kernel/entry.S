#include <asm.h>

.equ    KERNEL, 0
.equ    USER,   156
.equ    PCB_KERNEL_SP, 312
.equ    PCB_USER_SP, 316
.equ    PCB_PREEMPT_COUNT, 320

.macro STI
.endm

.macro CLI
.endm

LEAF(asm_start)
    mtc0    zero, CP0_STATUS
    mtc0    zero, CP0_WATCHLO
    mtc0    zero, CP0_WATCHHI

    mfc0    t0, CP0_CONFIG
    and     t0, ~0x7
    ori     t0, 0x2
    mtc0    t0, CP0_CONFIG
    
    jr  ra
END(asm_start)

LEAF(enable_preempt)
    la      t0, current_running
    lw      t0, 0(t0)
    lw      t1, PCB_PREEMPT_COUNT(t0)
    beq     t1, zero, do_enable
    nop
    addi    t1, t1, -1
    sw      t1, PCB_PREEMPT_COUNT(t0)
    beq     t1, zero, do_enable
    nop
    jr  ra
    nop
do_enable:
    addi    k0, zero, 1
    mfc0    k1, CP0_STATUS
    or      k1, k1, k0
    mtc0    k1, CP0_STATUS
    jr  ra
END(enable_preempt)

LEAF(disable_preempt)
    li      k0, 0xfffe
    lui     k1, 0xffff
    addu    k1, k0, k1
    mfc0    t1, CP0_STATUS
    and     t1, t1, k1
    mtc0    t1, CP0_STATUS
    la      t0, current_running
    lw      t0, 0(t0)
    lw      t1, PCB_PREEMPT_COUNT(t0)
    addi    t1, t1, 1
    sw      t1, PCB_PREEMPT_COUNT(t0)
    jr  ra
END(disable_preempt)

.macro SAVE_CONTEXT offset
    //TODO
.endm

.macro RESTORE_CONTEXT offset
    //TODO
.endm

NESTED(do_scheduler, 0, ra)
    SAVE_CONTEXT(KERNEL)
    jal     scheduler
    RESTORE_CONTEXT(KERNEL)
    jr      ra
END(do_scheduler)

.global exception_handler_begin
.global exception_handler_end

NESTED(exception_handler_entry, 0, sp)   
exception_handler_begin:
    // TODO close interrupt
    // jmp exception_handler[i] which decided by CP0_CAUSE
    // Leve2 exception Handler.
exception_handler_end:
END(exception_handler_entry)

NESTED(handle_int, 0, sp)
    // interrupt handler
    // Leve3 exception Handler.
END(handle_int)

NESTED(handle_syscall, 0, sp)
    // syscall handler
END(handle_syscall)

NESTED(handle_other, 0, sp)
    // other exception handler
END(handle_other)



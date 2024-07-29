#include "irq.h"

#include "timer.h"

void __attribute__((interrupt("IRQ"))) irq_service(void)
{
    if(IRQ_REGS->pending_basic & IRQ_BASIC_CORE_TIMER)
        handle_basic_core_timer_irq();

    return;
}

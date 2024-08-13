#include "irq.h"

#include "config.h"
#include "timer.h"
#include "gpio.h"

void __attribute__((interrupt("IRQ"))) irq_service(void)
{
    gpio_set(LED_STATUS_4);

    if(IRQ_REGS->pending_basic & IRQ_BASIC_CORE_TIMER)
        handle_basic_core_timer_irq();

    return;
}

#include "timer.h"

#include "irq.h"

volatile uint64_t ticks_ms;

void timer_init(void)
{
    TIMER_REGS->pre_divider = 126;
    TIMER_REGS->load_value = 1000;
    TIMER_REGS->control =
        TIMER_CONTROL_FREE_RUNNING |
        TIMER_CONTROL_ENABLE_TIMER |
        TIMER_CONTROL_ENABLE_IRQ |
        TIMER_CONTROL_USE_32_BIT;

    IRQ_REGS->enable_basic = IRQ_BASIC_CORE_TIMER;

    return;
}

uint64_t get_time_ms(void)
{
    return ticks_ms;
}

void wait_ms(uint64_t ms)
{
    uint64_t end_time = get_time_ms() + ms;

    while(get_time_ms() < end_time);

    return;
}

void handle_basic_core_timer_irq(void)
{
    TIMER_REGS->irq_clear = 1;
    ticks_ms++;

    return;
}

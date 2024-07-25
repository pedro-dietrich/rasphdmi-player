#include "gpio.h"

void gpio_select(uint32_t gpio_num, gpio_select_mode_t mode)
{
    if(gpio_num >= 54U)
        return;

    uint32_t reg_offset = gpio_num / 10;
    uint32_t shift_amount = 3 * (gpio_num % 10);

    volatile uint32_t* gpio_reg_select = (volatile uint32_t*)GPIO_SELECT;
    gpio_reg_select[reg_offset] &= ~(0b111 << shift_amount);
    gpio_reg_select[reg_offset] |= (mode << shift_amount);

    return;
}

void gpio_set(uint32_t gpio_num)
{
    if(gpio_num >= 54U)
        return;

    uint32_t reg_offset = gpio_num / 32;
    uint32_t shift_amount = gpio_num % 32;

    ((volatile uint32_t*)GPIO_SET)[reg_offset] = 1 << shift_amount;

    return;
}

void gpio_clear(uint32_t gpio_num)
{
    if(gpio_num >= 54U)
        return;

    uint32_t reg_offset = gpio_num / 32;
    uint32_t shift_amount = gpio_num % 32;

    ((volatile uint32_t*)GPIO_CLEAR)[reg_offset] = 1 << shift_amount;

    return;
}

uint32_t gpio_read(uint32_t gpio_num)
{
    if(gpio_num >= 54U)
        return 0xFFFFFFFF;

    uint32_t reg_offset = gpio_num / 32;
    uint32_t shift_amount = gpio_num % 32;

    return (1 & (((volatile uint32_t*)GPIO_READ)[reg_offset] >> shift_amount));
}

#include "gpio.h"

int main()
{
    // Configurar GPIOs a serem utilizadas para depuração
    gpio_select(5, GPIO_MODE_OUTPUT);
    gpio_select(6, GPIO_MODE_OUTPUT);
    gpio_select(19, GPIO_MODE_OUTPUT);
    gpio_select(16, GPIO_MODE_OUTPUT);
    gpio_select(26, GPIO_MODE_OUTPUT);
    gpio_select(20, GPIO_MODE_OUTPUT);
    gpio_select(21, GPIO_MODE_OUTPUT);

    // Trava a CPU, piscando um LED de status
    while(1)
    {
        gpio_set(5);
        for(uint32_t i = 0; i < 0x0800000; i++);
        gpio_clear(5);
        for(uint32_t i = 0; i < 0x0800000; i++);
    }

    return 0;
}

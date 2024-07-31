#include "dma.h"
#include "framebuffer.h"
#include "gpio.h"
#include "text_renderer.h"
#include "timer.h"
#include "video.h"

int main()
{
    // Configurar GPIOs a serem utilizadas para depuração
    gpio_select(6, GPIO_MODE_OUTPUT);
    gpio_select(13, GPIO_MODE_OUTPUT);
    gpio_select(19, GPIO_MODE_OUTPUT);
    gpio_select(16, GPIO_MODE_OUTPUT);
    gpio_select(26, GPIO_MODE_OUTPUT);
    gpio_select(20, GPIO_MODE_OUTPUT);
    gpio_select(21, GPIO_MODE_OUTPUT);

    timer_init();

    // Configura o framebuffer, ou acende o LED em caso de erro
    if(setup_framebuffer(VIDEO_WIDTH, VIDEO_HEIGHT, DISPLAY_BPP))
        gpio_set(21);

    for(uint32_t i = 0; i < FRAME_COUNT; i++)
    {
        draw_frame(i);
        for(uint32_t t = 0; t < 0x003000; t++);
    }

    // Imprime um texto na tela no fim da reprodução
    position_t text_pos;
    text_pos.x = 25;
    text_pos.y = 20;
    color_t text_color;
    text_color.r = 0xFF;
    text_color.g = 0x20;
    text_color.b = 0x20;
    print_screen("Fim", text_pos, text_color, false, text_color);

    // Trava a CPU, piscando um LED de status
    while(1)
    {
        gpio_set(6);
        for(uint32_t i = 0; i < 0x0200000; i++);
        gpio_clear(6);
        for(uint32_t i = 0; i < 0x0200000; i++);
    }

    return 0;
}

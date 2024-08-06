#include "dma.h"
#include "framebuffer.h"
#include "gpio.h"
#include "text_renderer.h"
#include "timer.h"
#include "video.h"

void initialize(void);
void play_video(void);
void show_status(void);

int main(void)
{
restart:
    initialize();

    play_video();

    for(uint32_t i = 0; i < 0x00400000; i++);

    show_status();

    // Trava a CPU, piscando um LED de status
    while(1)
    {
        gpio_set(6);
        for(uint32_t i = 0; i < 0x0100000; i++);
        gpio_clear(6);
        for(uint32_t i = 0; i < 0x0100000; i++);
    }

    return 0;
}

void initialize(void)
{
    // Configurar GPIOs de comando
    gpio_select(2, GPIO_MODE_INPUT);
    gpio_select(3, GPIO_MODE_INPUT);

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

    return;
}

void play_video(void)
{
    for(uint32_t i = 0; i < FRAME_COUNT; i++)
    {
        copy_frame(i);
        for(uint32_t t = 0; t < 0x008000; t++);
    }

    return;
}

void show_status(void)
{
    if(setup_framebuffer(400, 225, 24))
        gpio_set(21);

    position_t pos = {0, 0};
    color_t bg_color = {0x00, 0x20, 0xD0};

    for(pos.x = 0; pos.x < 400; pos.x++)
    {
        for(pos.y = 0; pos.y < 225; pos.y++)
            draw_pixel(bg_color, pos);
    }

    color_t text1_color = {0xA0, 0xFF, 0xA0};
    color_t text2_color = {0xFF, 0xA0, 0xA0};

    pos.x = 60;
    pos.y = 35;
    print_screen("Video name:", pos, text1_color, false, bg_color);
    pos.y += 25;
    print_screen("Horizontal resolution:", pos, text1_color, false, bg_color);
    pos.y += 25;
    print_screen("Vertical resolution:", pos, text1_color, false, bg_color);
    pos.y += 25;
    print_screen("Bits per pixel (bpp):", pos, text1_color, false, bg_color);
    pos.y += 25;
    print_screen("Frames per second (FPS):", pos, text1_color, false, bg_color);
    pos.y += 25;
    print_screen("Duration, in seconds:", pos, text1_color, false, bg_color);
    pos.y += 25;
    print_screen("Raw video size, in MB:", pos, text1_color, false, bg_color);

    pos.x = 168;
    pos.y = 35;
    print_screen("Bad Apple", pos, text2_color, false, bg_color);
    pos.x = 267;
    pos.y += 25;
    print_value(VIDEO_WIDTH, pos, text2_color, false, bg_color);
    pos.x = 249;
    pos.y += 25;
    print_value(VIDEO_HEIGHT, pos, text2_color, false, bg_color);
    pos.x = 258;
    pos.y += 25;
    print_value(DISPLAY_BPP, pos, text2_color, false, bg_color);
    pos.x = 285;
    pos.y += 25;
    print_value(30, pos, text2_color, false, bg_color);
    pos.x = 258;
    pos.y += 25;
    print_value(FRAME_COUNT / 30, pos, text2_color, false, bg_color);
    pos.x = 267;
    pos.y += 25;
    print_value(FRAME_SIZE * FRAME_COUNT / 1048576, pos, text2_color, false, bg_color);

    return;
}

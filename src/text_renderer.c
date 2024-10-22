#include "text_renderer.h"

#include "font.h"
#include "framebuffer.h"

void print_screen(const char* text, position_t pos, color_t text_color, bool use_bg, color_t bg_color)
{
    uint32_t current_x = pos.x;
    uint32_t current_y = pos.y;

    position_t pixel_coord = pos;

    for(uint32_t i = 0; text[i] != '\0'; i++)
    {
        // Verifica se é possível renderizar o caractere dentro da tela
        if(current_x + CHAR_WIDTH >= get_framebuffer_width())
        {
            current_x = pos.x;
            current_y += CHAR_FULL_HEIGHT;
        }
        if(current_y + CHAR_HEIGHT >= get_framebuffer_height())
            return;

        // Caracteres especiais
        switch(text[i])
        {
            case '\b':
                current_x -= CHAR_FULL_WIDTH;
                continue;

            case '\t':
                current_x += (4 * CHAR_FULL_WIDTH) - (current_x % CHAR_FULL_WIDTH);
                continue;

            case '\n':
                current_x = pos.x;
                current_y += CHAR_FULL_HEIGHT;
                continue;

            case '\r':
                current_x = pos.x;
                continue;

            case ' ':
                current_x += CHAR_FULL_WIDTH;
                continue;
        }

        for(uint8_t ch_y = 0; ch_y < CHAR_FULL_HEIGHT; ch_y++)
        {
            pixel_coord.y = current_y + ch_y;
            for(uint8_t ch_x = 0; ch_x < CHAR_FULL_WIDTH; ch_x++)
            {
                pixel_coord.x = current_x + ch_x;
                if(font_pixel(text[i], ch_x, ch_y))
                {
                    draw_pixel(text_color, pixel_coord);
                    continue;
                }
                if(use_bg)
                    draw_pixel(bg_color, pixel_coord);
            }
        }

        current_x += CHAR_FULL_WIDTH;
    }

    return;
}

void print_value(uint32_t number, position_t pos, color_t text_color, bool use_bg, color_t bg_color)
{
    char text[11];

    uint32_t i = 0;
    if(number == 0)
    {
        text[0] = '0';
        i++;
    }

    uint32_t digit_indicator = 1000000000U;
    bool first_digit = false;
    while(digit_indicator)
    {
        uint32_t digit = (number / digit_indicator) % 10;
        digit_indicator /= 10;

        if(digit == 0 && first_digit == false) continue;
        first_digit = true;

        text[i] = digit + 0x30;
        i++;
    }

    text[i] = '\0';

    print_screen(text, pos, text_color, use_bg, bg_color);

    return;
}

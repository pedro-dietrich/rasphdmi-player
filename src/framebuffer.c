#include "framebuffer.h"

#include "mailbox.h"
#include "gpio.h"

framebuffer_t framebuffer;

int setup_framebuffer(uint32_t width, uint32_t height, uint32_t bbp)
{
    // Buffer para mensagem via mailbox
    volatile uint32_t __attribute__((aligned(16))) mail[32];

    // Faz uma requisição para configurar o framebuffer e obter dados
    mail[0] = 4 * 26;           // Tamanho da mensagem via mailbox, em bytes
    mail[1] = MB_REQUEST_CODE;  // Mensagem do tipo requisição

    mail[2] = MB_TAG_ALLOCATE_FRAMEBUFFER;
    mail[3] = 8;    // Tamanho do buffer de valor, em bytes
    mail[4] = 8;    // Tamanho do buffer de valor na requisição, em bytes
    mail[5] = 16;   // Alinhamento e espaço para endereço do framebuffer
    mail[6] = 0;    // Espaço para o tamanho do framebuffer

    mail[7] = MB_TAG_SET_SCREEN_PHYSICAL_DIMENSIONS;
    mail[8] = 8;        // Tamanho do buffer de valor, em bytes
    mail[9] = 8;        // Tamanho do buffer de valor na requisição, em bytes
    mail[10] = width;   // Resolução horizontal
    mail[11] = height;  // Resolução vertical

    mail[12] = MB_TAG_SET_SCREEN_VIRTUAL_DIMENSIONS;
    mail[13] = 8;       // Tamanho do buffer de valor, em bytes
    mail[14] = 8;       // Tamanho do buffer de valor na requisição, em bytes
    mail[15] = width;   // Resolução horizontal virtual
    mail[16] = height;  // Resolução vertical virtual

    mail[17] = MB_TAG_SET_PIXEL_DEPTH;
    mail[18] = 4;   // Tamanho do buffer de valor, em bytes
    mail[19] = 4;   // Tamanho do buffer de valor na requisição, em bytes
    mail[20] = bbp; // Profundidade dos pixels, em bits por pixel

    mail[21] = MB_TAG_GET_PITCH;
    mail[22] = 4;   // Tamanho do buffer de valor, em bytes
    mail[23] = 4;   // Tamanho do buffer de valor na requisição, em bytes
    mail[24] = 0;   // Espaço para o pitch (bytes por linha)

    mail[25] = MB_END_TAG;  // Fim da mensagem por mailbox e padding
    mail[26] = 0;
    mail[27] = 0;
    mail[28] = 0;
    mail[29] = 0;
    mail[30] = 0;
    mail[31] = 0;

    // Envia a mensagem e espera o retorno
    mailbox_write(8, mail);
    uint32_t* response = mailbox_read(8);

    if(!response)
        return -1;
    if(mail[1] != MB_RESPONSE_OK_CODE)
        return -2;

    // Configura os dados do frambuffer obtidos
    framebuffer.address = (uint8_t*)(mail[5] & 0x3FFFFFFF);
    framebuffer.size = mail[6];
    framebuffer.bbp = mail[20];
    framebuffer.pitch = mail[24];
    framebuffer.width = mail[10];
    framebuffer.height = mail[11];

    return 0;
}

void draw_frame()
{
    position_t pos = {0, 0};

    gpio_set(6);    // Ativa um LED para indicar que um frame está sendo renderizado.

    for(pos.y = 0; pos.y < framebuffer.height; pos.y++)
    {
        for(pos.x = 0; pos.x < framebuffer.width; pos.x++)
        {
            color_t color = {255 * pos.y / framebuffer.height, 0, 255 * pos.x / framebuffer.width};
            draw_pixel(color, pos);
        }
    }

    gpio_clear(6);  // Desativa o LED para indicar que o frame terminou de ser renderizado.

    return;
}

void draw_pixel(color_t color, position_t pos)
{
    uint32_t y_offset = framebuffer.pitch * pos.y;

    switch(framebuffer.bbp)
    {
        case 8:
            // Profundidade de 8bbp usa apenas o canal de cor R
            framebuffer.address[y_offset + pos.x] = color.r;
            break;

        case 16:
            // Profundidade de 16bbp usa a codificação (RRRRRGGG GGGBBBBB)
            framebuffer.address[y_offset + 2 * pos.x] = (color.r & 0xF8) | (color.g >> 5);
            framebuffer.address[y_offset + 2 * pos.x + 1] = (color.g << 3) | (color.b >> 3);
            break;

        case 24:
            // Profundidade de 24bits usa a codificação (RRRRRRRR GGGGGGGG BBBBBBBB)
            framebuffer.address[y_offset + pos.x * 3] = color.b;
            framebuffer.address[y_offset + pos.x * 3 + 1] = color.g;
            framebuffer.address[y_offset + pos.x * 3 + 2] = color.r;
            break;

        case 32:
            // Profundidade de 32bits usa a codificação de 24bbp + AAAAAAAA
            framebuffer.address[y_offset + pos.x * 4] = color.b;
            framebuffer.address[y_offset + pos.x * 4 + 1] = color.g;
            framebuffer.address[y_offset + pos.x * 4 + 2] = color.r;
            framebuffer.address[y_offset + pos.x * 4 + 3] = 0xFF;
            break;

        default:
            // Profundidade dos pixel indefinida
            framebuffer.address[y_offset + pos.x * (framebuffer.bbp >> 3)] = 0x7F;
    }

    return;
}

uint32_t get_framebuffer_width()
{
    return framebuffer.width;
}

uint32_t get_framebuffer_height()
{
    return framebuffer.height;
}

#include "mailbox.h"

void mailbox_write(uint8_t channel, volatile uint32_t* data)
{
    while(*(volatile uint32_t*)MB_STATUS & MB_FULL);

    uint32_t mail = (uint32_t)data;

    // Os 28 primeiros bits correspondem ao endereço da mensagem,
    // enquanto os últimos 4, ao canal do mailbox utilizado.
    *(volatile uint32_t*)MB_WRITE = (mail & ~0xF) | (channel & 0xF);

    return;
}

uint32_t* mailbox_read(uint8_t channel)
{
    uint32_t data = 0x0;

    while(1)
    {
        while(*(volatile uint32_t*)MB_STATUS & MB_EMPTY);

        data = *(volatile uint32_t*)MB_READ;
        if((data & 0xF) == channel)
            return (uint32_t*)(data & ~0xF);
    }

    return 0x0;
}

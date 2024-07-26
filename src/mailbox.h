#pragma once

#include "types.h"

// Constantes para utilizar o mailbox (MB)
#define MB_BASE 0x3F00B880
#define MB_READ (MB_BASE)
#define MB_STATUS (MB_BASE + 0x18)
#define MB_WRITE (MB_BASE + 0x20)

#define MB_EMPTY 0x40000000
#define MB_FULL 0x80000000

#define MB_POWER_CHANNEL 0
#define MB_FRAMEBUFFER_CHANNEL 1
#define MB_VIRTUAL_UART_CHANNEL 2
#define MB_VCHIQ_CHANNEL 3
#define MB_LEDS_CHANNEL 4
#define MB_BUTTONS_CHANNEL 5
#define MB_TOUCHSCREEN_CHANNEL 6
#define MB_COUNTER_CHANNEL 7
#define MB_PROPERTY_CHANNEL 8

#define MB_REQUEST_CODE 0x00000000
#define MB_RESPONSE_OK_CODE 0x80000000
#define MB_RESPONSE_ERROR_CODE 0x80000001

#define MB_END_TAG 0x0

#define MB_TAG_ALLOCATE_FRAMEBUFFER 0x00040001
#define MB_TAG_FRAMEBUFFER_BLANK 0x00040002
#define MB_TAG_GET_SCREEN_PHYSICAL_DIMENSIONS 0x00040003
#define MB_TAG_GET_SCREEN_VIRTUAL_DIMENSIONS 0x00040004
#define MB_TAG_GET_PIXEL_DEPTH 0x00040005
#define MB_TAG_GET_PIXEL_ORDER 0x00040006
#define MB_TAG_GET_PITCH 0x00040008
#define MB_TAG_GET_OFFSET 0x00040009
#define MB_TAG_GET_OVERSCAN 0x0004000A
#define MB_TAG_GET_PALETTE 0x0004000B
#define MB_TAG_GET_TOUCHBUFFER 0x0004000F
#define MB_TAG_GET_GPIO_VIRTUAL_BUFFER 0x00040010

#define MB_TAG_RELEASE_FRAMEBUFFER 0x00048001
#define MB_TAG_SET_SCREEN_PHYSICAL_DIMENSIONS 0x00048003
#define MB_TAG_SET_SCREEN_VIRTUAL_DIMENSIONS 0x00048004
#define MB_TAG_SET_PIXEL_DEPTH 0x00048005
#define MB_TAG_SET_PIXEL_ORDER 0x00048006
#define MB_TAG_SET_ALPHA_MODE 0x00048007
#define MB_TAG_SET_SCREEN_OFFSET 0x00048009
#define MB_TAG_SET_OVERSCAN 0x0004800A
#define MB_TAG_SET_PALETTE 0x0004800B
#define MB_TAG_SET_VSYNC 0x0004800E
#define MB_TAG_SET_BACKLIGHT 0x0004800F
#define MB_TAG_SET_TOUCH_BUFFER 0x0004801F
#define MB_TAG_SET_GPIO_VIRTUAL_BUFFER 0x00048020

/*
* @brief Espera haver espaço no mailbox e envia uma mensagem.
*
* @param channel Indica o canal do mailbox.
* @param data Endereço da mensagem a ser enviada dividido por 16.
*/
void mailbox_write(uint8_t channel, volatile uint32_t* data);

/*
* @brief Espera uma mensagem de resposta no canal indicado e a retorna.
*
* @param channel Indica o canal do mailbox que deve receber a mensagem.
*
* @return Endereço do buffer da mensagem de retorno do mailbox.
*/
uint32_t* mailbox_read(uint8_t channel);

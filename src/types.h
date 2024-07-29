#pragma once

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

typedef enum
{
    true = 1,
    false = 0
} bool;

/*
* @brief Contém a resolução horizontal e vertical de um display
* físico ou virtual, ou do framebuffer.
*
* @param width Resolução horizontal.
* @param height Resolução vertical.
*/
typedef struct
{
    uint32_t width;
    uint32_t height;
} dimensions_t;

/*
* @brief Dados para utilizar o framebuffer.
*
* @param address Endereço base do framebuffer.
* @param size Tamanho do framebuffer.
* @param bbp Quantidade de bits por pixel.
* @param pitch Número de bytes por linha do framebuffer.
* @param width Resolução horizontal do framebuffer, em pixels.
* @param width Resolução vertical do framebuffer, em pixels.
*/
typedef struct
{
    uint8_t* address;
    uint32_t size;
    uint32_t bbp;
    uint32_t pitch;
    uint32_t width;
    uint32_t height;
} framebuffer_t;

/*
* @brief Composição de cores de um pixel RGB padrão.
*
* @param r Red - Intensidade da cor vermelha do pixel (0 - 255)
* @param g Green - Intensidade da cor verde do pixel (0 - 255)
* @param b Blue - Intensidade da cor azul do pixel (0 - 255)
*/
typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} color_t;

/*
* @brief Coordenadas x e y, em inteiros sem sinal, para localização
* no framebuffer.
*
* @param x Coordenada x
* @param y Coordenada y
*/
typedef struct
{
    uint32_t x;
    uint32_t y;
} position_t;

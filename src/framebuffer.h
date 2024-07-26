#pragma once

#include "types.h"

/*
* @brief Inicializa e configura o framebuffer de acordo com as dimensões
* e profundidade de pixel especificadas.
*
* @param width Resolução horizontal do framebuffer.
* @param height Resolução vertical do framebuffer.
* @param bbp Bits per Pixel: Profundidade de cada pixel, ou seja, quantos bits
* cada pixel utiliza para representar uma cor.
*
* @return Retorna 0 se o framebuffer foi configurado corretamente,
* -1 caso um erro ocorra ao receber a mensagem via mailbox ou
* -2 se a mensagem foi recebida mas não foi possível configurar o framebuffer.
*/
int setup_framebuffer(uint32_t width, uint32_t height, uint32_t bbp);

/*
* @brief Envia uma imagem ao framebuffer e exibe no monitor.
*/
void draw_frame();

/*
* @brief Configura a cor de um pixel no framebuffer.
*
* @param color Cor do pixel.
* @param pos Posição do pixel no framebuffer.
*/
void draw_pixel(color_t color, position_t pos);


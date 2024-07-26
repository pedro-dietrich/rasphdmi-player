#pragma once

#include "types.h"

// Tamanho dos caracteres sem espaçamento
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16
// Tamanho dos caracteres com espaçamento
#define CHAR_FULL_WIDTH 9
#define CHAR_FULL_HEIGHT 18

// Caracteres renderizáveis
#define FIRST_CHAR 0x21
#define LAST_CHAR 0xFF

/*
* @brief Verifica se o pixel nas coordenadas passadas deve ser renderizado,
* de acordo com a fonte.
*
* @param character Caractere a ser renderizado.
* @param pos_x Coordenada x do caractere (deve estar entre 0 e 7).
* @param pos_y Coordenada y do caractere (deve estar entre 0 e 15).
*
* @return `true` caso o pixel nas coordenadas deve ser renderizado,
* ou `false` caso contrário.
*/
bool font_pixel(unsigned char character, uint8_t pos_x, uint8_t pos_y);

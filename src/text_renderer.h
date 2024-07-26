#pragma once

#include "types.h"

/*
* @brief Imprime texto na tela (sem formatação), em uma posição específica.
* Também é possível escolher a cor do texto e de fundo.
*
* @param text String com o texto a ser renderizado.
* @param pos Posição, em pixels, do canto superior esquerdo da string.
* @param text_color Cor, em RGB, do texto.
* @param use_bg Decide entre usar um fundo colorido ao redor da string ou não.
* @param bg_color Cor de fundo para a string, caso `use_bg` seja `true`.
*/
void print_screen(const char* text, position_t pos, color_t text_color, bool use_bg, color_t bg_color);

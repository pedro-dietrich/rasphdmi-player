#include "font.h"

/*
* Binário da fonte utilizada para renderizar os caracteres 8x16.
* Cada array de 16 bytes é um caractere,
* cada byte é uma linha de pixels do caractere e
* cada bit é um pixel da linha.
*/
static const unsigned char font_data[224][16] =
{
	{0x00, 0x00, 0x18, 0x3C, 0x3C, 0x3C, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x66, 0x66, 0x66, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x6C, 0x6C, 0xFE, 0x6C, 0x6C, 0x6C, 0xFE, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x10, 0x10, 0x7C, 0xD6, 0xD0, 0xD0, 0x7C, 0x16, 0x16, 0xD6, 0x7C, 0x10, 0x10, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0xC2, 0xC6, 0x0C, 0x18, 0x30, 0x60, 0xC6, 0x86, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x38, 0x6C, 0x6C, 0x38, 0x76, 0xDC, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x18, 0x18, 0x18, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x18, 0x30, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x30, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7C, 0xC6, 0xCE, 0xCE, 0xD6, 0xD6, 0xE6, 0xE6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x18, 0x38, 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7C, 0xC6, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0xC6, 0xFE, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7C, 0xC6, 0x06, 0x06, 0x3C, 0x06, 0x06, 0x06, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x0C, 0x1C, 0x3C, 0x6C, 0xCC, 0xFE, 0x0C, 0x0C, 0x0C, 0x1E, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xFE, 0xC0, 0xC0, 0xC0, 0xFC, 0x06, 0x06, 0x06, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x38, 0x60, 0xC0, 0xC0, 0xFC, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xFE, 0xC6, 0x06, 0x06, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0x7E, 0x06, 0x06, 0x06, 0x0C, 0x78, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7C, 0xC6, 0xC6, 0x0C, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xDE, 0xDE, 0xDE, 0xDC, 0xC0, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x10, 0x38, 0x6C, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xFC, 0x66, 0x66, 0x66, 0x7C, 0x66, 0x66, 0x66, 0x66, 0xFC, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x3C, 0x66, 0xC2, 0xC0, 0xC0, 0xC0, 0xC0, 0xC2, 0x66, 0x3C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xF8, 0x6C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xFE, 0x66, 0x62, 0x68, 0x78, 0x68, 0x60, 0x62, 0x66, 0xFE, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xFE, 0x66, 0x62, 0x68, 0x78, 0x68, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x3C, 0x66, 0xC2, 0xC0, 0xC0, 0xDE, 0xC6, 0xC6, 0x66, 0x3A, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0xCC, 0x78, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xE6, 0x66, 0x66, 0x6C, 0x78, 0x78, 0x6C, 0x66, 0x66, 0xE6, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xF0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x62, 0x66, 0xFE, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xC6, 0xEE, 0xFE, 0xFE, 0xD6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xC6, 0xE6, 0xF6, 0xFE, 0xDE, 0xCE, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xFC, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xD6, 0xDE, 0x7C, 0x0C, 0x0E, 0x00, 0x00},
	{0x00, 0x00, 0xFC, 0x66, 0x66, 0x66, 0x7C, 0x6C, 0x66, 0x66, 0x66, 0xE6, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7C, 0xC6, 0xC6, 0x64, 0x38, 0x0C, 0x06, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0x7E, 0x5A, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x6C, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xD6, 0xD6, 0xD6, 0xFE, 0xEE, 0x6C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xC6, 0xC6, 0x6C, 0x7C, 0x38, 0x38, 0x7C, 0x6C, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xFE, 0xC6, 0x86, 0x0C, 0x18, 0x30, 0x60, 0xC2, 0xC6, 0xFE, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x3C, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x3C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x3C, 0x00, 0x00, 0x00, 0x00},
	{0x10, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00},
	{0x00, 0x30, 0x30, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xE0, 0x60, 0x60, 0x78, 0x6C, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC0, 0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x1C, 0x0C, 0x0C, 0x3C, 0x6C, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xFE, 0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x38, 0x6C, 0x64, 0x60, 0xF0, 0x60, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0xCC, 0x78, 0x00},
	{0x00, 0x00, 0xE0, 0x60, 0x60, 0x6C, 0x76, 0x66, 0x66, 0x66, 0x66, 0xE6, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x18, 0x18, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x06, 0x06, 0x00, 0x0E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x66, 0x66, 0x3C, 0x00},
	{0x00, 0x00, 0xE0, 0x60, 0x60, 0x66, 0x6C, 0x78, 0x78, 0x6C, 0x66, 0xE6, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFE, 0xD6, 0xD6, 0xD6, 0xD6, 0xC6, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0xDC, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0xDC, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 0xF0, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0x0C, 0x1E, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0xDC, 0x76, 0x66, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0x60, 0x38, 0x0C, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x10, 0x30, 0x30, 0xFC, 0x30, 0x30, 0x30, 0x30, 0x36, 0x1C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0xC6, 0xC6, 0xD6, 0xD6, 0xD6, 0xFE, 0x6C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0xC6, 0x6C, 0x38, 0x38, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7E, 0x06, 0x0C, 0xF8, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xCC, 0x18, 0x30, 0x60, 0xC6, 0xFE, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x0E, 0x18, 0x18, 0x18, 0x70, 0x18, 0x18, 0x18, 0x18, 0x0E, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x70, 0x18, 0x18, 0x18, 0x0E, 0x18, 0x18, 0x18, 0x18, 0x70, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x76, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC3, 0x99, 0x99, 0xF3, 0xE7, 0xE7, 0xFF, 0xE7, 0xE7, 0x7E, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0xFE, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x3C, 0x3C, 0x3C, 0x18, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x10, 0x7C, 0xD6, 0xD0, 0xD0, 0xD0, 0xD6, 0x7C, 0x10, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x38, 0x6C, 0x60, 0x60, 0xF0, 0x60, 0x60, 0x66, 0xF6, 0x6C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0xC6, 0x7C, 0x6C, 0x6C, 0x7C, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x66, 0x66, 0x3C, 0x18, 0x7E, 0x18, 0x7E, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x7C, 0xC6, 0x60, 0x38, 0x6C, 0xC6, 0xC6, 0x6C, 0x38, 0x0C, 0xC6, 0x7C, 0x00, 0x00, 0x00},
	{0x00, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x3C, 0x42, 0x99, 0xA5, 0xA1, 0xA5, 0x99, 0x42, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x3C, 0x6C, 0x6C, 0x3E, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x6C, 0xD8, 0x6C, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x06, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0xA5, 0x42, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x38, 0x6C, 0x6C, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00},
	{0x38, 0x6C, 0x18, 0x30, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x38, 0x6C, 0x18, 0x6C, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x18, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xF6, 0xC0, 0xC0, 0xC0, 0x00},
	{0x00, 0x00, 0x7F, 0xD6, 0xD6, 0x76, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x6C, 0x38, 0x00},
	{0x30, 0x70, 0x30, 0x30, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x38, 0x6C, 0x6C, 0x38, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0xD8, 0x6C, 0x36, 0x6C, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x60, 0xE0, 0x60, 0x60, 0xF6, 0x0C, 0x18, 0x30, 0x66, 0xCE, 0x1A, 0x3F, 0x06, 0x06, 0x00, 0x00},
	{0x60, 0xE0, 0x60, 0x60, 0xF6, 0x0C, 0x18, 0x30, 0x6E, 0xDB, 0x06, 0x0C, 0x1F, 0x00, 0x00, 0x00},
	{0x70, 0xD8, 0x30, 0xD8, 0x76, 0x0C, 0x18, 0x30, 0x66, 0xCE, 0x1A, 0x3F, 0x06, 0x06, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x30, 0x30, 0x30, 0x60, 0xC6, 0xC6, 0x7C, 0x00, 0x00},
	{0x60, 0x30, 0x00, 0x38, 0x6C, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
	{0x0C, 0x18, 0x00, 0x38, 0x6C, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
	{0x10, 0x38, 0x6C, 0x00, 0x38, 0x6C, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
	{0x76, 0xDC, 0x00, 0x38, 0x6C, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x6C, 0x00, 0x38, 0x6C, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
	{0x38, 0x6C, 0x38, 0x00, 0x38, 0x6C, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x3E, 0x78, 0xD8, 0xD8, 0xFC, 0xD8, 0xD8, 0xD8, 0xD8, 0xDE, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x3C, 0x66, 0xC2, 0xC0, 0xC0, 0xC0, 0xC0, 0xC2, 0x66, 0x3C, 0x0C, 0x66, 0x3C, 0x00},
	{0x60, 0x30, 0x00, 0xFE, 0x66, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x66, 0xFE, 0x00, 0x00, 0x00, 0x00},
	{0x0C, 0x18, 0x00, 0xFE, 0x66, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x66, 0xFE, 0x00, 0x00, 0x00, 0x00},
	{0x10, 0x38, 0x6C, 0x00, 0xFE, 0x66, 0x60, 0x7C, 0x60, 0x60, 0x66, 0xFE, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x6C, 0x00, 0xFE, 0x66, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x66, 0xFE, 0x00, 0x00, 0x00, 0x00},
	{0x60, 0x30, 0x00, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x08, 0x00, 0x00, 0x00},
	{0x06, 0x0C, 0x00, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
	{0x18, 0x3C, 0x66, 0x00, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x66, 0x00, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xF8, 0x6C, 0x66, 0x66, 0xF6, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00, 0x00, 0x00, 0x00},
	{0x76, 0xDC, 0x00, 0xC6, 0xE6, 0xF6, 0xFE, 0xDE, 0xCE, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
	{0x60, 0x30, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x0C, 0x18, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x10, 0x38, 0x6C, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x76, 0xDC, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x6C, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7E, 0xC6, 0xCE, 0xCE, 0xDE, 0xF6, 0xE6, 0xE6, 0xC6, 0xFC, 0x00, 0x00, 0x00, 0x00},
	{0x60, 0x30, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x0C, 0x18, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x10, 0x38, 0x6C, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x6C, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x06, 0x0C, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xF0, 0x60, 0x7C, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x60, 0xF0, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xCC, 0xC6, 0xC6, 0xC6, 0xD6, 0xDC, 0x80, 0x00, 0x00, 0x00},
	{0x00, 0x60, 0x30, 0x18, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x18, 0x30, 0x60, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x10, 0x38, 0x6C, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x76, 0xDC, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x6C, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x38, 0x6C, 0x38, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0xDB, 0x1B, 0x7F, 0xD8, 0xDB, 0x7E, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC0, 0xC0, 0xC0, 0xC6, 0x7C, 0x18, 0x6C, 0x38, 0x00},
	{0x00, 0x60, 0x30, 0x18, 0x00, 0x7C, 0xC6, 0xFE, 0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x0C, 0x18, 0x30, 0x00, 0x7C, 0xC6, 0xFE, 0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x10, 0x38, 0x6C, 0x00, 0x7C, 0xC6, 0xFE, 0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x6C, 0x00, 0x7C, 0xC6, 0xFE, 0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x60, 0x30, 0x18, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x0C, 0x18, 0x30, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x18, 0x3C, 0x66, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x6C, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x78, 0x30, 0x78, 0x0C, 0x7E, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x76, 0xDC, 0x00, 0xDC, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x60, 0x30, 0x18, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x0C, 0x18, 0x30, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x10, 0x38, 0x6C, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x76, 0xDC, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x6C, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x7E, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0xCE, 0xDE, 0xFE, 0xF6, 0xE6, 0xFC, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x60, 0x30, 0x18, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x18, 0x30, 0x60, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x30, 0x78, 0xCC, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0xCC, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x0C, 0x18, 0x30, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7E, 0x06, 0x0C, 0xF8, 0x00},
	{0x00, 0x00, 0xF0, 0x60, 0x60, 0x7C, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 0xF0, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x6C, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7E, 0x06, 0x0C, 0xF8, 0x00}
};

bool font_pixel(unsigned char character, uint8_t pos_x, uint8_t pos_y)
{
    if(character < FIRST_CHAR || pos_x >= 8 || pos_y > 16)
        return false;

    return (font_data[character - FIRST_CHAR][pos_y] & (0x80 >> pos_x)) ? true : false;
}

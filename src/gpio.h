#pragma once

#include "types.h"

// Constantes para uso do GPIO
#define GPIO_BASE 0x3f200000
#define GPIO_SELECT (GPIO_BASE)
#define GPIO_SET (GPIO_BASE + 0x1C)
#define GPIO_CLEAR (GPIO_BASE + 0x28)
#define GPIO_READ (GPIO_BASE + 0x34)
#define GPIO_EVENT_DETECT (GPIO_BASE + 0x40)
#define GPIO_RISING_EDGE_DETECT (GPIO_BASE + 0x4C)
#define GPIO_FALLING_EDGE_DETECT (GPIO_BASE + 0x58)
#define GPIO_HIGH_LEVEL_DETECT (GPIO_BASE + 0x64)
#define GPIO_LOW_LEVEL_DETECT (GPIO_BASE + 0x70)
#define GPIO_ASYNC_RISING_EDGE_DETECT (GPIO_BASE + 0x7C)
#define GPIO_ASYNC_FALLING_EDGE_DETECT (GPIO_BASE + 0x88)
#define GPIO_PULL_UP_DOWN (GPIO_BASE + 0x94)
#define GPIO_PULL_UP_DOWN_CLOCK (GPIO_BASE + 0x98)

/*
* @brief Possíveis configurações de uso para um GPIO.
*/
typedef enum
{
    GPIO_MODE_INPUT = 0b000,
    GPIO_MODE_OUTPUT = 0b001,
    GPIO_MODE_ALT_5 = 0b010,
    GPIO_MODE_ALT_4 = 0b011,
    GPIO_MODE_ALT_0 = 0b100,
    GPIO_MODE_ALT_1 = 0b101,
    GPIO_MODE_ALT_2 = 0b110,
    GPIO_MODE_ALT_3 = 0b111
} gpio_select_mode_t;

/*
* @brief Configura o mode de uso de um GPIO como entrada saída ou ALT 0-5.
*
* @param gpio_num Número do GPIO a ser configurado. Deve estar entre 0 e 53.
* @param mode Modo de uso do GPIO escolhido.
*/
void gpio_select(uint32_t gpio_num, gpio_select_mode_t mode);

/*
* @brief Ativa a saída do GPIO escolhido.
*
* @param gpio_num Número do GPIO a ser ativado. Deve estar entre 0 e 53.
*/
void gpio_set(uint32_t gpio_num);

/*
* @brief Desativa a saída do GPIO escolhido.
*
* @param gpio_num Número do GPIO a ser desativado. Deve estar entre 0 e 53.
*/
void gpio_clear(uint32_t gpio_num);

/*
* @brief Lê o estado do GPIO escolhido (tanto entrada quanto saída).
*
* @param gpio_num Número do GPIO a ser lido Deve estar entre 0 e 53.
*
* @return Valor obtido do GPIO, ou 0xFFFFFFFF no caso de um GPIO inválido.
*/
uint32_t gpio_read(uint32_t gpio_num);

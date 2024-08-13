#pragma once

#include "types.h"

#define SYS_TIMER_ADDRESS 0x3F003000
#define TIMER_ADDRESS 0x3F00B400

typedef struct
{
    uint32_t control_status;
    uint32_t counter_lower;
    uint32_t counter_higher;
    uint32_t compare_zero;
    uint32_t compare_one;
    uint32_t compare_two;
    uint32_t compare_three;
} system_timer_regs_t;

typedef struct
{
    uint32_t load_value;
    uint32_t current_value;
    uint32_t control;
    uint32_t irq_clear;
    uint32_t raw_irq;
    uint32_t masked_irq;
    uint32_t reload_value;
    uint32_t pre_divider;
    uint32_t free_running_counter;
} timer_regs_t;

#define SYS_TIMER_REGS ((system_timer_regs_t*)(SYS_TIMER_ADDRESS))

#define SYS_TIMER_CS_MATCH_0 0x00000001
#define SYS_TIMER_CS_MATCH_1 0x00000002
#define SYS_TIMER_CS_MATCH_2 0x00000004
#define SYS_TIMER_CS_MATCH_3 0x00000008

#define TIMER_REGS ((timer_regs_t*)(TIMER_ADDRESS))

#define TIMER_CONTROL_USE_23_BIT 0x00000002
#define TIMER_CONTROL_PRE_SCALE_MASK 0x0000000C
#define TIMER_CONTROL_ENABLE_IRQ 0x00000020
#define TIMER_CONTROL_ENABLE_TIMER 0x00000080
#define TIMER_CONTROL_HALT_ON_DEBUG 0x00000100
#define TIMER_CONTROL_FREE_RUNNING 0x00000200

#define TIMER_CONTROL_PRE_SCALE(value) ((value << 2) & TIMER_CONTROL_PRE_SCALE_MASK)

#define TIMER_PRE_DIVIDER_MASK 0x000001FF;

/*
* @brief Inicia o timer com clock de 1 MHZ, carregando com valor de 1000,
* ou seja, um timer em milisegundos. As interrupções também são habilitadas.
*/
void timer_init(void);

/*
* @brief Adquire o tempo desde o início do timer.
*
* @return Valor em milisegundos do tempo atual.
*/
uint64_t get_time_ms(void);

/*
* @brief Bloqueia a execução do processador por um determinado tempo.
*
* @param ms Tempo, em milisegundos, que o processador deve esperar.
*/
void wait_ms(uint64_t ms);

/*
* @brief Função que lida com a interrupção gerada pelo timer.
*/
void handle_basic_core_timer_irq(void);

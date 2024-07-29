#pragma once

#include "types.h"

#define IRQ_ADDRESS 0x3F00B200

typedef struct
{
    uint32_t pending_basic;
    uint32_t pending_1;
    uint32_t pending_2;
    uint32_t fiq;
    uint32_t enable_1;
    uint32_t enable_2;
    uint32_t enable_basic;
    uint32_t disable_1;
    uint32_t disable_2;
    uint32_t disable_basic;
} irq_regs_t;

#define IRQ_REGS ((irq_regs_t*) IRQ_ADDRESS)

#define IRQ_BASIC_CORE_TIMER 0x00000001
#define IRQ_BASIC_MAILBOX 0x00000002
#define IRQ_BASIC_DOORBELL_0 0x00000004
#define IRQ_BASIC_DOORBELL_1 0x00000008
#define IRQ_BASIC_GPU_0_HALTED 0x00000010
#define IRQ_BASIC_GPU_1_HALTED 0x00000020
#define IRQ_BASIC_ILLEGAL_ACCESS_TYPE_1 0x00000040
#define IRQ_BASIC_ILLEGAL_ACCESS_TYPE_0 0x00000080
#define IRQ_BASIC_INTERRUPTION_GROUP_1 0x00000100
#define IRQ_BASIC_INTERRUPTION_GROUP_2 0x00000200
#define IRQ_BASIC_GPU_7 0x00000400  //JPEG
#define IRQ_BASIC_GPU_9 0x00000800  // USB
#define IRQ_BASIC_GPU_10 0x00001000
#define IRQ_BASIC_GPU_18 0x00002000 // DMA 2
#define IRQ_BASIC_GPU_19 0x00004000 // DMA 3
#define IRQ_BASIC_GPU_53 0x00008000 // I2C
#define IRQ_BASIC_GPU_54 0x00010000 // SPI
#define IRQ_BASIC_GPU_55 0x00020000 // PCM
#define IRQ_BASIC_GPU_56 0x00040000 // SDIO
#define IRQ_BASIC_GPU_57 0x00080000 // UART

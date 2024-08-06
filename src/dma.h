#pragma once

#include "types.h"

// Adquire o endereço do barramento
#define BUS_ADDRESS(address) ((address & 0x3FFFFFFF) | 0x40000000)

#define CT_NORMAL 0x81
#define CT_NONE -1

typedef struct
{
    uint32_t channel_number;
    bool status;
} channel_data_t;

/*
* @brief Contém os dados para um bloco de controle.
*
* @param transfer_info
* @param src_address Endereço dos dados a serem transferidos.
* @param dst_address Endereço de destino da transferência.
* @param transfer_length Tamanho total do block a ser transferido.
* @param mode_2d_stride Tamanho em bytes de cada linha do bloco.
* @param next_block_address Endereço do próximo bloco de controle.
* @param reserved Espaçamento de 8 bytes não utilizados.
*/
typedef struct
{
    uint32_t transfer_info;
    uint32_t src_address;
    uint32_t dest_address;
    uint32_t transfer_length;
    uint32_t mode_2d_stride;
    uint32_t next_block_address;
    uint32_t reserved[2];
} dma_control_block_t;

/*
* @brief Conjunto de registradores para um canal DMA.
* Um ponteiro para este struct deve ser obtido pela macro `DMA_REG(channel)`.
*
* @param control_and_status Registrador para controlar o comportamento do canal
* DMA, ou ler o status do mesmo.
* @param contro_block_address Endereço (alinhado em 16 bytes) do bloco de
* controle a ser utilizado.
* @param control_block Bloco de controle sendo manuseado pelo canal DMA.
*/
typedef struct
{
    uint32_t control_and_status;
    uint32_t control_block_address;
    dma_control_block_t control_block;
} dma_channel_regs_t;

// Endereços para utilizar o DMA (Direct Memory Access)
#define DMA_BASE 0x3F007000
#define DMA_INTERRUPT_STATUS (DMA_BASE + 0x00000FE0)
#define DMA_GLOBAL_ENABLE (DMA_BASE + 0x00000FF0)

// Registradores para os DMAs (canais 0 a 14)
#define DMA_REGS(channel) (dma_channel_regs_t*)(DMA_BASE + (0x100 * channel))

// Bits para o campo de controle e status do canal DMA
#define DMA_CS_ACTIVE 0x00000001
#define DMA_CS_END 0x00000002
#define DMA_CS_INT 0x00000004
#define DMA_CS_DREQ 0x00000008
#define DMA_CS_PAUSED 0x00000010
#define DMA_CS_DREQ_STOPS_DMA 0x00000020
#define DMA_CS_WAITING_FOR_OUTSTANDING_WRITES 0x00000040
#define DMA_CS_ERROR 0x00000100
#define DMA_CS_PRIORITY_MASK 0x000F0000
#define DMA_CS_PANIC_PRIORITY_MASK 0x00F00000
#define DMA_CS_WAIT_FOR_OUTSTANDING_WRITES 0x10000000
#define DMA_CS_DISDEBUG 0x20000000
#define DMA_CS_ABORT 0x40000000
#define DMA_CS_RESET 0x80000000

#define DMA_CS_DEFAULT_PRIORITY 0x1
#define DMA_CS_DEFAULT_PANIC_PRIORITY 0xF

#define DMA_CS_PRIORITY(priority) ((priority << 16) & DMA_CS_PRIORITY_MASK)
#define DMA_CS_PANIC_PRIORITY(panic_priority) ((panic_priority << 20) & DMA_CS_PANIC_PRIORITY_MASK)

// Bits para o campo de informação de transferência do canal DMA
#define DMA_TI_INTERRUPT_ENABLE 0x00000001
#define DMA_TI_2D_MODE 0x00000002
#define DMA_TI_WAIT_RESP 0x00000008
#define DMA_TI_DEST_INCREMENT 0x00000010
#define DMA_TI_DEST_WIDTH 0x00000020
#define DMA_TI_DEST_DATA_REQ 0x00000040
#define DMA_TI_DEST_IGNORE 0x00000080
#define DMA_TI_SRC_INCREMENT 0x00000100
#define DMA_TI_SRC_WIDTH 0x00000200
#define DMA_TI_SRC_DATA_REQ 0x00000400
#define DMA_TI_SRC_IGNORE 0x00000800
#define DMA_TI_BURST_LENGTH_MASK 0x0000F000
#define DMA_TI_PERIPHERAL_MAP_MASK 0x001F0000
#define DMA_TI_WAITS_MASK 0x03E00000
#define DMA_TI_NO_WIDE_BURSTS 0x04000000

#define DMA_TI_DEFAULT_BURST_LENGTH 0x0

#define DMA_TI_BURST_LENGTH(burst_length) ((burst_length << 12) & DMA_TI_BURST_LENGTH_MASK)

/*
* @brief Realiza um reset no canal selecionado.
*
* @param channel Número do canal a ser utilizado (deve estar entre 0 e 14).
*
* @return Retorna `true` se o canal DMA estiver pronto para uso,
* ou `false` caso contrário.
*/
bool dma_init_channel(uint32_t* channel);

/*
* @brief Configura o bloco de controle com as informações necessárias
* para a transferência.
*
* @param control_block_ptr Ponteiro para o bloco de memória a ser configurado.
* @param dest Endereço de destino da transferência.
* @param src Endereço de origem da transferência.
* @param length Tamanho, em bytes, da transferência.
* @param burst_length Tamanho do burst.
*/
void dma_setup_mem_copy(dma_control_block_t* control_block_ptr, void* dest, void* src, uint32_t length, uint32_t burst_length);

/*
* @brief Realiza uma transferência pelo canal DMA especificado,
* bloqueando a execução do programa até o fim da execução.
*
* @param channel Canal DMA a ser utilizado.
* @param control_block_ptr Ponteiro do bloco de controle da transferência.
*
* @return Retorna `true` caso a transferência seja bem-sucedida,
* ou `false` em caso de erro.
*/
bool dma_transfer(uint32_t channel, dma_control_block_t* control_block_ptr);

/*
* @brief Faz uma cópia de dados utilizando DMA.
*
* @param src Endereço de onde os dados serão copiados.
* @param dest Endereço para onde os dados serão copiados.
* @param size Tamanho, em bytes, dos dados que serão copiados.
*
* @return Retorna `true` se a transferência for bem-sucedida,
* ou `false` caso contrário.
*/
bool dma_copy(void* src, void* dest, uint32_t size);

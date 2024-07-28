#include "dma.h"

bool dma_init_channel(uint32_t channel)
{
    // Apenas os canais 0 a 14 podem ser utilizados
    if(channel > 14)
        return false;

    // Ativa o canal DMA selecionado
    *((volatile uint32_t*)DMA_GLOBAL_ENABLE) |= (1 << channel);

    // Faz o reset do canal escolhido
    dma_channel_regs_t* dma_channel_regs = DMA_REGS(channel);
    dma_channel_regs->control_and_status = DMA_CS_RESET;

    // Espera o reset ser concluído
    while(dma_channel_regs->control_and_status & DMA_CS_RESET);

    // Zera os valores do bloco de controle
    dma_channel_regs->control_block.transfer_info = 0;
    dma_channel_regs->control_block.src_address = 0;
    dma_channel_regs->control_block.dest_address = 0;
    dma_channel_regs->control_block.transfer_length = 0;
    dma_channel_regs->control_block.mode_2d_stride = 0;
    dma_channel_regs->control_block.next_block_address = 0;
    dma_channel_regs->control_block.reserved[0] = 0;
    dma_channel_regs->control_block.reserved[1] = 0;

    return true;
}

void dma_setup_mem_copy(dma_control_block_t* control_block_ptr, void* dest, void* src, uint32_t length, uint32_t burst_length)
{
    control_block_ptr->transfer_info =
        DMA_TI_BURST_LENGTH(burst_length) |
        DMA_TI_SRC_WIDTH |
        DMA_TI_SRC_INCREMENT |
        DMA_TI_DEST_WIDTH |
        DMA_TI_DEST_INCREMENT;
    control_block_ptr->src_address = (uint32_t)src;
    control_block_ptr->dest_address = (uint32_t)dest;
    control_block_ptr->transfer_length = length;
    control_block_ptr->mode_2d_stride = 0;
    control_block_ptr->next_block_address = 0;

    return;
}

bool dma_transfer(uint32_t channel, dma_control_block_t* control_block_ptr)
{
    // Indica o endereço do bloco de controle
    dma_channel_regs_t* dma_regs = DMA_REGS(channel);
    dma_regs->control_block_address = BUS_ADDRESS((uint32_t)control_block_ptr);

    // Ativa os bits de controle e status, iniciando a transferência
    dma_regs->control_and_status =
        DMA_CS_WAIT_FOR_OUTSTANDING_WRITES |
        DMA_CS_PRIORITY(DMA_CS_DEFAULT_PRIORITY) |
        DMA_CS_PANIC_PRIORITY(DMA_CS_DEFAULT_PANIC_PRIORITY) |
        DMA_CS_ACTIVE;

    // Espera o fim da transferência
    while(dma_regs->control_and_status & DMA_CS_ACTIVE);

    return (dma_regs->control_and_status & DMA_CS_ERROR) ? false : true;
}

bool dma_copy(void* src, void* dest, uint32_t size)
{
    uint32_t channel = 0;
    dma_control_block_t control_block __attribute__((aligned(32)));

    if(!dma_init_channel(channel))
        return false;

    dma_setup_mem_copy(&control_block, dest, src, size, DMA_TI_DEFAULT_BURST_LENGTH);

    return dma_transfer(channel, &control_block);
}

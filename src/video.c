#include "video.h"

// Carrega dados do vídeo no endereço reservado para isso
__attribute__((section(".video_data"))) const uint8_t video_data[] =
#include "video.data"

void* get_frame_address(uint32_t frameNumber)
{
    return (void*)((uint32_t)(VIDEO_ADDRESS + (frameNumber * FRAME_SIZE)));
}

#include "video.h"

// Carrega dados do vídeo no endereço reservado para isso
VIDEO_DATA =
#include "video.data"

void* get_frame_address(uint32_t frameNumber)
{
    return (void*)((uint32_t)(VIDEO_ADDRESS + (frameNumber * FRAME_SIZE)));
}

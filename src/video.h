#pragma once

#include "types.h"

#define VIDEO_ADDRESS 0x00020000

#define VIDEO_WIDTH 192
#define VIDEO_HEIGHT 144
#define VIDEO_BPP 8
#define DISPLAY_BPP 8
#define FRAME_COUNT 1200

#define VIDEO_BYTES_PER_PIXEL (VIDEO_BPP / 8)
#define FRAME_SIZE (VIDEO_WIDTH * VIDEO_HEIGHT * VIDEO_BYTES_PER_PIXEL)

void* get_frame_address(uint32_t frameNumber);

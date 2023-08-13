#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint16_t width;
    uint16_t height;

    uint32_t* data;
} Tga;

Tga* tgaLoad(unsigned char *ptr, int size);
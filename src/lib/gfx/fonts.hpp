#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <lib/gfx/font_data.hpp>

typedef struct
{
    uint8_t  width;
    uint8_t  height;
    uint8_t  spacing_x;
    uint8_t  spacing_y;
    const uint8_t* data;
} __attribute__((packed)) font_t;

static uint32_t font_get_width(font_t font) { return font.width + font.spacing_x; }
static uint32_t font_get_height(font_t font) { return font.height + font.spacing_y; }

static const font_t FONT_SYSTEM_8x8  = { 8, 8,  0, 0, FONTDATA_SYSTEM_8x8 };
static const font_t FONT_SYSTEM_8x16 = { 8, 16, 0, 0, FONTDATA_SYSTEM_8x16 };
static const font_t FONT_SLIM_8x8    = { 8, 8,  1, 0, FONTDATA_SLIM_8x8 };
static const font_t FONT_SLIM_8x16   = { 8, 16, 0, 0, FONTDATA_SLIM_8x16 };
static const font_t FONT_HARIBOTE    = { 8, 16, 0, 0, font };
static inline bool bit_address_from_byte(uint32_t to_convert, int to_return)
{
    int mask = 1 << (to_return - 1);
    return ((to_convert & mask) != 0);
}
#define kernelFont FONT_SYSTEM_8x8

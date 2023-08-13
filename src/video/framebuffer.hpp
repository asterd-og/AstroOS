#pragma once

#include <stdint.h>
#include <lib/gfx/fonts.hpp>
#include <lib/gfx/colors.hpp>
#include <desktop/tga.hpp>

#define getTransparency(tLevel) 100-tLevel

#define black 0
#define blue 0xFF0000AA
#define green 0xFF00AA00
#define cyan 0xFF00AAAA
#define red 0xFFAA0000
#define magenta 0xFFAA00AA
#define brown 0xFFAA5500
#define lightGray 0xFFAAAAAA
#define darkGray 0xFF555555
#define lightBlue 0xFF5555FF
#define lightGreen 0xFF55FF55
#define lightCyan 0xFF55FFFF
#define lightRed 0xFFFF5555
#define lightMagenta 0xFFFF55FF
#define yellow 0xFFFFFF55
#define white 0xFFFFFFFF

typedef struct {
    uint32_t r;
    uint32_t g;
    uint32_t b;
} rgb;

static inline uint32_t colorPackRgb(rgb rgb) {
    return rgb.r | (rgb.g << 8) | (rgb.b << 16);
}

class Framebuffer {
	private:
	public:
		int width;
		int height;
		int bpp;
		int pitch;
		int size;

		int gridW;
		int gridH;

		uint32_t* backBuffer;

		rgb rgb;

		void create(int width, int height,
				    int bpp, int pitch,
				    uint32_t* backBufferAddr);

		uint32_t getPixel(int x, int y);

		void drawPixel(int x, int y, uint32_t color);
		void drawAlphaPixel(int x, int y, uint32_t color);

		uint32_t alphaBlend(uint32_t c1, uint32_t c2, uint8_t alpha);

		void drawFillRect(int x, int y, int w, int h, uint32_t color);
		void drawFillAlphaRect(int x, int y, int w, int h, uint32_t color);

		void drawChar(int x, int y, char c, uint32_t color, font_t font = kernelFont);
		void drawString(int x, int y, char* str, uint32_t color, font_t font = kernelFont);

		void drawTga(int x, int y, Tga* tga);

		void clear(uint32_t color);

		int getBpp();
		int getPitch();
};

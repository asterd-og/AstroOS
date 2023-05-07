#pragma once

#include <stdint.h>
#include <lib/gfx/fonts.hpp>
#include <lib/gfx/colors.hpp>

#define getTransparency(tLevel) 100-tLevel

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
		uint32_t* address;
		uint32_t* backAddress;
		rgb rgb;

		void init();

		uint32_t getPixel(int x, int y);

		void drawPixel(int x, int y, uint32_t color);
		void drawAlphaPixel(int x, int y, uint32_t color);

		uint32_t alphaBlend(uint32_t c1, uint32_t c2, uint8_t alpha);

		void drawFillRect(int x, int y, int w, int h, uint32_t color);

		void drawChar(int x, int y, char c, uint32_t color, font_t font);
		void drawString(int x, int y, char* str, uint32_t color, font_t font);

		void clear(uint32_t color);
		void update();
};

extern Framebuffer Gfx;

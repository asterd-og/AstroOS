#pragma once

#include <stdint.h>
#include <lib/gfx/fonts.hpp>
#include <lib/gfx/colors.hpp>

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

		void init();

		uint32_t getPixel(int x, int y);

		void drawPixel(int x, int y, uint32_t color);
		
		void drawFillRect(int x, int y, int w, int h, uint32_t color);

		void drawChar(int x, int y, char c, uint32_t color, font_t font);
		void drawString(int x, int y, char* str, uint32_t color, font_t font);

		void clear(uint32_t color);
		void update();
};

extern Framebuffer Gfx;

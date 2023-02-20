#pragma once

#include <stdint.h>
#include <lib/gfx/fonts.h>

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

		void init(int);
		void drawPixel(int, int, uint32_t);
		
		void drawFillRect(int, int, int, int, uint32_t);

		void drawChar(int, int, char, uint32_t, font_t);
		void drawString(int, int, char*, uint32_t, font_t);

		void clear(uint32_t);
		void update();
};

extern Framebuffer Vbe;

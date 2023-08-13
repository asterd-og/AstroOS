#include <video/framebuffer.hpp>
#include <kernel/limine.h>
#include <kernel/kernel.hpp>
#include <lib/string.hpp>
#include <lib/printf.h>
#include <memory/heap.hpp>
#include <sys/serial.hpp>

void Framebuffer::create(int width, int height,
				  	     int bpp, int pitch,
				         uint32_t* backBufferAddr) {
	this->width = width;
	this->height = height;
	this->pitch = pitch;
	this->bpp = bpp;
	this->size = size;

	this->backBuffer = backBufferAddr;

	memset(this->backBuffer, 0, this->size);
}

uint32_t Framebuffer::getPixel(int x, int y) {
	if (x > this->width || y > this->height || x < 0 || y < 0) return 0;
	return this->backBuffer[y * width + x];
}

void Framebuffer::drawPixel(int x, int y, uint32_t color) {
	if (x > this->width || y > this->height || x < 0 || y < 0) return;
	this->backBuffer[y * width + x] = color;
}

void Framebuffer::drawAlphaPixel(int x, int y, uint32_t color) {
	if (x > this->width || y > this->height || x < 0 || y < 0) return;
	this->backBuffer[y * width + x] = alphaBlend(color, this->getPixel(x, y), (color >> 24));
}

uint32_t Framebuffer::alphaBlend(uint32_t c1, uint32_t c2, uint8_t alpha) {
	this->rgb.r = ((c1 & 0xFF) * alpha + (c2 & 0xFF) * (255 - alpha)) / 255;
    this->rgb.g = (((c1 >> 8) & 0xFF) * alpha + ((c2 >> 8) & 0xFF) * (255 - alpha)) / 255;
    this->rgb.b = (((c1 >> 16) & 0xFF) * alpha + ((c2 >> 16) & 0xFF) * (255 - alpha)) / 255;
    return colorPackRgb(this->rgb);
}

void Framebuffer::drawFillRect(int x, int y, int w, int h, uint32_t color) {
	for (int i = x; i < x + w; i++)
		for (int j = y; j < y + h; j++)
			drawPixel(i, j, color);
}
void Framebuffer::drawFillAlphaRect(int x, int y, int w, int h, uint32_t color) {
	for (int i = x; i < x + w; i++)
		for (int j = y; j < y + h; j++)
			drawAlphaPixel(i, j, color);
}

void Framebuffer::drawChar(int x, int y, char c, uint32_t color, font_t font) {
	if (c == 0) return;
	uint32_t p = font.height * c;
	for (size_t _y = 0; _y < font.height; _y++)
		for (size_t _x = 0; _x < font.width; _x++)
			if (bit_address_from_byte(font.data[p + _y], _x + 1))
				drawPixel(x + (font.width - _x), y + _y, color);
}

void Framebuffer::drawString(int x, int y, char* str, uint32_t color, font_t font) {
	for (int i = 0; i < strlen(str); i++) {
		drawChar(x + (i * font.width), y, str[i], color, font);
	}
}

void Framebuffer::drawTga(int x, int y, Tga* tga) {
	for (int i = 0; i < tga->width; i++)
		for (int j = 0; j < tga->height; j++)
			this->drawPixel(x + i, y + j, tga->data[j * tga->width + i]);
}

void Framebuffer::clear(uint32_t color) {
	for (int i = 0; i < this->width * this->height; i++) this->backBuffer[i] = color;
}

int Framebuffer::getBpp() { return this->bpp; }
int Framebuffer::getPitch() { return this->pitch; }
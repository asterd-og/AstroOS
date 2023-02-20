#include <video/framebuffer.h>
#include <kernel/limine.h>
#include <kernel/kernel.h>
#include <lib/string.h>
#include <memory/pmm.h>

static volatile struct limine_framebuffer_request fb_req = {
	.id = LIMINE_FRAMEBUFFER_REQUEST,
	.revision = 0
};

void Framebuffer::init(int framebufferIdx) {
	struct limine_framebuffer* fb = fb_req.response->framebuffers[0];
	
	this->width = fb->width;
	this->height = fb->height;
	this->pitch = fb->pitch;
	this->bpp = fb->bpp;
	this->size = this->width * this->height * 4;

	this->address = (uint32_t*)fb->address;
	this->backAddress = (uint32_t*)Pmm::alloc((1024 * 768) / pageSize);

	memset(this->backAddress, 0x0, this->size);
}

void Framebuffer::drawPixel(int x, int y, uint32_t color) {
	if (x > this->width || y > this->height || x < 0 || y < 0) return;
	this->backAddress[y * this->pitch / 4 + x] = color;
}

void Framebuffer::drawFillRect(int x, int y, int w, int h, uint32_t color) {
	for (int i = x; i < x + w; i++)
		for (int j = y; j < y + h; j++)
			drawPixel(i, j, color);
}

void Framebuffer::drawChar(int x, int y, char c, uint32_t color, font_t font) {
	if (c == 0) return;
	uint32_t p = font.height * c;
	for (size_t _y = 0; _y < font.height; _y++)
		for (size_t _x = 0; _x < font.width; _x++)
			if (bit_address_from_byte(font.data[p + _y], _x + 1))
				drawPixel(x + (font.width - _x), y + _y, color);
}

void Framebuffer::clear(uint32_t color) {
	for (int i = 0; i < this->width * this->height; i++) this->backAddress[i] = color;
}

void Framebuffer::update() {
	for (int i = 0; i < this->width * this->height; i++) this->address[i] = this->backAddress[i];
}
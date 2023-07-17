#include <video/vbe.hpp>
#include <kernel/limine.h>
#include <memory/heap.hpp>
#include <sys/serial.hpp>

static volatile struct limine_framebuffer_request fb_req = {
	.id = LIMINE_FRAMEBUFFER_REQUEST,
	.revision = 0
};

void Vbe::init() {
    struct limine_framebuffer* fb = fb_req.response->framebuffers[0];

	this->frontBuffer = (uint32_t*)fb->address;
	this->backBuffer = (uint32_t*)Heap::alloc(fb->width * fb->height * 4);
    this->create(fb->width, fb->height,
                 fb->bpp, fb->pitch,
                 backBuffer);
                
    io.print("VBE BPP: %lu.\nVBE Pitch: %lu.\n", fb->bpp, fb->pitch);
}

void Vbe::drawGc(int x, int y, Framebuffer gc) {
    for (int y1 = 0; y1 < gc.height; y1++)
        for (int x1 = 0; x1 < gc.width; x1++)
            this->drawPixel(x + x1, y + y1, gc.getPixel(y1, x1));
}

void Vbe::update() {
    for (int i = 0; i < this->width * this->height; i++) this->frontBuffer[i] = this->backBuffer[i];
}
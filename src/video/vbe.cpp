#include <video/vbe.hpp>
#include <kernel/limine.h>
#include <memory/heap.hpp>

static volatile struct limine_framebuffer_request fb_req = {
	.id = LIMINE_FRAMEBUFFER_REQUEST,
	.revision = 0
};

void Vbe::init() {
    struct limine_framebuffer* fb = fb_req.response->framebuffers[0];

	this->frontBuffer = (uint32_t*)fb->address;
	this->backBuffer = (uint32_t*)Heap::alloc(this->size);
    this->create(fb->width, fb->height,
                 fb->bpp, fb->pitch,
                 backBuffer);
}

void Vbe::update() {
    for (int i = 0; i < this->width * this->height; i++) this->frontBuffer[i] = this->backBuffer[i];
}
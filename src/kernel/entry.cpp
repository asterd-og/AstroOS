#include <kernel/kernel.h>
#include <tables/gdt/gdt.h>
#include <tables/idt/idt.h>
#include <video/terminal.h>
#include <lib/printf.h>
#include <memory/pmm.h>
#include <lib/string.h>
#include <sys/pit.h>
#include <video/framebuffer.h>

static volatile struct limine_hhdm_request hhdmReq = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

uint64_t hhdmOff;

Framebuffer Vbe;

extern "C" void _start() {
    hhdmOff = hhdmReq.response->offset;

    Pmm::init();
    Vbe.init(0);

    Terminal::init();

    printf("PMM Initialised.\n");
    printf("FB Initialised.\n");
    printf("Terminal Initialised.\n");
    Gdt::init();
    printf("GDT Initialised.\n");
    Idt::init();
    printf("IDT Initialised.\n");
    Pit::init();
    printf("PIT Initialised.\n");

    for (;;) {
		asm("hlt");
	}
}

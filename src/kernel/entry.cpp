#include <kernel/kernel.h>
#include <tables/gdt/gdt.h>
#include <tables/idt/idt.h>
#include <video/terminal.h>
#include <lib/printf.h>
#include <memory/pmm.h>
#include <lib/string.h>
#include <sys/pit.h>
#include <video/framebuffer.h>
#include <sys/ps2/keyboard.h>

static volatile struct limine_hhdm_request hhdmReq = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

uint64_t hhdmOff;

Framebuffer Vbe;

extern "C" void _start() {
    hhdmOff = hhdmReq.response->offset;

    Pmm::init();
    Vbe.init();

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

    Keyboard::init();

    char c = 0;

    while (1) {
        c = Keyboard::getChar();
        if (c != '\0') printf("%c", c);
        c = '\0';
    }

    for (;;) {
		asm("hlt");
	}
}

#include <kernel/kernel.hpp>
#include <tables/gdt/gdt.hpp>
#include <tables/idt/idt.hpp>
#include <video/terminal.hpp>
#include <lib/printf.h>
#include <memory/pmm.hpp>
#include <lib/string.hpp>
#include <sys/pit.hpp>
#include <video/framebuffer.hpp>
#include <sys/ps2/keyboard.hpp>
#include <memory/vmm.hpp>
#include <memory/pageMap.hpp>
#include <memory/pageTable.hpp>

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

    for (;;) {
        asm("hlt");
	}
}

#include <kernel/kernel.h>
#include <tables/gdt/gdt.h>
#include <tables/idt/idt.h>
#include <video/terminal.h>
#include <lib/printf.h>
#include <memory/pmm.h>
#include <lib/string.h>
#include <sys/pit.h>

static volatile struct limine_hhdm_request hhdmReq = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

uint64_t hhdmOff;

extern "C" void _start() {
    hhdmOff = hhdmReq.response->offset;

    Terminal::init();

    Gdt::init();
    printf("GDT Initialised.\n");
    Idt::init();
    printf("IDT Initialised.\n");
    Pmm::init();
    printf("PMM Initialised.\n");
    Pit::init();
    printf("PIT Initialised.\n");
	
    for (;;) {
		asm("hlt");
	}
}

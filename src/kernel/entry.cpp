#include <kernel/kernel.h>
#include <tables/gdt/gdt.h>
#include <tables/idt/idt.h>
#include <video/terminal.h>
#include <lib/printf.h>
#include <memory/pmm.h>
#include <lib/string.h>

static volatile struct limine_hhdm_request hhdmReq = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

uint64_t hhdmOff;

void moveTo(char* str, char c, int times) {
    for (int i = 0; i < times; i++) str[i] = c;
}

extern "C" void _start() {
    hhdmOff = hhdmReq.response->offset;

    Terminal::init();

    Gdt::init();
    printf("GDT Initialised.\n");
    Idt::init();
    printf("IDT Initialised.\n");
    Pmm::init();
    printf("PMM Initialised.\n");

    char* test = (char*)Pmm::alloc(2);
    moveTo(test, 'a', pageSize * 2);

    printf("%s\n%d\n", test, strlen(test));

	for (;;) {
		asm("hlt");
	}
}

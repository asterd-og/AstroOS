#include <kernel/kernel.h>
#include <tables/gdt/gdt.h>
#include <tables/idt/idt.h>
#include <video/terminal.h>
#include <lib/printf.h>

extern "C" void _start() {
    Terminal::init();

    Gdt::init();
    printf("GDT Initialised.\n");
    Idt::init();
    printf("IDT Initialised.\n");

    __asm__ volatile("int $0x3");

	for (;;) {
		asm("hlt");
	}
}

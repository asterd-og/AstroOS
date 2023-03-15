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

Framebuffer Vbe;

extern "C" void _start() {
    printf("Astro Kernel Booted.\n\n");

    Gdt::init();
    printf("GDT Initialised.\n");

    Idt::init();
    printf("IDT Initialised.\n");

    Pmm::init();
    printf("PMM Initialised.\n");
 
    Vbe.init();
    printf("FB Initialised.\n");

    Vbe.clear(0x0);
    Vbe.drawFillRect(150, 150, 150, 150, 0xFF00FF);

    for (;;) {
        Vbe.update();
	}
}

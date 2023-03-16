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
#include <sys/sw/console.hpp>
#include <sys/serial.hpp>

Framebuffer Vbe;
Serial io;

extern "C" void _start() {
    printf("+--------------------+\n");
    printf("|Astro Kernel Booted.|\n");
    printf("+--------------------+\n\n");

    io = Serial();
    io.print("Serial Initialised.\n");

    Gdt::init();
    printf("GDT Initialised.\n");

    Idt::init();
    printf("IDT Initialised.\n");

    Pmm::init();
    printf("PMM Initialised.\n");

    Keyboard::init();
    printf("KB Initialised.\n");

    Console::init();
 
    for (;;) {
        Console::update();
	}
}

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
#include <sys/exec/syscalls.hpp>
#include <sys/exec/elf.hpp>
#include <sys/exec/com.hpp>

Framebuffer Vbe;
Serial io;

extern "C" void _start() {
    printf("+----------------------+\n");
    printf("| Astro Kernel Booted. |\n");
    printf("+----------------------+\n\n");

    io = Serial();
    io.print("Serial Initialised.\n");

    Gdt::init();
    printf("GDT Initialised.\n");
    
    Pmm::init();
    printf("PMM Initialised.\n");

	Vmm::init();
    printf("VMM Initialised.\n");

    Idt::init();
    printf("IDT Initialised.\n");
    
    printf("HHDM Off: %ld | 0x%lx.\n", Pmm::getHhdmOff(), Pmm::getHhdmOff());
    
    Vbe.init();
    printf("FB Initialised.\n");
    
    static volatile struct limine_module_request modReq = {
		.id = LIMINE_MODULE_REQUEST,
		.revision = 0
	};
	
	struct limine_module_response* modRes = modReq.response;
	
	printf("Module 0 (PRG) addr: 0x%lx size: 0x%lx\n", (uint64_t)modRes->modules[0]->address + Pmm::getHhdmOff(), modRes->modules[0]->size);

	Syscalls::init();
	printf("Syscalls Initialised.\n");

    Keyboard::init();
    printf("KB Initialised.\n");

    Console::init();
 
    for (;;) {
        Console::update();
		//Vbe.termEffect();
	}
}

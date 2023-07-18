#include <kernel/kernel.hpp>
#include <tables/gdt/gdt.hpp>
#include <tables/idt/idt.hpp>
#include <video/terminal.hpp>
#include <lib/printf.h>
#include <lib/string.hpp>
#include <sys/pit.hpp>
#include <video/framebuffer.hpp>
#include <video/vbe.hpp>
#include <sys/ps2/keyboard.hpp>
#include <sys/sw/console.hpp>
#include <sys/serial.hpp>
#include <sys/ps2/mouse.hpp>
#include <desktop/cursor.hpp>
#include <memory/heap.hpp>
#include <memory/pmm.hpp>
#include <desktop/window.hpp>

static volatile struct limine_hhdm_request hhdmReq = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

uint64_t hhdmOff;

Vbe Gfx;
Serial io;

extern "C" void _start() {
    hhdmOff = hhdmReq.response->offset;

    io = Serial();
    io.print("Serial Initialised.\n");

    Pmm::init();
    io.print("Pmm Initialised.\n");

    Heap::init();
    io.print("Heap Initialised.\n");
    
    Gfx.init();
    io.print("GFX Initialised.\n");

    Gdt::init();
    io.print("GDT Initialised.\n");
    
    Idt::init();
    io.print("IDT Initialised.\n");

    Mouse::init();
    io.print("Mouse initialised.\n");

    Keyboard::init();
    io.print("Keyboard Initialised.\n");

    Console::init();
    io.print("Console Initialised.\n");

    for (;;) {
        Gfx.clear(black);
        Console::update();
        Console::winUpdate();
        Cursor::draw();
        Gfx.update();
    }
}

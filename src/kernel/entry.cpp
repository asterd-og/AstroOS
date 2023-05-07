#include <kernel/kernel.hpp>
#include <tables/gdt/gdt.hpp>
#include <tables/idt/idt.hpp>
#include <video/terminal.hpp>
#include <lib/printf.h>
#include <lib/string.hpp>
#include <sys/pit.hpp>
#include <video/framebuffer.hpp>
#include <sys/ps2/keyboard.hpp>
#include <sys/sw/console.hpp>
#include <sys/serial.hpp>
#include <sys/ps2/mouse.hpp>
#include <desktop/cursor.hpp>
#include <desktop/window.hpp>
#include <memory/heap.hpp>

static volatile struct limine_hhdm_request hhdmReq = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

volatile struct limine_memmap_request memReq = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

struct limine_memmap_response* memRes;

uint64_t hhdmOff;

Framebuffer Gfx;
Serial io;

extern "C" void _start() {
    hhdmOff = hhdmReq.response->offset;
    
    memRes = memReq.response;

    io = Serial();
    io.print("Serial Initialised.\n");

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

    Window win = Window("hey", 400, 400, 10, 30);
    
    for (;;) {
        Gfx.clear(0xFF191919);
        win.update();
        win.draw();
        Cursor::draw();
        Gfx.update();
    }
}

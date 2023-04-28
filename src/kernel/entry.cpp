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
#include <sys/sw/console.hpp>
#include <sys/serial.hpp>
#include <sys/ps2/mouse.hpp>
#include <desktop/cursor.hpp>
#include <desktop/window.hpp>

static volatile struct limine_hhdm_request hhdmReq = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

uint64_t hhdmOff;

Framebuffer Gfx;
Serial io;

extern "C" void _start() {
    hhdmOff = hhdmReq.response->offset;

    Pmm::init();
    Gfx.init();
    
    io = Serial();
    io.print("Serial Initialised.\n");

    io.print("PMM Initialised.\n");
    io.print("FB Initialised.\n");

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
        Gfx.clear(0xFFFFFFFF);
        win.update();
        win.draw();
        Cursor::draw();
        Gfx.update();
    }
}

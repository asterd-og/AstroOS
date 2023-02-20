#include <sys/ps2/keyboard.h>
#include <lib/ports.h>
#include <tables/idt/idt.h>
#include <sys/ps2/kbMap.h>

namespace Keyboard {
    bool pressed = false;
    char currentChar = '\0';

    void handler(Registers* regs) {
        uint8_t key = inb(0x60);
        if (!(key & 0x80)) {
            pressed = true;
            currentChar = keys[key];
        }
    }

    void init() {
        Idt::installHandler(1, handler);
    }

    char getChar() {
        if (pressed) {
            pressed = false;
            return currentChar;
        } else {
            return '\0';
        }
    }
}
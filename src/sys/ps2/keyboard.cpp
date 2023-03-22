#include <sys/ps2/keyboard.hpp>
#include <lib/ports.hpp>
#include <tables/idt/idt.hpp>
#include <sys/ps2/kbMap.hpp>

namespace Keyboard {
    bool pressed = false;
    char currentChar = '\0';
    bool caps = false;
    bool shift = false;

    void handler(Registers* regs) {
        uint8_t key = inb(0x60);
        if (!(key & 0x80)) {
			// key down
            if (key == 0x2a) {
                // shift
                shift = true;
            } else if (key == 0x3a) {
                // caps
                caps = !caps;
            } else {
                pressed = true;
                if (shift) currentChar = keysShift[key];
                else if (caps) currentChar = keysCaps[key];
                else currentChar = keys[key];
            }
        } else {
            if (key == 0xaa) {
                // shift up
                shift = false;
            }
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

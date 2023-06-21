#include <sys/ps2/mouse.hpp>
#include <video/vbe.hpp>
#include <lib/ports.hpp>
#include <sys/serial.hpp>
#include <sys/pic.hpp>

namespace Mouse {
    uint8_t state = 0;
    uint8_t bytes[3];  // check on wiki.osdev.org/PS/2_mouse
    // For more info

    uint32_t _x = 0;
    uint32_t _y = 0;
    bool _left = false;
    bool _right = false;

    void waitWrite() {
        while ((inb(0x64) & 2) != 0) {;}
    }

    void waitRead() {
        while ((inb(0x64) & 1) != 1) {;}
    }

    void write(uint8_t value) {
        waitWrite();
        outb(0x64, 0xd4);
        waitWrite();
        outb(0x60, value);
    }

    uint8_t read() {
        waitRead();
        return inb(0x60);
    }

    void init() {
        uint8_t ts;
        waitWrite();
        outb(0x64, 0xA8);
        waitWrite();
        outb(0x64, 0x20);
        waitRead();
        ts = (inb(0x60) | 2);
        waitWrite();
        outb(0x64, 0x60);
        waitWrite();
        outb(0x60, ts);
        write(0xF6);
        read();
        write(0xF4);
        read();
        Idt::installHandler(12, update);
    }

    void handle(int8_t x1, int8_t y1) {
        _x += x1;
        _y += y1;

        if (_x <= 0) _x = 0;
        if (_y <= 0) _y = 0;
        if (_x >= Gfx.width) _x = Gfx.width;
        if (_y >= Gfx.height) _y = Gfx.height;
    }

    void update(Registers* regs) {
        uint8_t b = inb(0x64);
        if ((!(b & 1)) == 1) { state = 0; return; }
        if ((!(b & 2)) == 0) { state = 0; return; }
        if (!(b & 0x20)) { state = 0; return; }
        switch (state) {
            // State of packet
            case 0:
                waitRead();
                bytes[0] = read();
                state++;
                break;
            case 1:
                waitRead();
                bytes[1] = read();
                state++;
                break;
            case 2:
                waitRead();
                bytes[2] = read();

                handle(bytes[1], -bytes[2]);

                _left = (bool)(bytes[0] & 0b00000001);
                _right = (bool)((bytes[0] & 0b00000010) >> 1);

                state = 0;

                break;
        }
    }

    uint32_t x() { return _x; }
    uint32_t y() { return _y; }
    bool left() { return _left; }
    bool right() { return _right; }
}

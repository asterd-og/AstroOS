#include <sys/serial.hpp>
#include <lib/string.hpp>
#include <lib/ports.hpp>
#include <lib/printf.h>

#define port 0x3f8 // COM 1

Serial::Serial() {
    outb(port + 1, 0);
    outb(port + 3, 0x80);
    outb(port, 0x03);
    outb(port + 1, 0);
    outb(port + 3, 0x03);
    outb(port + 2, 0xC7);
    outb(port + 4, 0x0B);
}

int Serial::received() {
    return (inb(port + 5) & 1);
}

char Serial::read() {
    while (this->received() == 0);
    return inb(port);
}

int Serial::isTransmitEmpty() {
    return inb(port + 5) & 0x20;
}

void Serial::write(char c) {
    while (this->isTransmitEmpty() == 0);
    outb(port, c);
}

int Serial::print(char* str, ...) {
    va_list va;
    va_start(va, str);
    char buffer[2048];
    const int ret = vsnprintf_(buffer, strlen(str)+1, str, va);
    va_end(va);
    for (int i = 0; i < strlen(buffer); i++)
        this->write(buffer[i]);
    return 0;
}

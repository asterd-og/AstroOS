#pragma once

#include <stdint.h>
#include <stdarg.h>

class Serial {
    public:
        Serial();
        int received();
        char read();
        int isTransmitEmpty();
        void write(char c);
        int print(char* str, ...);
};

extern Serial io;
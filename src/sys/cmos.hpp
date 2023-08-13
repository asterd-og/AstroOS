#pragma once

#include <stdint.h>
#include <stddef.h>

#define cYear 2023

namespace Cmos {
    extern unsigned char second;
    extern unsigned char minute;
    extern unsigned char hour;
    extern unsigned char day;
    extern unsigned char month;
    extern unsigned int year;

    enum {
        cmosAddress = 0x70,
        cmosData = 0x71
    };
}
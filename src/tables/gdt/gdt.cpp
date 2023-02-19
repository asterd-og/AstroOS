#include <tables/gdt/gdt.h>

namespace Gdt {
    uint64_t data[9] = {
        0x0000000000000000,
    
        0x00009a000000ffff, // 16-bit code
        0x000093000000ffff, // 16-bit data

        0x00cf9a000000ffff, // 32-bit code
        0x00cf93000000ffff, // 32-bit data

        0x00af9b000000ffff, // 64-bit code
        0x00af93000000ffff, // 64-bit data

        0x00affb000000ffff, // usermode 64-bit code
        0x00aff3000000ffff, // usermode 64-bit data
    };

    void init() {
        GdtR gdt = {
            .length = (sizeof(uint64_t) * 9) - 1,
            .offset = (uint64_t)&data
        };

        __asm__ volatile("lgdt %0" : : "m"(gdt) : "memory");
    }
}
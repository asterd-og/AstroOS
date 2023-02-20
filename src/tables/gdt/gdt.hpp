#pragma once

#include <stdint.h>

namespace Gdt {
    typedef struct {
        uint16_t length;
        uint64_t offset;
    } __attribute__((packed)) GdtR;
    
    void init();
}
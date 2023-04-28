#pragma once

#include <stdint.h>
#include <stddef.h>
#include <tables/idt/idt.hpp>

namespace Mouse {
    void init();
    void update(Registers* regs);

    uint32_t x();
    uint32_t y();
    bool left();
    bool right();
}
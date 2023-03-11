#pragma once

#include <stdint.h>

namespace Vmm {
    typedef struct {
        bool present : 1;
        bool rw : 1;
        bool userSuper : 1;
        bool wt : 1;
        bool cd : 1;
        bool access : 1;
        bool r0 : 1;
        bool largerPages : 1;
        bool i0 : 1;
        uint8_t available : 3;
        uint64_t addr : 52;
    } PDE;

    typedef struct {
        PDE entries[512];
    } __attribute__((aligned(0x1000))) PT;

    void init();
    void pmIndexer(uint64_t vaddr);
}
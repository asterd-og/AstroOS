// PMM Using a stack-based approach
// No slab allocator, no bitmap allocator, only stack
// Everything made by astrido

#pragma once

#include <stdint.h>
#include <stddef.h>

#define pageSize 4096

#define divRoundUp(x, y) (x + ( y - 1)) / y
#define alignUp(x, y) divRoundUp(x, y) * y

namespace Pmm {
    void  init();
    void* alloc(size_t size);
    void  free(void* ptr, size_t size);
    uint64_t getHhdmOff();
    uint64_t getMemSize();
}
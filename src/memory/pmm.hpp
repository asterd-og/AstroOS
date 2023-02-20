#pragma once

#include <stdint.h>
#include <stddef.h>

#define pageSize 4096

#define divRoundUp(x, y) (x + ( y - 1)) / y
#define alignUp(x, y) divRoundUp(x, y) * y

namespace Pmm {
    void  init();
    void* alloc(size_t);
    void  free(void*, size_t);
}
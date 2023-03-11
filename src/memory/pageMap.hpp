#pragma once

#include <stdint.h>

namespace pageMap {
    typedef struct {
        uint64_t PDP;
        uint64_t PD;
        uint64_t PT;
        uint64_t P;
    } PMInfo;

    PMInfo index(uint64_t vaddr);
};
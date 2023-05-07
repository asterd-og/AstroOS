#pragma once

#include <stdint.h>
#include <stddef.h>

#define MAGIC 0xBADFACADE

namespace Heap {
    typedef struct {
        bool used;
        uint32_t size;
        uint32_t magic;
    } Block;

    void init();
    void* alloc(size_t size);
    void free(void* ptr);
}

void* malloc(size_t size);
void free(void* ptr);
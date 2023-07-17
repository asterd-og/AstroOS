#include <memory/heap.hpp>
#include <kernel/kernel.hpp>
#include <lib/string.hpp>
#include <sys/serial.hpp>
#include <memory/pmm.hpp>

namespace Heap {
    void init() {
    }

    void* alloc(size_t _size) {
        Pmm::alloc(1);
        return Pmm::alloc((_size - 1) / 4096 + 1);
    }

    void free(void* ptr) {
    }
}

void* malloc(size_t size) {
    return Heap::alloc(size);
}

void free(void* ptr) {
    Heap::free(ptr);
}

void *operator new(size_t size)
{
    return malloc(size);
}

void *operator new[](size_t size)
{
    return malloc(size);
}

void operator delete(void *ptr)
{
    free(ptr);
}

void operator delete[](void *ptr)
{
    free(ptr);
}
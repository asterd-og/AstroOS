#include <memory/heap.hpp>
#include <kernel/kernel.hpp>
#include <lib/string.hpp>
#include <sys/serial.hpp>

namespace Heap {
    uint64_t addr;
    uint64_t addrPtr;
    uint64_t size;

    uint64_t getMemSize() {
        static uint64_t size = 0;
        if (size > 0) return size;
        for (uint64_t i = 0; i < memRes->entry_count; i++) {
            size += memRes->entries[i]->length;
		}
        return size;
    }

    void init() {
        uint64_t lastSize = 0;
        for (uint64_t i = 0; i < memRes->entry_count; i++) {
			if (memRes->entries[i]->type == LIMINE_MEMMAP_USABLE ||
				memRes->entries[i]->type == LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE &&
                memRes->entries[i]->length >= getMemSize()) {
                    if (memRes->entries[i]->length > lastSize) {
                        addr = memRes->entries[i]->base;
                        size = memRes->entries[i]->length;
                        lastSize = size;
                    }
			}
        }
        addrPtr = addr;
    }

    void* alloc(size_t _size) {
        if (_size >= size) {
            io.print("Alloc: Size too big.\n");
            return nullptr;
        }
        Block* block = (Block*)addrPtr;
        if (block->used == true && block->magic == MAGIC) {
            while (true) {
                addrPtr += block->size + sizeof(Block);
                if (addrPtr >= size) {
                    io.print("Alloc: Didn't find free block.\n");
                    return nullptr;
                }
                block = (Block*)addrPtr;
                if (block->used == false || block->magic != MAGIC)
                    break;
            }
        }

        block->used = true;
        block->magic = MAGIC;
        block->size = _size;

        addrPtr += sizeof(Block);

        return (void*)addrPtr;
    }

    void free(void* ptr) {
        Block* block = (Block*)((uint64_t)ptr - sizeof(Block));
        block->used = false;
        block->magic = 0;
        block->size = 0;
        ptr = nullptr;
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
// PMM Using a stack-based approach
// No slab allocator, no bitmap allocator, only stack
// Everything made by astrido

#include <memory/pmm.hpp>
#include <kernel/kernel.hpp>
#include <lib/string.hpp>
#include <lib/printf.h>

namespace Pmm {
    uint64_t* stackAddr = nullptr;
    uint64_t stackSize = 0;
    int top = -1;

    uint64_t higherAddress = 0;
	uint64_t topAddress = 0;

    static volatile struct limine_memmap_request memReq = {
        .id = LIMINE_MEMMAP_REQUEST,
        .revision = 0
    };

    static volatile struct limine_hhdm_request hhdmReq = {
        .id = LIMINE_HHDM_REQUEST,
        .revision = 0
    };

    struct limine_memmap_response* memRes;

    uint64_t getMemSize() {
        static uint64_t size = 0;
        if (size > 0) return size;
        for (uint64_t i = 0; i < memRes->entry_count; i++) {
            size += memRes->entries[i]->length;
		}
        return size;
    }

    void stackPush(uint64_t val) {
        if (top + 1 > stackSize) return;
        top++;
        stackAddr[top] = val;
    }

    void stackPop() {
        if (top <= 0) return;
        top--;
    }

    uint64_t stackTop() {
        return stackAddr[top];
    }
    
    uint64_t getHhdmOff() {
		return hhdmReq.response->offset;
	}

    void init() {
        memRes = memReq.response;

		for (uint64_t i = 0; i < memRes->entry_count; i++) {
			if (memRes->entries[i]->type == LIMINE_MEMMAP_USABLE ||
				memRes->entries[i]->type == LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE) {
				topAddress = memRes->entries[i]->base + memRes->entries[i]->length;
				if (topAddress > higherAddress)
					higherAddress = topAddress;
			}
		}

        for (int i = 0; i < getMemSize(); i += 4096) stackSize++;

		for (uint64_t i = 0; i < memRes->entry_count; i++)
			if (memRes->entries[i]->type == LIMINE_MEMMAP_USABLE) {
				if (memRes->entries[i]->length >= stackSize) {
                    stackAddr = (uint64_t*)(memRes->entries[i]->base + hhdmReq.response->offset);
                    memRes->entries[i]->length -= stackSize;
                    memRes->entries[i]->base += stackSize;
                    for (int i = 0; i < stackSize; i++) {
                        stackAddr[i] = 0;
                    }
                    break;
				}
			}

		for (uint64_t i = 0; i < memRes->entry_count; i++)
			if (memRes->entries[i]->type == LIMINE_MEMMAP_USABLE ||
				memRes->entries[i]->type == LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE) {
				for (uint64_t j = 0; j < memRes->entries[i]->length; j += pageSize) {
                    stackPush(memRes->entries[i]->base + j);
                }
			}
    }

    void* alloc(size_t size) {
        for (int i = 0; i < size; i++) stackPop();
        return (void*)stackTop();
    }

    void free(void* ptr, size_t size) {
        for (int i = 0; i < size; i++) stackPush((uint64_t)ptr + (i * 4096));
        return;
    }
}

#include <memory/pmm.hpp>
#include <kernel/kernel.hpp>
#include <lib/string.hpp>
#include <lib/printf.h>

namespace Pmm {
    uint8_t* bitmap;
    size_t bitmapSize;

    uint64_t higherAddress = 0;
	uint64_t topAddress = 0;

    bool inc = false;
    uint64_t index = 0;

    void setBit(int index) {
        bitmap[index / 8] |= (1 << (index % 8));
        // Sets the bit in the index
    }

    void clearBit(int index) {
        bitmap[index / 8] &= ~(1 << (index % 8));
        // This creates a mask, and reverts from 1 to 0
    }

    bool getBit(int index) {
        return (bitmap[index / 8] & (1 << (index % 8)));
    }

    static volatile struct limine_memmap_request memReq = {
        .id = LIMINE_MEMMAP_REQUEST,
        .revision = 0
    };

    void init() {
        struct limine_memmap_response* memRes = memReq.response;

		for (uint64_t i = 0; i < memRes->entry_count; i++) {
			if (memRes->entries[i]->type == LIMINE_MEMMAP_USABLE ||
				memRes->entries[i]->type == LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE) {
				topAddress = memRes->entries[i]->base + memRes->entries[i]->length;
				if (topAddress > higherAddress)
					higherAddress = topAddress;
			}
		}

		bitmapSize = alignUp((higherAddress / pageSize) / 8, pageSize);

		for (uint64_t i = 0; i < memRes->entry_count; i++)
			if (memRes->entries[i]->type == LIMINE_MEMMAP_USABLE) {
				if (memRes->entries[i]->length >= bitmapSize) {
					bitmap = (uint8_t*)(memRes->entries[i]->base + hhdmOff);
					memset(bitmap, 0xFF, bitmapSize);
					break;
				}
			}

		for (uint64_t i = 0; i < memRes->entry_count; i++)
			if (memRes->entries[i]->type == LIMINE_MEMMAP_USABLE ||
				memRes->entries[i]->type == LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE) {
				for (uint64_t j = 0; j < memRes->entries[i]->length; j += pageSize) {
					clearBit((memRes->entries[i]->base + j) / pageSize);
				}
			}
    }

    uint64_t findFree(size_t size) {
        if (inc) {
            inc = false;
            return -1;
        }
        for (uint64_t i = 0; i < size;) {
            if (index > bitmapSize) {
                if (inc == true) {
                    inc = false;
                    return -1;
                } else {
                    inc = true;
                    return findFree(size);
                }
            } else if (getBit(i + index) == 0) {
                i++;
                continue;
            } else {
                index++;
                i = 0;
                continue;
            }
        }
        return index;
    }

    void* alloc(size_t size) {
        uint64_t idx = findFree(size);
        if (idx == -1) {
            return (void*)-1;
        }

        for (uint64_t i = index; i < index + size; i++)
            setBit(i);
        
        return (void*)((index * pageSize) + bitmap);
    }

    void free(void* ptr, size_t size) {
        uint64_t idx = (uint64_t)ptr / pageSize;
        for (int i = idx; i < idx + size; i++)
            clearBit(i);
        return;
    }
}
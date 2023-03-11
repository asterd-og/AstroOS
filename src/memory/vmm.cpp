#include <memory/vmm.hpp>
#include <memory/pageMap.hpp>
#include <memory/pageTable.hpp>
#include <memory/pmm.hpp>
#include <lib/string.hpp>
#include <video/framebuffer.hpp>

namespace Vmm {
    PT* PML4;
    pageTable ptm(PML4);

    void init() {
        PML4 = (Vmm::PT*)Pmm::alloc(1);
        memset(PML4, 0, 4096);

        // Here we map the whole memory map to it's address
        // We also need to make sure we mapped the FB addr!
        for (uint64_t i = 0; i < Pmm::getMemSize(); i += 4096) {
            ptm.mapAddr((void*)i, (void*)i);
        }

        uint64_t fBase = (uint64_t)Vbe.address;
        uint64_t fSize = 1024000 + 4096;
        for (uint64_t i = fBase; i < fBase + fSize; i += 4096) {
            ptm.mapAddr((void*)i, (void*)i);
        }

        asm ("mov %0, %%cr3" :: "r" (PML4));
    }
}
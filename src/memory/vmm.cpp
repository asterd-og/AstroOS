#include <memory/vmm.hpp>
#include <memory/pageMap.hpp>
#include <memory/pageTable.hpp>
#include <memory/pmm.hpp>
#include <lib/string.hpp>
#include <lib/printf.h>
#include <video/framebuffer.hpp>
#include <sys/serial.hpp>

namespace Vmm {

    void init() {
        PT* PML4;

        PML4 = (Vmm::PT*)Pmm::alloc(1);
        memset(PML4, 0, 4096);

        pageTable ptm = pageTable(PML4);

        printf("Starlight.\n");

        // Here we map the whole memory map to it's virtual address
        for (uint64_t i = 0; i < Pmm::getMemSize(); i += 0x1000) {
            ptm.mapAddr((void*)i, (void*)i);
        }

        //printf("Going to move.\n");

        asm ("mov %0, %%cr3" :: "r" (PML4));
    }
}

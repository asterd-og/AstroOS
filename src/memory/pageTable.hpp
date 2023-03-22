#pragma once

#include <stdint.h>
#include <memory/vmm.hpp>

class pageTable {
    public:
        Vmm::PT* PML4;
        pageTable(Vmm::PT* PML4A);
        void mapAddr(void* vaddr, void* paddr);
};

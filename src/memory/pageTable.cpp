#include <memory/pageTable.hpp>
#include <memory/pageMap.hpp>
#include <memory/pmm.hpp>
#include <lib/string.hpp>
#include <lib/printf.h>

int i = 0;

pageTable::pageTable(Vmm::PT* PML4A) {
    this->PML4 = PML4A;
}

void pageTable::mapAddr(void* vaddr, void* paddr) {
    pageMap::PMInfo idx = pageMap::index((uint64_t)vaddr);
    Vmm::PDE pde;

    pde = PML4->entries[idx.PDP];
    Vmm::PT* pdp;

    if (!pde.present) {
        pdp = (Vmm::PT*)Pmm::alloc(1);
        memset(pdp, 0, 4096);
        pde.addr = (uint64_t)pdp >> 12;
        pde.present = true;
        pde.rw = true;
        PML4->entries[idx.PDP] = pde;
    } else {
        pdp = (Vmm::PT*)((uint64_t)pde.addr << 12);
    }

    pde = pdp->entries[idx.PD];
    Vmm::PT* pd;

    if (!pde.present) {
        pd = (Vmm::PT*)Pmm::alloc(1);
        memset(pd, 0, 4096);
        pde.addr = (uint64_t)pd >> 12;
        pde.present = true;
        pde.rw = true;
        pdp->entries[idx.PD] = pde;
    } else {
        pd = (Vmm::PT*)((uint64_t)pde.addr << 12);
    }

    pde = pd->entries[idx.PT];
    Vmm::PT* pt;

    if (!pde.present) {
        pt = (Vmm::PT*)Pmm::alloc(1);
        memset(pt, 0, 4096);
        pde.addr = (uint64_t)pt >> 12;
        pde.present = true;
        pde.rw = true;
        pd->entries[idx.PT] = pde;
    } else {
        pt = (Vmm::PT*)((uint64_t)pde.addr << 12);
    }
    
	i++;
    
    if (i >= 56000)
		printf("> %d\n", i);

    pde = pt->entries[idx.P];
    pde.addr = (uint64_t)paddr >> 12;
    pde.present = true;
    pde.rw = true;

    pt->entries[idx.P] = pde;
}

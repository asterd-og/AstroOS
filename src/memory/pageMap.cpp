#include <memory/pageMap.hpp>

namespace pageMap {
    PMInfo index(uint64_t vaddr) {
        uint64_t P;
        uint64_t PT;
        uint64_t PD;
        uint64_t PDP;
        
        vaddr >>= 12;    // All of addresses in each page
        // are 12 bits aligned
        P = vaddr & 0x1ff;
        vaddr >>= 9;
        PT = vaddr & 0x1ff;
        vaddr >>= 9;
        PD = vaddr & 0x1ff;
        vaddr >>= 9;
        PDP = vaddr & 0x1ff;

        return {
            .PDP = PDP,
            .PD = PD,
            .PT = PT,
            .P = P
        };
    }
}
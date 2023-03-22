#include <sys/exec/com.hpp>
#include <lib/printf.h>
#include <memory/pmm.hpp>

namespace Com {
	typedef void(*handler)(void);
	handler p;
	
	void test() {
		p();
	}
	
	void start(uint64_t* addr) {
		void* comMem = Pmm::alloc(16); // 65536
		unsigned long long stack_ptr = (unsigned long long)comMem + 65536;
		__asm__ __volatile__("movq %0, %%rsp" : : "m"(stack_ptr));
		void(*comEntry)(void) = (void(*)(void))(addr);
		comEntry();
	}
}

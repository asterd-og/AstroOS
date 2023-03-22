#include <sys/exec/syscalls.hpp>
#include <tables/idt/idt.hpp>
#include <lib/printf.h>

namespace Syscalls {
	void handler(Registers* regs) {
		printf("Syscall executed!\n");
	}
	
	void init() {
		Idt::installSyscalls(handler);
	}
}

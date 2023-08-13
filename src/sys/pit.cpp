#include <sys/pit.hpp>
#include <tables/idt/idt.hpp>
#include <lib/ports.hpp>
#include <lib/printf.h>

namespace Pit {
	void handler(Registers* regs) {
		//pitCounter++;
	}

	void init() {
		outb(0x43, 0x36);
		uint64_t div = 1193180 / 100;
		outb(0x40, static_cast<uint8_t>(div));
		outb(0x40, static_cast<uint8_t>(div >> 8));
		Idt::installHandler(0, handler); 
	}
}
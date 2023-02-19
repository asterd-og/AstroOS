#include <sys/pit.h>
#include <tables/idt/idt.h>
#include <lib/ports.h>
#include <lib/printf.h>

namespace Pit {
    uint64_t pitCounter;

	void handler(Registers* regs) {
		pitCounter++;
	}

	void init() {
		outb(0x43, 0x36);
		uint64_t div = 1193180 / 100;
		outb(0x40, static_cast<uint8_t>(div));
		outb(0x40, static_cast<uint8_t>(div >> 8));
		Idt::installHandler(0, handler); 
	}
}
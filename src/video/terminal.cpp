#include <video/terminal.hpp>
#include <video/framebuffer.hpp>
#include <kernel/limine.h>
#include <lib/string.hpp>
#include <sys/ps2/keyboard.hpp>
#include <lib/printf.h>

namespace Terminal {
	struct limine_terminal_request termReq = {
		.id = LIMINE_TERMINAL_REQUEST,
		.revision = 0
	};

	void init() {
	}
	
    void write(char* str) {
		termReq.response->write(termReq.response->terminals[0], str, 2);
    }
}

extern "C" void _putchar(char c) {
    char str[2] = {c, '\0'};
    Terminal::write(str);
}
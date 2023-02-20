#include <video/terminal.hpp>
#include <video/framebuffer.hpp>
#include <kernel/limine.h>
#include <lib/string.hpp>

namespace Terminal {
    int cx = 32;
	int cy = 32;

    void init() {
        Vbe.clear(0x000000);
		Vbe.drawFillRect(32, 32, Vbe.width - 64, Vbe.height - 64, 0x121212);
    }

    void write(char* str) {
        for (int i = 0; i < strlen(str); i++)
			if (str[i] != '\0') {
				if (str[i] == '\n') {
					cx = 32;
					cy += kernelFont.height + kernelFont.spacing_y;
				} else {
					if (cx >= Vbe.width - 64) {
						cx = 32;
						cy += kernelFont.height + kernelFont.spacing_y;
					} else if (cy >= Vbe.height - 64) {
						Vbe.clear(0);
						Vbe.drawFillRect(32, 32, Vbe.width - 64, Vbe.height - 64, 0x121212);
						cx = 32;
						cy = 32;
					}
					Vbe.drawChar(cx, cy, str[i], 0xFFFFFFFF, kernelFont);
					cx += kernelFont.width + kernelFont.spacing_x;
				}
			}
		Vbe.update();
    }
}

extern "C" void _putchar(char c) {
    char str[2] = {c, '\0'};
    Terminal::write(str);
}
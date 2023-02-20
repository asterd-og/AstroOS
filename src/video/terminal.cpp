#include <video/terminal.hpp>
#include <video/framebuffer.hpp>
#include <kernel/limine.h>
#include <lib/string.hpp>
#include <sys/ps2/keyboard.hpp>
#include <lib/printf.h>

namespace Terminal {
    int cx = 32;
	int cy = 32;
	char buff[512];
	int idx = 0;
	char c = 0;

	const uint32_t bg0 = 0x1d2021;
	const uint32_t bg  = 0x282828;
	const uint32_t fg0 = 0xfbf1c7;

    void init() {
        Vbe.clear(bg0);
		Vbe.drawFillRect(32, 32, Vbe.width - 64, Vbe.height - 64, bg);
    }

	void printWelcome() {
		printf("\n\nAstro OS built-in shell v0.1\n\n");
		printInput();
	}

	void printInput() {
		printf(":> ");
	}

	void update() {
		c = Keyboard::getChar();
		if (c != '\0') {
			if (c == '\n') {
				printf("\n%s\n", buff);
				idx = 0;
				memset(buff, 0, strlen(buff));
				printInput();
			} else if (c == '\b') {
				if (idx > 0) {
					printf("\b");
					idx--;
					buff[idx] = '\0';
				}
			} else {
				printf("%c", c);
				buff[idx] = c;
				idx++;
			}
		}
		c = '\0';
	}

    void write(char* str) {
        for (int i = 0; i < strlen(str); i++)
			if (str[i] != '\0') {
				if (str[i] == '\n') {
					cx = 32;
					cy += kernelFont.height + kernelFont.spacing_y;
				} else if (str[i] == '\b') {
					cx -= (kernelFont.width + kernelFont.spacing_x);
					Vbe.drawFillRect(cx, cy, kernelFont.width + kernelFont.spacing_x, kernelFont.height, bg);
				} else if (str[i] == '\t') {
					cx += (kernelFont.width + kernelFont.spacing_x);
				} else {
					if (cx >= Vbe.width - 64) {
						cx = 32;
						cy += kernelFont.height + kernelFont.spacing_y;
					} else if (cy >= Vbe.height - 64) {
						Vbe.clear(0);
						Vbe.drawFillRect(32, 32, Vbe.width - 64, Vbe.height - 64, bg);
						cx = 32;
						cy = 32;
					}
					Vbe.drawChar(cx, cy, str[i], fg0, kernelFont);
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
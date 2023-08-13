#include <sys/sw/console.hpp>
#include <lib/string.hpp>
#include <sys/ps2/keyboard.hpp>
#include <lib/printf.h>
#include <video/framebuffer.hpp>
#include <desktop/window.hpp>
#include <desktop/tga.hpp>
#include <kernel/kernel.hpp>

namespace Console {
    char buffer[512];
    int idx;
    char c;
    int count = 0;

    Window win;

    int cx = 0;
    int cy = 0;

    int fg = WHITE;
    int bg = 0xA0000000;

    Tga* astro;

    void printc(char c) {
        if (c == '\n') {
            cx = 0;
            cy += 8;
        } else if (c == '\b') {
            cx -= 8;
            win.gc.drawFillRect(cx, cy, 8, 8, bg);
        } else {
            if (cx + 8 > win.w) {
                cx = 0;
                cy += 8;
            }
            win.gc.drawChar(cx, cy, c, fg);
            cx += 8;
        }
    }

    void print(char* str) {
        for (int i = 0; i < strlen(str); i++)
            printc(str[i]);
    }

    void cursorErase() {
        win.gc.drawFillRect(cx, cy + 6, 8, 2, bg);
    }

    void cursorDraw() {
        win.gc.drawFillRect(cx, cy + 6, 8, 2, WHITE);
    }

    void init() {
        win.create("Console", 640, 480, 0, 0, true, true);
        win.gc.clear(bg);
        astro = tgaLoad((unsigned char*)findModule(1)->address, findModule(1)->size);
        printInput();
        cursorDraw();
    }

    void printInput() {
        print("> ");
    }

    void about() {
        win.gc.drawTga(cx, cy, astro);
        cx += 186;
        print("AstroOS is a 64 bit Operating System made by Astrido");
        cy += 186;
        cx = 0;
        print("\n");
    }

    void update() {
        c = Keyboard::getChar();
        if (c != '\0') {
            cursorErase();
            if (c == '\n') {
                print("\n");
                if (!strcmp(buffer, "about")) about(); // TODO: hardcoded for now it's 3 am, I will make a cmd handler later.
                else {
                    print(buffer);
                    print("\n");
                }
                memset(buffer, 0, strlen(buffer));
                idx = 0;
                count++;
                printInput();
            } else if (c == '\b') {
                if (idx > 0) {
                    idx--;
                    buffer[idx] = 0;
                    printc('\b');
                }
            } else {
                printc(c);
                buffer[idx] = c;
                idx++;
            }
            cursorDraw();
        }
    }

    void winUpdate() {
        win.update();
        win.draw();
    }
}

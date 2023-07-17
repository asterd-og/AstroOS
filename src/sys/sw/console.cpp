#include <sys/sw/console.hpp>
#include <lib/string.hpp>
#include <sys/ps2/keyboard.hpp>
#include <lib/printf.h>
#include <video/framebuffer.hpp>
#include <desktop/window.hpp>

namespace Console {
    char buffer[512];
    int idx;
    char c;
    int count = 0;

    Window win;

    int cx = 0;
    int cy = 0;

    int fg = cyan;
    int bg = black;

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

    void printfgc(char* str, ...) {
        va_list va;
        va_start(va, str);
        char buffer[2048];
        const int ret = vsnprintf_(buffer, strlen(str)+1, str, va);
        va_end(va);
        for (int i = 0; i < strlen(buffer); i++)
            printc(buffer[i]);
    }

    void print(char* str) {
        for (int i = 0; i < strlen(str); i++)
            printc(str[i]);
    }

    void cursorErase() {
        win.gc.drawFillRect(cx, cy, 8, 8, bg);
    }

    void cursorDraw() {
        win.gc.drawFillRect(cx, cy, 8, 8, red);
    }

    void init() {
        win.create("Console", 400, 200, 10, 30);
        printInput();
        cursorDraw();
    }

    void printInput() {
        print("> ");
    }

    void update() {
        c = Keyboard::getChar();
        if (c != '\0') {
            cursorErase();
            if (c == '\n') {
                print("\n");
                print(buffer);
                print("\n");
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

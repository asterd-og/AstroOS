#include <sys/sw/console.hpp>
#include <lib/string.hpp>
#include <sys/ps2/keyboard.hpp>
#include <lib/printf.h>

namespace Console {
    char buffer[512];
    int idx;
    char c;
    int count = 0;

    void init() {
        printf("\nConsole Initialised.\n");
        printInput();
    }

    void printInput() {
        printf("%d> ", count);
    }

    void update() {
        c = Keyboard::getChar();
        if (c != '\0') {
            if (c == '\n') {
                printf("\n%s\n", buffer);
                memset(buffer, 0, strlen(buffer));
                idx = 0;
                count++;
                printInput();
            } else if (c == '\b') {
                if (idx > 0) {
                    idx--;
                    buffer[idx] = 0;
                    printf("\b \b");
                }
            } else {
                printf("%c", c);
                buffer[idx] = c;
                idx++;
            }
        }
    }
}

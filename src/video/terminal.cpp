#include <video/terminal.h>
#include <kernel/limine.h>

namespace Terminal {
    static struct limine_terminal* term;
    static struct limine_terminal_response* termRes;

    static volatile struct limine_terminal_request termReq = {
        .id = LIMINE_TERMINAL_REQUEST,
        .revision = 0
    };

    void init() {
        termRes = termReq.response;
        term = termRes->terminals[0];
    }

    size_t strlen(char* str) {
        int i = 0; while(*str++) i++;
        return i;
    }

    void write(char c) {
        char s[2] = {c, '\0'};
        termRes->write(term, s, 2);
    }
}

extern "C" void _putchar(char c) {
    Terminal::write(c);
}
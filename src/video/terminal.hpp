#pragma once

#include <stdint.h>
#include <stddef.h>

namespace Terminal {
    void init();
    void printInput();
    void printWelcome();
    void update();
    void write(char*);
}
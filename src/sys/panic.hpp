#pragma once

#include <stdint.h>
#include <tables/idt/idt.hpp>

void panic(char*, Registers*);
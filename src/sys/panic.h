#pragma once

#include <stdint.h>
#include <tables/idt/idt.h>

void panic(char*, Registers*);
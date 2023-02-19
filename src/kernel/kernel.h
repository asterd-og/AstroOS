#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <kernel/limine.h>

static constexpr uint64_t STACK_SIZE = 0x4000;
extern uint8_t *kernel_stack;
extern uint64_t hhdmOff;

void kmain();
void kloop();

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <kernel/limine.h>

static constexpr uint64_t STACK_SIZE = 0x4000;
extern uint8_t *kernel_stack;
extern uint64_t hhdmOff;

extern volatile struct limine_memmap_request memReq;
extern struct limine_memmap_response* memRes;

void kmain();
void kloop();
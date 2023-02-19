#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <kernel/limine.h>

static constexpr uint64_t STACK_SIZE = 0x4000;
extern uint8_t *kernel_stack;
extern uint64_t hhdm_offset;

extern volatile struct limine_memmap_request memmap_request;
extern volatile struct limine_hhdm_request hhdm_request;
extern volatile struct limine_smp_request smp_request;
extern volatile struct limine_module_request module_request;
extern volatile struct limine_kernel_file_request kernel_file_request;
extern volatile struct limine_kernel_address_request kernel_address_request;
extern volatile struct limine_rsdp_request rsdp_request;
limine_file *find_module(char *name);
void kmain();
void kloop();

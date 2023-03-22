#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct {
	uint64_t r15;
	uint64_t r14;
	uint64_t r13;
	uint64_t r12;
	uint64_t r11;
	uint64_t r10;
	uint64_t r9;
	uint64_t r8;
	uint64_t rsi;
	uint64_t rdi;
	uint64_t rbp;
	uint64_t rdx;
	uint64_t rcx;
	uint64_t rbx;
	uint64_t rax;
	uint64_t intNo;
	uint64_t err;
	uint64_t rip;
	uint64_t cs;
	uint64_t rflags;
	uint64_t rsp;
	uint64_t ss;
} __attribute__((packed)) Registers;

namespace Idt {
	typedef struct {
		uint16_t offsetLow;
		uint16_t cs;
		uint8_t ist;
		uint8_t attr;
		uint16_t offsetMid;
		uint32_t offsetHigh;
		uint32_t reserved;    // always be zero
	} __attribute__((packed)) IdtEntry;
	
	typedef struct {
		uint16_t limit;
		uint64_t base;
	} __attribute__((packed)) IdtR;

	typedef void(*handler)(Registers*);

	void init();
	void setDesc(uint8_t idx, void* isr);
	void installHandler(uint8_t idx, handler hand);
	void installSyscalls(handler hand);
}

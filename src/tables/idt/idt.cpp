#include <tables/idt/idt.h>
#include <lib/printf.h>
#include <sys/pic.h>

namespace Idt {
    static const char *messages[32] = {
        "Division by zero",
        "Debug",
        "Non-maskable interrupt",
        "Breakpoint",
        "Detected overflow",
        "Out-of-bounds",
        "Invalid opcode",
        "No coprocessor",
        "Double fault",
        "Coprocessor segment overrun",
        "Bad TSS",
        "Segment not present",
        "Stack fault",
        "General protection fault",
        "Page fault",
        "Unknown interrupt",
        "Coprocessor fault",
        "Alignment check",
        "Machine check",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
    };

    extern "C" void* intVector[];

    __attribute__((aligned(0x10))) 
    static IdtEntry idt[256];

    handler handlers[16];

    void init() {
		__asm__ volatile ("cli");

        static IdtR idtr = {
            .base = (uintptr_t)&idt[0],
            .limit = (uint16_t)sizeof(IdtEntry) * 256 - 1
        };

        for (uint8_t idx = 0; idx < 47; idx++)
            setDesc(idx, intVector[idx]);
        
        __asm__ volatile("lidt %0" : : "m"(idtr));
        Pic::init();
        __asm__ volatile("sti");
    }
	
    void setDesc(uint8_t idx, void* isr) {
        IdtEntry* entry = &idt[idx];

        entry->offsetLow = (uint64_t)isr & 0xFFFF;
        entry->cs = 0x28;
        entry->ist = 0;
        entry->attr = 0x8E;
        entry->offsetMid = ((uint64_t)isr >> 16) & 0xFFFF;
        entry->offsetHigh = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
        entry->reserved = 0;
    }

    void installHandler(uint8_t idx, handler hand) {
        handlers[idx] = hand;
    }

    extern "C" void intHandler(Registers* regs) {
        if (regs->intNo < 32) {
            __asm__ volatile("cli");

            printf("exception has occurred!\n%s\n\n", messages[regs->intNo]);
	        printf("dump:\n");
	        printf("sizeof: %lu\n", sizeof(*regs));
	        printf("rax=%016lX rbx=%016lX rcx=%016lX rdx=%016lX\n", regs->rax, regs->rbx, regs->rcx, regs->rdx);
	        printf("rdi=%016lX rsi=%016lX rbp=%016lX rsp=%016lX\n", regs->rdi, regs->rsi, regs->rbp, regs->rsp);
	        printf("r8=%016lX r9=%016lX r10=%016lX r11=%016lX\n", 	regs->r8,  regs->r9,  regs->r10, regs->r11);
	        printf("r12=%016lX r13=%016lX r14=%016lX r15=%016lX\n", regs->r12, regs->r13, regs->r14, regs->r15);

	        printf("rip=%016lX rflags=%016lX rsp=%016lX\n", regs->rip, regs->rflags, regs->rsp);
	        printf("cs=%016lX ss=%016lX\n", regs->cs, regs->ss);
	        printf("int_no=%016lX err_code=%016lX\n", regs->intNo, regs->err);

            for (;;) __asm__ volatile("hlt");
        } else {
            if ((uintptr_t*)handlers[regs->intNo - 32] != nullptr) {
                handlers[regs->intNo - 32](regs);
            }
            Pic::eoi(regs->intNo - 32);
        }
    }
}
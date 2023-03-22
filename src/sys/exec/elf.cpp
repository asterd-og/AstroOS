#include <sys/exec/elf.hpp>
#include <lib/printf.h>
#include <lib/string.hpp>

namespace Elf {
	void start(uint64_t* addr) {
		Elf64_Ehdr* ehdr = (Elf64_Ehdr*)addr;
		if (ehdr->e_ident[0] != 0x7f && ehdr->e_ident[1] != 'E' && ehdr->e_ident[2] != 'L' &&
			ehdr->e_ident[3] != 'F') {
				printf("Could not open ELF file. Invalid magic.\n");
				return;
			} else {
				printf("Valid ELF magic headers.\n");
			}
		
		if (ehdr->e_ident[4] != 2) {
			printf("Could not open ELF file. Not a 64 bit program.\n");
			return;
		}
		
		if (ehdr->e_type != 2) {
			printf("Could not open ELF file. Not an executable file. %d\n", ehdr->e_type);
			return;
		}
		
		void (*entryPoint)(void) = (void (*)(void)) ehdr->e_entry;
		entryPoint();
	}
}

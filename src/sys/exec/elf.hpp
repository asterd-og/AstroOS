#pragma once

#include <stdint.h>
#include <stddef.h>

namespace Elf {
	typedef struct {
		uint8_t  e_ident[16];    // ELF identification bytes
		uint16_t e_type;         // Object file type
		uint16_t e_machine;      // Architecture
		uint32_t e_version;      // Object file version
		uint64_t e_entry;        // Entry point virtual address
		uint64_t e_phoff;        // Program header table file offset
		uint64_t e_shoff;        // Section header table file offset
		uint32_t e_flags;        // Processor-specific flags
		uint16_t e_ehsize;       // ELF header size in bytes
		uint16_t e_phentsize;    // Size of each program header table entry
		uint16_t e_phnum;        // Number of entries in the program header table
		uint16_t e_shentsize;    // Size of each section header table entry
		uint16_t e_shnum;        // Number of entries in the section header table
		uint16_t e_shstrndx;     // Index of the section header table entry containing the section names
	} Elf64_Ehdr;
	
	// Thanks https://www.uclibc.org/docs/elf-64-gen.pdf
	
	void start(uint64_t* addr);
}

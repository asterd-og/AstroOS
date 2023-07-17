ISONAME = AstroOS.iso
CXX := clang++

KOUT = kernel.elf

LD := ld.lld

LVL5_PAGING = 0

# User controllable linker flags. We set none by default.
LDFLAGS ?=

# Internal C flags that should not be changed by the user.
CXXFLAGS = -O2 -pipe -Wall -Wextra -ffreestanding \
		 -fpermissive -Isrc/ -DLVL5_PAGING=$(LVL5_PAGING) -g -Wno-c99-designator -Wno-unused-parameter -Wno-deprecated-volatile -Wno-register

override INTERNALCPPFLAGS :=   \
	-target x86_64-pc-none-elf \
	-std=gnu++20		       \
	-ffreestanding             \
	-fno-exceptions            \
	-fno-stack-protector       \
	-fno-omit-frame-pointer    \
	-fno-rtti                  \
	-fno-pic                   \
	-mabi=sysv                 \
	-mno-80387                 \
	-mno-mmx                   \
	-mno-3dnow                 \
	-mno-sse2                  \
	-mno-red-zone              \
	-mcmodel=kernel

# Internal linker flags that should not be changed by the user.
override INTERNALLDFLAGS :=    \
	-Tconf/linker.ld       \
	-nostdlib              \
	-zmax-page-size=0x1000 \
	-static

override CPPFILES := $(shell find . -name "*.cpp")
override ASMFILES := $(shell find . -name "*.asm")
override OBJ := $(CPPFILES:.cpp=.o)
override OBJ += $(ASMFILES:.asm=_asm.o)

.PHONY: all
all: $(ISONAME) run
	rm -rf iso_root $(OBJ) $(KOUT) $(ISONAME)

run:
	mv AstroOS.iso /mnt/c/Users/Administrator/AstroOS.iso
	cmd.exe /c qemu-system-x86_64 -M q35 -m 2G -smp 1 -s -cdrom C:/Users/Administrator/AstroOS.iso -boot d -no-reboot -no-shutdown --serial stdio

run-uefi: ovmf-x64
	qemu-system-x86_64 -M q35 -m 2G -bios /usr/share/ovmf/OVMF.fd -cdrom $(ISONAME) -boot d --enable-kvm --serial stdio

ovmf-x64:
	mkdir -p ovmf-x64
	cd ovmf-x64 && curl -o OVMF-X64.zip https://efi.akeo.ie/OVMF/OVMF-X64.zip && 7z x OVMF-X64.zip
	rm ovmf-x64/OVMF-X64.zip
	rm ovmf-x64/readme.txt

uefi: $(ISONAME) run-uefi clean

limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v4.x-branch-binary --depth=1
	make -C limine

kernel: $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) $(INTERNALLDFLAGS) -o $(KOUT)

%.o: %.cpp
	@echo Compiling $< to $@
	@$(CXX) $(CXXFLAGS) $(INTERNALCPPFLAGS) -c $< -o $@

%_asm.o: %.asm
	@echo Compiling $< to $@
	@nasm -f elf64 $< -o $@

initrd:
	@echo Generating init ramdisk!
#	@tar czf  bin/initrd.img -C bin/fs/ ./ --format=ustar

mkdisk:
	@dd if=/dev/zero of=disk.img bs=1k count=100000
	@mkfs -t ext2 -i 1024 -b 1024 -F disk.img

$(ISONAME): limine kernel initrd
	@rm -fr iso_root
	@mkdir -p iso_root
	@cp $(KOUT) \
		conf/limine.cfg limine/limine.sys limine/limine-cd.bin limine/limine-cd-efi.bin iso_root/
	@xorriso -as mkisofs -b limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-cd-efi.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o $(ISONAME)
	@limine/limine-deploy $(ISONAME)
	@rm -rf iso_root

clean:
	rm -rf iso_root $(ISONAME) $(OBJ) $(KOUT)

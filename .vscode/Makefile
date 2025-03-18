# C source files
C_SOURCES = $(wildcard kernel/src/*.c debug/src/*.c drivers/src/*.c cpu/src/*.c libc/src/*.c)
# Header files
HEADERS = $(wildcard kernel/include/*.h drivers/include/*.h cpu/include/*.h libc/include/*.h)
# ASM files
ASM = $(wildcard cpu/src/asm/*.asm)
# Object files
OBJ = ${C_SOURCES:.c=.o} ${ASM:.asm=.o}

# Compiler and tools
CC = i386-elf-gcc
GDB = i386-elf-gdb

# Compiler flags
CFLAGS = -g -O0 -ffreestanding -Wall -Wextra -fno-exceptions -m32 -Wimplicit-function-declaration -Wchar-subscripts -Wint-conversion

# Build option: Select boot folder or Multiboot folder
BOOT_TYPE ?= boot  # Default to 'boot'. Set BOOT_TYPE=Multiboot to use the Multiboot folder.

# Default target
kai-os.bin: $(BOOT_TYPE)/bootsect.bin kernel.bin
	cat $^ > kai-os.bin
	cat $^ > iso/kai-os.bin
	genisoimage -o kai-os.iso -b kai-os.bin -no-emul-boot -boot-load-size 4 -boot-info-table iso/

# Linking the kernel
kernel.bin: $(BOOT_TYPE)/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Kernel ELF for debugging
kernel.elf: $(BOOT_TYPE)/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^

# Rule to build bootsect.o for the Multiboot folder
Multiboot/bootsect.o: Multiboot/bootsect.asm
	nasm $< -f elf -o $@

# Rule to link the Multiboot bootsector to a binary
Multiboot/bootsect.bin: Multiboot/bootsect.o
	i386-elf-ld -o $@ -Ttext 0x7C00 $^ --oformat binary

# Rule to build the boot sector for the boot folder
boot/bootsect.bin: boot/bootsect.asm
	nasm $< -f bin -o $@

# Rule to build kernel entry for the boot folder
boot/kernel_entry.o: boot/kernel_entry.asm
	nasm $< -f elf -o $@

# Run the OS in QEMU
run: kai-os.bin
	qemu-system-i386 -fda kai-os.bin

# Debugging with QEMU and GDB
debug: kai-os.bin kernel.elf
	qemu-system-i386 -s -fda kai-os.bin -d guest_errors,int &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Rules for building object files from .c files
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

# Rules for building object files from assembly files
%.o: %.asm
	nasm $< -f elf -o $@

# Clean up build artifacts
clean:
	rm -rf *.bin *.dis *.o kai-os.bin *.elf
	rm -rf iso/*.bin kai-os.iso kernel/src/*.o boot/*.bin drivers/src/*.o debug/src/*.o boot/*.o Multiboot/*.o cpu/src/*.o cpu/src/asm/*.o libc/src/*.o Multiboot/*.bin

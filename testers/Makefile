# Source files
C_SOURCES = $(wildcard kernel/src/*.c kernel/shell/src/*.c debug/src/*.c drivers/src/*.c cpu/src/*.c libc/src/*.c)
HEADERS = $(wildcard kernel/include/*.h kernel/shell/include/*.h drivers/include/*.h cpu/include/*.h libc/include/*.h)
ASM = $(wildcard cpu/src/asm/*.asm)

# Object files
OBJ = ${C_SOURCES:.c=.o} ${ASM:.asm=.o}

# Compiler and tools
CC = gcc
LD = ld
NASM = nasm
GDB = gdb

# Compiler flags
CFLAGS = -Iinc -ggdb -c -ffreestanding -mno-red-zone -mcmodel=kernel

# Boot type (boot or Multiboot)
BOOT_TYPE ?= boot  # Default to 'boot'. Set BOOT_TYPE=Multiboot to use the Multiboot folder.

# Default target
kai-os.bin: $(BOOT_TYPE)/bootsect.bin kernel.bin
	cat $^ > kai-os.bin
	cat $^ > iso/kai-os.bin
	genisoimage -o kai-os.iso -b kai-os.bin -no-emul-boot -boot-load-size 4 -boot-info-table iso/

# Linking the kernel
kernel.bin: $(BOOT_TYPE)/kernel_entry.o ${OBJ} linker.ld
	${LD} -o $@ -T linker.ld --oformat binary $^

# Kernel ELF for debugging
kernel.elf: $(BOOT_TYPE)/kernel_entry.o ${OBJ} linker.ld
	${LD} -o $@ -T linker.ld $^

# Rule to build boot sector for Multiboot
Multiboot/bootsect.o: Multiboot/bootsect.asm
	${NASM} $< -f elf64 -o $@

Multiboot/bootsect.bin: Multiboot/bootsect.o
	${LD} -o $@ -Ttext 0x7C00 --oformat binary $^

# Rule to build boot sector for boot folder
boot/bootsect.bin: boot/bootsect.asm
	${NASM} $< -f bin -o $@

# Rule to build kernel entry for boot folder
boot/kernel_entry.o: boot/kernel_entry.asm
	${NASM} $< -f elf64 -o $@

# Run the OS in QEMU
run: kai-os.bin
	qemu-system-x86_64 -drive format=raw,file=kai-os.bin

# Debugging with QEMU and GDB
debug: kai-os.bin kernel.elf
	qemu-system-x86_64 -s -drive format=raw,file=kai-os.bin -d guest_errors,int &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Rules for building object files from .c files
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

# Rules for building object files from assembly files
%.o: %.asm
	${NASM} $< -f elf64 -o $@

# Clean up build artifacts
clean:
	rm -rf *.bin *.dis *.o kai-os.bin *.elf
	rm -rf iso/*.bin kai-os.iso kernel/src/*.o boot/*.bin drivers/src/*.o debug/src/*.o boot/*.o Multiboot/*.o cpu/src/*.o cpu/src/asm/*.o libc/src/*.o Multiboot/*.bin kernel/shell/src/*.o

# Find source files
C_SOURCES = $(shell find kernel/src/ debug/src/ drivers/src/ cpu/src/ libc/src/ -type f -name '*.c')
ASM_SOURCES = $(shell find cpu/src/asm/ -type f -name '*.asm')

# Object files
OBJC = $(C_SOURCES:.c=.o)
OBJS = $(ASM_SOURCES:.asm=.o)

# Compiler and tools
CC = i386-elf-gcc
LD = i386-elf-ld
NASM = nasm
GDB = i386-elf-gdb

# Compiler flags
CFLAGS = -g -O0 -ffreestanding -Wall -Wextra -fno-exceptions -m32 \
         -Wimplicit-function-declaration -Wchar-subscripts -Wint-conversion

# Boot type selection (default: boot)
BOOT_TYPE ?= boot

# Default build target
all: clean kai-os.bin clean

debug: clean kai-os-debug.bin clean
gdb: clean kai-os-gdb.bin clean

# Bootable image targets
kai-os.bin: boot/bootsect.bin kernel.bin
	cat $^ > kai-os.bin
	cat $^ > iso/kai-os.bin
	genisoimage -o kai-os.iso -b kai-os.bin -no-emul-boot -boot-load-size 4 -boot-info-table iso/

kai-os-debug.bin: kai-os.bin
	qemu-system-i386 -hda kai-os.bin -monitor stdio

kai-os-gdb.bin: kai-os.bin
	qemu-system-i386 -S -s -hda kai-os.bin

# Kernel binary
kernel.bin: boot/kernel_entry.o ${OBJC} ${OBJS}
	${LD} -o $@ -Ttext 0x8000 $^ --oformat binary

# Kernel ELF for debugging
kernel.elf: boot/kernel_entry.o ${OBJC} ${OBJS}
	${LD} -o $@ -Ttext 0x8000 $^

# Build boot sector (Multiboot)
Multiboot/bootsect.o: Multiboot/bootsect.asm
	${NASM} $< -f elf -o $@

Multiboot/bootsect.bin: Multiboot/bootsect.o
	${LD} -o $@ -Ttext 0x7C00 $^ --oformat binary

# Build boot sector (boot folder)
boot/bootsect.bin: boot/bootsect.asm
	${NASM} $< -f bin -o $@

# Build kernel entry
boot/kernel_entry.o: boot/kernel_entry.asm
	${NASM} $< -f elf -o $@

# Run in QEMU
run: kai-os.bin
	qemu-system-i386 -fda kai-os.bin

# Debugging with QEMU and GDB
debug: kai-os.bin kernel.elf
	qemu-system-i386 -s -fda kai-os.bin -d guest_errors,int &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Compile C files
%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

# Compile Assembly files
%.o: %.asm
	${NASM} $< -f elf -o $@

%.bin: %.asm
	${NASM} -O0 -f bin -o $@ $<

# Clean up
clean:
	rm -rf *.bin *.dis *.o *.elf kai-os.bin kai-os.iso
	rm -rf iso/*.bin kernel/src/*.o drivers/src/*.o debug/src/*.o boot/*.o Multiboot/*.o
	rm -rf cpu/src/*.o cpu/src/asm/*.o libc/src/*.o Multiboot/*.bin boot/*.bin

# Collect C source files
C_SOURCES = $(wildcard kernel/*.c drivers/src/*.c cpu/src/*.c libc/src/*.c)
# Collect header files
HEADERS = $(wildcard kernel/*.h drivers/include/*.h cpu/include/*.h libc/include/*.h)
# Object files
OBJ = ${C_SOURCES:.c=.o} cpu/src/asm/interrupts.o cpu/src/asm/stub.o

# Compiler and tools
CC = i386-elf-gcc
GDB = i386-elf-gdb

# Compiler flags
CFLAGS = -g -ffreestanding -Wall -Wextra -fno-exceptions -m32 -Wimplicit-function-declaration -Wchar-subscripts

# Default target
kai-os.bin: boot/bootsect.bin kernel.bin
	cat $^ > kai-os.bin

# Linking the kernel
kernel.bin: boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Kernel ELF for debugging
kernel.elf: boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^

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

# Rules for building binary files from assembly files
%.bin: %.asm
	nasm $< -f bin -o $@

# Clean up build artifacts
clean:
	rm -rf *.bin *.dis *.o kai-os.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/src/*.o boot/*.o cpu/src/*.o libc/src/*.o

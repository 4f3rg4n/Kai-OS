#!/bin/bash

# Compile the C kernel file with 32-bit architecture
gcc -m32 -ffreestanding -c kernel.c -o kernel.o

# Assemble the kernel entry file with 32-bit format
nasm kernel_entry.asm -f elf32 -o kernel_entry.o

# Link the kernel object files into a binary, specifying the linker script for 32-bit
ld -m elf_i386 -o kernel.bin -Ttext 0x1000 kernel_entry.o kernel.o --oformat binary

# Assemble the boot sector file
nasm -f bin boot.asm -o boot.bin

# Combine the boot sector and kernel into a single disk image
cat boot.bin kernel.bin > os-image

# Run the OS image in QEMU
qemu-system-i386 os-image

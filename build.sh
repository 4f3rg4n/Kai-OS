#nasm -f elf32 boot.asm -o boot.o
#gcc -m32 -c kernel.c -o kernel.o
#gcc -m32 -c ./libs/src/stdlib.c -o ./libs/src/stdlib.o
#gcc -m32 -c ./drivers/src/vga.c -o ./drivers/src/vga.o

#ld -m elf_i386 -T link.ld -o ./bin/kernel.bin boot.o kernel.o ./libs/src/stdlib.o ./drivers/src/vga.o
#qemu-system-x86_64 -kernel ./bin/kernel.bin

make clean
make run
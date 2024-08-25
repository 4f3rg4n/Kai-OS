# Compiler and assembler options
ASM = nasm
CC = gcc
LD = ld
QEMU = qemu-system-x86_64

# Compiler and linker flags
ASM_FLAGS = -f elf32
CFLAGS = -m32 -c -fno-stack-protector
LDFLAGS = -m elf_i386 -T link.ld

# Source files
BOOT_SRC = ./boot/boot.asm
KERNEL_SRC = ./kernel/kernel.c

# Directories
LIB_DIR = ./libs/src
DRIVER_DIR = ./drivers/src

# Find all .c files in libs and drivers directories
LIB_SRCS = $(wildcard $(LIB_DIR)/*.c)
DRIVER_SRCS = $(wildcard $(DRIVER_DIR)/*.c)

# Convert source file lists to object file lists (keep object files in their directories)
LIB_OBJS = $(LIB_SRCS:.c=.o)
DRIVER_OBJS = $(DRIVER_SRCS:.c=.o)

# Object files
BOOT_OBJ = ./boot/boot.o
KERNEL_OBJ = ./kernel/kernel.o

# Output binary
KERNEL_BIN = ./bin/kernel.bin

# Targets
all: $(KERNEL_BIN) run

$(BOOT_OBJ): $(BOOT_SRC)
	$(ASM) $(ASM_FLAGS) $(BOOT_SRC) -o $(BOOT_OBJ)

$(KERNEL_OBJ): $(KERNEL_SRC)
	$(CC) $(CFLAGS) $(KERNEL_SRC) -o $(KERNEL_OBJ)

# Compile all libraries and drivers, keeping the object files in their directories
$(LIB_DIR)/%.o: $(LIB_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(DRIVER_DIR)/%.o: $(DRIVER_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Link everything together
$(KERNEL_BIN): $(BOOT_OBJ) $(KERNEL_OBJ) $(LIB_OBJS) $(DRIVER_OBJS)
	$(LD) $(LDFLAGS) -o $(KERNEL_BIN) $(BOOT_OBJ) $(KERNEL_OBJ) $(LIB_OBJS) $(DRIVER_OBJS)

run: $(KERNEL_BIN)
	$(QEMU) -kernel $(KERNEL_BIN)

clean:
	rm -f $(BOOT_OBJ) $(KERNEL_OBJ) $(LIB_OBJS) $(DRIVER_OBJS) $(KERNEL_BIN)

.PHONY: all run clean

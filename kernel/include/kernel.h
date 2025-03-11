#ifndef KERNEL_H
#define KERNEL_H

#include "../../libc/include/stdlib.h"
#include "../../libc/include/memory.h"
#include "../../libc/include/strings.h"
#include "../../cpu/include/idt.h"
#include "../../cpu/include/isr.h"
#include "../../cpu/include/timer.h"
#include "../../drivers/include/keyboard.h"
#include "pmm.h"
#include "vmm.h"
#include "boot.h"
#include "shell.h"
#include "acpi.h"
#include "kerrors.h"

void kmain();

#endif
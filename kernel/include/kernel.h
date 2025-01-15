#ifndef KERNEL_H
#define KERNEL_H

#include "../../libc/include/stdlib.h"
#include "../../libc/include/memory.h"
#include "../../libc/include/strings.h"
#include "../../cpu/include/idt.h"
#include "../../cpu/include/isr.h"
#include "../../cpu/include/timer.h"
#include "../../drivers/include/keyboard.h"
#include "shell.h"

void kmain();

#endif
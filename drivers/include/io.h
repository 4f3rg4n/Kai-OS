#include "../../libc/include/types.h"

// get vlaue from port
u8bit  in8(short port);
u16bit in16(short port);
u32bit in32(short port);

// send value via port
void out8(short port, char byte);
void out16(short port, char byte);
void out32(short port, int word);

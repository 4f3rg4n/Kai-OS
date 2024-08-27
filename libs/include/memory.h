#ifndef MEMORY_H
#define MEMORY_H

void memset(void* src, char value, int bytes);
void memcpy(void* src, void* dst, int bytes);
int memcmp(const void* mem1, const void* mem2, int bytes);

#endif
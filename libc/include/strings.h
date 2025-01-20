#ifndef STRINGS_H
#define STRINGS_H

#include "./stdlib.h"

int strcmp (const char* str1, const char* str2);
int strsize(const char* str1);
char* strcpy(char* dst, const char* src);
char *strcat(char *dst, const char *src);
int puts_c(const char* str, char color);
int puts(const char* str);

#endif
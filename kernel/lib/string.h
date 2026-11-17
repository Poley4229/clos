#pragma once

#include "stddef.h"

// Copy n bytes from dst and puts them in src
void* memcpy(void* dst, const void* src, size_t n);
// memcpy but dst and src can overlap
void* memmove(void* dst, const void* src, size_t n);
// Sets n bytes from dst to c
void* memset(void* dst, int c, size_t n);
// Compares n bytes from a and n bytes from b
int memcmp(const void* a, const void* b, size_t n);
// Counts bytes before the next null terminator
size_t strlen(const char* s);
// Compares 2 null terminated string
int strcmp(const char* s1, const char* s2);

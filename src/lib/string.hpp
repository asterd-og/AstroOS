#pragma once

#include <stdint.h>
#include <stddef.h>

int strlen(char* str);
void swap(char* x, char* y);
char* reverse(char* str, int x, int y);
char* itoa(int value, char* buffer, int radix);
void strcpy(char* dest, char* src);
int strcmp(char* x, char* y);

int memcmp(const void* dest, const void* src, int size);
void* memcpy(void* dest, const void* src, size_t size);
void * memset(void* dest, int data, size_t size);
void* memsetl(void* dest, uint32_t data, size_t size);

#pragma once

#include <stdint.h>
#include <stddef.h>

int strlen(char*);
void swap(char*, char*);
char* reverse(char*, int, int);
char* itoa(int, char*, int);
void strcpy(char*, char*);
int strcmp(char*, char*);

int memcmp(const void*, const void*, int);
void* memcpy(void*, const void*, size_t);
void * memset(void*, int, size_t);
void* memsetl(void*, uint32_t, size_t);

#include <lib/string.hpp>
#include <lib/math.hpp>

int strlen(char* src) {
	int i = 0;
	while(src[i] != '\0')
		i++;
	return i;
}

void swap(char* x, char* y) {
	char t = *x; *x = *y; *y = t;
}

char* reverse(char* str, int x, int y) {
	while (x < y)
		swap(&str[x++], &str[y--]);
	return str;
}

char* itoa(int value, char* buffer, int radix) {
	if (radix < 2 || radix > 32)
		return buffer;
	
	int n = abs(value);

	int i = 0;
	while (n) {
		int r = n % radix;

		if (r >= 10)
			buffer[i++] = 65 + (r - 10);
		else
			buffer[i++] = 48 + r;

		n = n / radix;
	}

	if (i == 0)
		buffer[i++] = '0';

	if (value < 0 && radix == 10)
		buffer[i++] = '-';

	buffer[i] = '\0';
	return reverse(buffer, 0, i - 1);
}

void strcpy(char* dest, char* src) {
	int i = 0;
	while (src[i++] != '\0')
		dest[i] = src[i];
}

int strcmp(char* x, char* y) {
	if (strlen(x) != strlen(y)) return 1;
	int i = 0;
	while (x[i++] != '\0')
		if (y[i] != x[i]) return 1;
	return 0;
}


void* memcpyl(void* dest, const void* src, size_t size) {
    size_t l = size/4;
    asm volatile("cld;rep movsl" : "+D"(dest), "+S"(src), "+c"(l) : : "memory");
    return dest;
}

void* memcpyw(void* dest, const void* src, size_t size) {
    size_t l = size/2;
    asm volatile("cld;rep movsw" : "+D"(dest), "+S"(src), "+c"(l) : : "memory");
    return dest;
}

void* memcpyb(void* dest, const void* src, size_t size) {
    asm volatile("cld;rep movsb" : "+D"(dest), "+S"(src), "+c"(size) : : "memory");
    return dest;
}

void* memcpy(void* dest, const void* src, size_t size) {
    if (size % 4 == 0) return memcpyl(dest, src, size);
    else if (size % 2 == 0) return memcpyw(dest, src, size);
    else return memcpyb(dest, src, size);
}

void* memsetl(void* dest, uint32_t data, size_t size) {
    size_t l = size / 4;
    asm volatile("cld;rep stosl" : "+D"(dest), "+c"(l) : "a"(data) : "memory");
    return dest;
}

void* memsetw(void* dest, uint16_t data, size_t size) {
    size_t l = size/2;
    asm volatile("cld;rep stosw" : "+D"(dest), "+c"(l) : "a"(data) : "memory");
    return dest;
}

void* memsetb(void* dest, uint8_t data, size_t size) {
    asm volatile("cld;rep stosb" : "+D"(dest), "+c"(size) : "a"(data) : "memory");
    return dest;
}

void* memset(void* dest, int data, size_t size) {
    if (size % 4 == 0) return memsetl(dest, data, size);
    else if (size % 2 == 0) return memsetw(dest, data, size);
    else return memsetb(dest, data, size);
}

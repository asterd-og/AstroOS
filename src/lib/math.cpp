#include <lib/math.hpp>

int abs(int x) {
	if (x < 0) return (-1) * x;
	else return x;
}

unsigned int log2(int x) {
	unsigned int res = 0;
	while (x > 1) {
		x >>= 1;
		res++;
	}
	return res;
}

double floor(double x) {
	if (x >= 9223372036854775807 || x <= -9223372036854775807 || x != x) return x;
	long long n = (long long)x;
	double d = (double)n;
	if (d == x || x >= 0) return d;
	return d - 1;
}

int clamp(int x, int y, int z) {
	if (y > z) return 0;
	if (x < y) return 0;
	else if (x > z) return z;
	return x;
}

unsigned int roundTo(unsigned int value, unsigned int roundTo)
{
    return (value + (roundTo - 1)) & ~(roundTo - 1);
}
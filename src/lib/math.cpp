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

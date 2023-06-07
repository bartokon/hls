#include "hbm_ram.hpp"
#include <stdio.h>
#include <math.h>

int main(void) {
	unsigned int indexes[512];
	double data[512][4] = {1};
	double out[512];
	for (auto i = 0; i < 512; ++i) {
		indexes[i] = i % 256;
	}
	hbm_ram(indexes, data, out);
	for (auto i = 0; i < 512; ++i) {
		if (int(out[i]) != (i * 8)) {
			printf("%d: %d \n", i, out[i]);
			return -1;
		}
	}
	return 0;
}

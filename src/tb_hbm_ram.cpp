#include "hbm_ram.hpp"
#include <stdio.h>

int main(void) {
	unsigned int indexes[512];
	double data[512][4];
	double out[512];
	for (auto i = 0; i < 512; ++i) {
		indexes[i] = i % 256;
		for (auto j = 0; j < 4; ++j) {
			data[i][j] = 1;
		}
	}
	hbm_ram(indexes, data, out);
	for (auto i = 0; i < 512; ++i) {
		if (out[i] != 6) {
			printf("%d: %lf \n", i, out[i]);
			return -1;
		}
	}
	return 0;
}

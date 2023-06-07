#include "access_pattern_manual.hpp"

int main(void) {
	double ab[2][512];
	double out[512];
	for (auto i = 0; i < 512; ++i) {
		ab[0][i] = i;
		ab[1][i] = i + 1;
	}
	access_pattern_manual(ab,  out);
	for (auto i = 0; i < 512; ++i) {
		if (out[i] != (ab[0][i] + ab[1][i])) {
			return -1;
		}
	}
	return 0;
}

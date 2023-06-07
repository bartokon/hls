#include "control_data_driven_df.hpp"

int main(void) {
	int ab[2][512];
	int out[512];

	for (auto i = 0; i < 512; ++i) {
		ab[0][i] = i;
		ab[1][i] = i;
		out[i] = 1;
	}

	control_data_driven_df(ab, out);

	for (auto i = 0; i < 512; ++i) {
		if (out[i] % 2 != 0) {
			return -1;
		}
	}

	return 0;
}

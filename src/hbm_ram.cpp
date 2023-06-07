#include "hbm_ram.hpp"

static double calculate_sum(
	double d0,
	double d1,
	double d2,
	double d3,
	double d4,
	double d5
) {
	return d0 + d1 + d2 + d3 + d4 + d5;
}

#define SOLUTION_0
//#define SOLUTION_1
//#define SOLUTION_2

static double ram_access(
	unsigned int index,
	double data_hbm[512][4]
	) {

#ifdef SOLUTION_0
	double data_index[8];
	for (unsigned int j = index, k = 0; j < index + 2; ++j, ++k) {
		for (auto i = 0; i < 4; ++i) {
			data_index[k*4 + i] = data_hbm[j][i];
		}
	}
#endif

#ifdef SOLUTION_1
	//Why no bursts?
	double const data_index[8] = {
		data_hbm[index][0], data_hbm[index][1], data_hbm[index][2], data_hbm[index][3],
		data_hbm[index + 1][0], data_hbm[index + 1][1], data_hbm[index + 1][2], data_hbm[index + 1][3]
	};
#endif

#ifdef SOLUTION_2
	//Bursts like solution_0
	volatile double const data_index[8] = {
		data_hbm[index][0], data_hbm[index][1], data_hbm[index][2], data_hbm[index][3],
		data_hbm[index + 1][0], data_hbm[index + 1][1], data_hbm[index + 1][2], data_hbm[index + 1][3]
	};
#endif

	return calculate_sum(
		data_index[0], data_index[1], data_index[2],
		data_index[4], data_index[5], data_index[6]
	);

};

extern "C"
void hbm_ram(unsigned int indexes[512], double data_hbm[512][4], double out[512]) {
#pragma HLS INTERFACE mode=m_axi bundle=gmem0 port=indexes
#pragma HLS INTERFACE mode=m_axi bundle=gmem1 port=data_hbm
#pragma HLS INTERFACE mode=m_axi bundle=gmem2 port=out
	for (auto i = 0; i < 512; ++i) {
		out[i] = ram_access(indexes[i], data_hbm);
	}
}

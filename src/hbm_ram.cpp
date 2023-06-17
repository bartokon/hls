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

//#define SOLUTION_0
//#define SOLUTION_1
#define SOLUTION_2

static double ram_access(
	unsigned int index,
	double data_hbm[512][4]
	) {

#ifdef SOLUTION_0
	// burst length 2, burst size 256 bit
	double data[8];
	for (unsigned int j = index, k = 0; j < index + 2; ++j, ++k) {
		for (auto i = 0; i < 4; ++i) {
			data[k*4 + i] = data_hbm[j][i];
		}
	}
#endif

#ifdef SOLUTION_1
	// Why no bursts?
	// No burst, two single transactions of size 256 bit
	// HBM stall
	double const data[8] = {
		data_hbm[index][0], data_hbm[index][1], data_hbm[index][2], data_hbm[index][3],
		data_hbm[index + 1][0], data_hbm[index + 1][1], data_hbm[index + 1][2], data_hbm[index + 1][3]
	};
#endif

#ifdef SOLUTION_2
	//Bursts like solution_0
	double const volatile data[8] = {
		data_hbm[index][0], data_hbm[index][1], data_hbm[index][2], data_hbm[index][3],
		data_hbm[index + 1][0], data_hbm[index + 1][1], data_hbm[index + 1][2], data_hbm[index + 1][3]
	};
#endif

	return calculate_sum(
		data[0], data[1], data[2],
		data[4], data[5], data[6]
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

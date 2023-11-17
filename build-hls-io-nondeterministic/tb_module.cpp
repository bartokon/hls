#include <iostream>
#include "module.hpp"

int main(void) {
	static ap_int<32> in_arr[16384];
	hls::stream<ap_int<32>> str_in;
	unsigned int size = 8u;
	unsigned int size_out = 0;

	ap_uint<1> working = 0;
	for (int i = 0; i < size; ++i) {
		in_arr[i] = 0;
		str_in.write(i);
	}
	hls_module(in_arr, str_in, &working, size, &size_out);
	for (int i = 0; i < size; ++i) {
		if (in_arr[i] != i) {
			return -1;
		}
	}
	std::cout << "Size_out is: " << size_out << std::endl;
	if (size_out != size) {
		return -1;
	}
    return 0;
}

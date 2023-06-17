#include <stdio.h>
#include <fstream>
#include <vector>
#include <cmath>

#include "fft.hpp"

std::vector<float> read_file(std::string path) {
	std::ifstream infile(path);
	if (infile.is_open() == false) {
		std::string message = "Error reading file! " + path;
		throw std::invalid_argument(message);
	}
	std::vector<float> vector_out;
	float number;
	while (infile >> number) {
		vector_out.push_back(number);
	}
	return vector_out;
};

int main(void) {
	std::vector<float> data_samples_x = read_file("../../../../data_samples_x.txt");
	std::vector<float> data_samples_y = read_file("../../../../data_samples_y.txt");
	std::vector<float> fft_output_re = read_file("../../../../fft_output_re.txt");
	std::vector<float> fft_output_im = read_file("../../../../fft_output_im.txt");

	hls::stream<std::complex<data_in_t>> in;
	hls::stream<std::complex<data_out_t>> out;
	block_scaling_t block_exponent = 0;

	std::complex<data_in_t> arr_in[FFT_LENGTH];
	std::complex<data_out_t> arr_out[FFT_LENGTH];

	for (auto i = 0; i < FFT_LENGTH; ++i) {
		arr_in[i].real(data_samples_y.at(i));
		arr_in[i].imag(0);
		in.write(arr_in[i]);
	}
	fft(in, out, block_exponent);
	std::cout << "Block exponent: " << block_exponent << "\n";
	for (auto i = 0; i < FFT_LENGTH; ++i) {
		arr_out[i] = out.read();
		std::cout << "IP: " << arr_out[i].real() * (1 << block_exponent)
			<< " " << arr_out[i].imag() * (1 << block_exponent) << "i \n";
		std::cout << "GOLD: " << fft_output_re.at(i) << " " << fft_output_im.at(i) << "i \n";
	}

	return 0;
}

#ifndef FFT_
#define FFT_

#include <cmath>
#include <complex>

#include "hls_fft.h"
#include "ap_fixed.h"

//https://docs.xilinx.com/r/en-US/ug1399-vitis-hls/FFT-Static-Parameters
#define FFT_INPUT_WIDTH 32
#define FFT_OUTPUT_WIDTH 32
#define FFT_LENGTH 1024
#define FFT_BLOCK_SCALING_WIDTH 8
//typedef ap_fixed<FFT_INPUT_WIDTH, 1> data_in_t;
//typedef ap_fixed<FFT_OUTPUT_WIDTH, FFT_OUTPUT_WIDTH-FFT_INPUT_WIDTH+1> data_out_t;
//typedef float data_in_t;
//typedef float data_out_t;
typedef ap_fixed<FFT_INPUT_WIDTH, 1> data_in_t;
typedef ap_fixed<FFT_OUTPUT_WIDTH, 1> data_out_t;
typedef ap_uint<8> block_scaling_t;

//FFT static config
//https://support.xilinx.com/s/article/1160838?language=en_US
struct fft_static_config_0 : hls::ip_fft::params_t {
	static const unsigned input_width = FFT_INPUT_WIDTH;
	static const unsigned output_width = FFT_OUTPUT_WIDTH;
	static const unsigned status_width = 8;
	static const unsigned config_width = 16;
	static const unsigned max_nfft = 10;
    static const bool has_nfft = true;
    static const unsigned channels = 1;
    //static const unsigned arch_opt = hls::ip_fft::pipelined_streaming_io;
    static const unsigned phase_factor_width = 34;
    static const unsigned ordering_opt = hls::ip_fft::natural_order;
    static const bool ovflo = false;
    static const unsigned scaling_opt = hls::ip_fft::block_floating_point;
};

//FFT typedefs
typedef hls::ip_fft::config_t<fft_static_config_0> fft_runtime_config_0;
typedef hls::ip_fft::status_t<fft_static_config_0> fft_status_0;

//FFT runtime config
static fft_runtime_config_0 get_runtime_cfg_0 (void) {
	fft_runtime_config_0 config;
	config.setNfft(log2(FFT_LENGTH)); // Set FFT length to 1024 => log2(1024) => 10
	config.setDir(1, 0); //First channel forward fft
	return config;
}

extern "C"
void fft (
	hls::stream<std::complex<data_in_t>> &in,
	hls::stream<std::complex<data_out_t>> &out,
	block_scaling_t &block_exponent
);

#endif

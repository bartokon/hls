#include "fft.hpp"

void stream_to_array (
 hls::stream<std::complex<data_in_t>> &in,
 std::complex<data_in_t> out[FFT_LENGTH]
) {
   for (int i=0; i < FFT_LENGTH; i++) {
	   out[i] = in.read();
   }
}

void array_to_stream (
	std::complex<data_out_t> in[FFT_LENGTH],
	hls::stream<std::complex<data_out_t>> &out
) {
   for (int i=0; i < FFT_LENGTH; i++) {
       out.write(in[i]);
   }
}

void generate_response (
	std::complex<data_out_t> in[FFT_LENGTH],
	hls::stream<std::complex<data_out_t>> &out,
	fft_status_0 &fft_status,
	block_scaling_t &block_exponent_out
) {
	array_to_stream(in, out);
	block_exponent_out = fft_status.getBlkExp();
}

// TOP function
void fft (
	hls::stream<std::complex<data_in_t>> &in,
	hls::stream<std::complex<data_out_t>> &out,
	block_scaling_t &block_exponent
) {
#pragma HLS INTERFACE mode=ap_ctrl_hs port=return
#pragma HLS INTERFACE mode=axis register_mode=both port=in register
#pragma HLS INTERFACE mode=axis register_mode=both port=out register
#pragma HLS INTERFACE mode=ap_vld port=block_exponent
#pragma HLS dataflow

	std::complex<data_in_t> xn[FFT_LENGTH];
	std::complex<data_out_t> xk[FFT_LENGTH];

	fft_static_config_0 fft_config;
	fft_runtime_config_0 cfg = get_runtime_cfg_0();
	fft_status_0 fft_status;

	stream_to_array(in, xn);
	hls::fft<fft_static_config_0>(xn, xk, &fft_status, &cfg);
	generate_response(xk, out, fft_status, block_exponent);

}

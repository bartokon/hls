#include "module.hpp"

#ifdef SOLUTION_0

template <class C_>
static void set(C_ in, volatile C_ *out) {
#pragma HLS INLINE OFF
	*out = in;
};

static void fun(ap_int<32> output_data[16384], hls::stream<ap_int<32>> &input_stream, unsigned int size) {
#pragma HLS INLINE OFF
	for (unsigned int i = 0; i < size; ++i) {
		output_data[i] = input_stream.read();
	}
};

extern "C"
void hls_module(
    ap_int<32> output_data[16384],
    hls::stream<ap_int<32>> &input_stream,
	volatile ap_uint<1> *working,
    unsigned int size,
	volatile unsigned int *size_out
) {
#pragma HLS STABLE variable=size
#pragma HLS INTERFACE mode=s_axilite bundle=control port=output_data storage_impl=uram
#pragma HLS INTERFACE mode=axis register_mode=both port=input_stream register
#pragma HLS INTERFACE mode=s_axilite bundle=control port=size
#pragma HLS INTERFACE mode=s_axilite bundle=control port=return
#pragma HLS INTERFACE mode=ap_hs port=working
#pragma HLS INTERFACE mode=ap_ovld port=size_out
	set(size, size_out);
	set(ap_uint<1>(1), working);
	fun(output_data, input_stream, size);
	set(ap_uint<1>(0), working);
}
#endif

#ifdef SOLUTION_1

static void fun(ap_int<32> output_data[16384], hls::stream<ap_int<32>> &input_stream, unsigned int size) {
#pragma HLS INLINE OFF
	for (unsigned int i = 0; i < size; ++i) {
		output_data[i] = input_stream.read();
	}
};

extern "C"
void hls_module(
    ap_int<32> output_data[16384],
    hls::stream<ap_int<32>> &input_stream,
	volatile ap_uint<1> *working,
    unsigned int size,
	volatile unsigned int *size_out
) {
#pragma HLS STABLE variable=size
#pragma HLS INTERFACE mode=s_axilite bundle=control port=output_data storage_impl=uram
#pragma HLS INTERFACE mode=axis register_mode=both port=input_stream register
#pragma HLS INTERFACE mode=s_axilite bundle=control port=size
#pragma HLS INTERFACE mode=s_axilite bundle=control port=return
#pragma HLS INTERFACE mode=ap_hs port=working
#pragma HLS INTERFACE mode=ap_ovld port=size_out
    *size_out = size;
    *working = ap_uint<1>(1);
	fun(output_data, input_stream, size);
	*working = ap_uint<1>(0);
}
#endif

#ifdef SOLUTION_2

static ap_uint<1> fun(ap_int<32> output_data[16384], hls::stream<ap_int<32>> &input_stream, unsigned int size) {
#pragma HLS INLINE OFF
	for (unsigned int i = 0; i < size; ++i) {
		output_data[i] = input_stream.read();
	}
    return ap_uint<1>(0);
};

extern "C"
void hls_module(
    ap_int<32> output_data[16384],
    hls::stream<ap_int<32>> &input_stream,
	volatile ap_uint<1> *working,
    unsigned int size,
	volatile unsigned int *size_out
) {
#pragma HLS STABLE variable=size
#pragma HLS INTERFACE mode=s_axilite bundle=control port=output_data storage_impl=uram
#pragma HLS INTERFACE mode=axis register_mode=both port=input_stream register
#pragma HLS INTERFACE mode=s_axilite bundle=control port=size
#pragma HLS INTERFACE mode=s_axilite bundle=control port=return
#pragma HLS INTERFACE mode=ap_hs port=working
#pragma HLS INTERFACE mode=ap_ovld port=size_out
    *size_out = size;
    *working = ap_uint<1>(1);
	*working = fun(output_data, input_stream, size);
}
#endif
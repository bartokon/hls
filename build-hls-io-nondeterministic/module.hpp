#ifndef MODULE_HPP_
#define MODULE_HPP_

#if   1
    #define SOLUTION_0
#elif 1
    #define SOLUTION_1
#elif 1
    #define SOLUTION_2
#endif

#include <ap_fixed.h>
#include <ap_axi_sdata.h>
#include <hls_stream.h>

extern "C"
void hls_module(
    ap_int<32> output_data[16384],
    hls::stream<ap_int<32>> &input_stream,
	volatile ap_uint<1> *working,
    unsigned int size,
	volatile unsigned int *size_out
);

#endif
#include "add.hpp"

void add(uint32_t a, uint32_t b, uint32_t &c) {
    c = a + b;
};

void add_stream(hls::stream<uint32_t> &a, hls::stream<uint32_t> &b, hls::stream<uint32_t> &c) {
    c.write(a.read() + b.read());
};

void scalar_to_stream(uint32_t a, hls::stream<uint32_t> &a_stream) {
    a_stream.write(a);
};

void stream_to_scalar(hls::stream<uint32_t> &a_stream, uint32_t &a) {
    a = a_stream.read();
};

void wrap(uint32_t a, uint32_t b, uint32_t &c) {
#pragma HLS DATAFLOW
    hls::stream<uint32_t> c_s;
    hls::stream<uint32_t> a_s;
    hls::stream<uint32_t> b_s;
    scalar_to_stream(a, a_s);
    scalar_to_stream(b, b_s);
    add_stream(a_s, b_s, c_s);
    stream_to_scalar(c_s, c);
};

void top_module(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *c_stream) {
#pragma HLS INTERFACE mode=m_axi port=a depth=1024 bundle=first
#pragma HLS INTERFACE mode=m_axi port=b depth=1024 bundle=second
#pragma HLS INTERFACE mode=m_axi port=c depth=1024 bundle=first
#pragma HLS INTERFACE mode=m_axi port=c_stream depth=1024 bundle=second
#pragma HLS INTERFACE mode=s_axilite port=return

    main_loop_pipeline: for (uint32_t i = 0; i < 1024; ++i) {
        uint32_t c_o;
        uint32_t const a_t = a[i];
        uint32_t const b_t = b[i];
        add(a_t, b_t, c_o);
        c[i] = c_o;
    }
    
    main_loop_stream: for (uint32_t i = 0; i < 1024; ++i) {
        wrap(a[i], b[i], c_stream[i]);
    }

};


#ifndef ADD_HPP
#define ADD_HPP

#include <cstdint>
#include <hls_stream.h>

void add(uint32_t a, uint32_t b, uint32_t &c);
void add_stream(hls::stream<uint32_t> &a, hls::stream<uint32_t> &b, hls::stream<uint32_t> &c);
void scalar_to_stream(uint32_t a, hls::stream<uint32_t> &a_stream);
void stream_to_scalar(hls::stream<uint32_t> &a_stream, uint32_t &a);
void wrap(uint32_t a, uint32_t b, uint32_t &c);
void top_module(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *c_stream);

#endif
#include "access_pattern.hpp"

//AB:
//a0 a1 a2 a3 a4 a5 a6 a7 ... an
//b0 b1 b2 b3 b4 b5 b6 b7 ... bn
extern "C"
void access_pattern(double ab[2][512], double out[512]) {
#pragma HLS INTERFACE mode=m_axi bundle=gmem0 max_read_burst_length=64 port=ab
#pragma HLS INTERFACE mode=m_axi bundle=gmem0 max_write_burst_length=64 port=out
    //ab arlen = 0x00 -> HBM IS STALLING!
    //out awlen = 0x3F
    for (auto i = 0; i < 512; ++i) {
        out[i] = ab[0][i] + ab[1][i];
        //or add pragma to create something like line buffer for access??
        //Big shift register on bram??
    }
};

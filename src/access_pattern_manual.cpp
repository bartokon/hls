#include "access_pattern_manual.hpp"

//AB:
//a0 a1 a2 a3 a4 a5 a6 a7 ... an
//b0 b1 b2 b3 b4 b5 b6 b7 ... bn
static void load(double *ab, double out[32]) {
    for (auto j = 0; j < 32; ++j) {
        out[j] = ab[j];
    }
};

static void add(double a[32], double b[32], double out[32]) {
    for (auto j = 0; j < 32; ++j) {
        out[j] = a[j]+b[j];
    }
}

static void store(double ab[32], double *out) {
    for (auto j = 0; j < 32; ++j) {
        out[j] = ab[j];
    }
};

extern "C"
void access_pattern_manual(double ab[2][512], double out[512]) {
#pragma HLS INTERFACE mode=m_axi bundle=gmem0 max_read_burst_length=64 port=ab
#pragma HLS INTERFACE mode=m_axi bundle=gmem0 max_write_burst_length=64 port=out
    //ab arlen = 0x03 -> LESS STALL ON HBM - MINI BURSTS
    //out awlen = 0x3F
    for (auto i = 0; i < 16; ++i) {
        //If this is possible...
        //Read burst = 64, split into two 32 bursts for A and B data
        double a[32]; //These buffers should be in adapter memory
        double b[32]; //These buffers should be in adapter memory
        double c[32]; //These buffers should be in adapter memory
        //First read burst ab[0][0] ... ab[0][31]
        //Second read burst ab[1][0] ... ab[1][31]
        //... next iteration ...
        //Third read burst ab[0][31] .. ab[0][63]
        //Fourth read burst ab[0][31] .. ab[0][63]
        //reduce stall on HBM
        load(&ab[0][i*32], a); //First burst ab[0][0] .. ab[0][31] .. ab[0][63] ..
        load(&ab[1][i*32], b); //Second burst ab[1][0] .. ab[1][31] .. ab[1][63] ..
        add(a, b, c);
        store(c, &out[i*32]); //Write burst
    }
};
//Tripcount config threshold = 0; - tool shouldn't unroll loops. But dsp usage is x4 :)

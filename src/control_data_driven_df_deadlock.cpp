#include "control_data_driven_df_deadlock.hpp"

static void load_stream(
    int ab[2][512],
    hls::stream<int> &out) {
    for (auto i = 0; i < 2; ++i) {
        for (auto j = 0; j < 512; ++j) {
            out.write(ab[i][j]);
        }
    }
};

static void store_stream(
    hls::stream<int> &in,
    int out[512],
    unsigned int count
) {
    for (auto i = 0; i < count; ++i) {
        //This should not generate deadlock as previous functions are still running and count could increase.
        int temp = in.read();
        out[i] = temp; //This temp should be buffered for burst writes automatically! as most of the time the bottle neck is memory access...
    }
};

static void count_divisible_by_two(
    hls::stream<int> &in_stream,
    hls::stream<int> &out_stream,
    unsigned int &count
) {
    for (auto i = 0; i < 1024; ++i) {
        int temp = in_stream.read();
        if (temp % 2 == 0) {
            out_stream.write(temp);
            ++count;
        }
    }
};

extern "C"
void control_data_driven_df_deadlock(
    int ab[2][512],
    int out[512]
) {
#pragma HLS INTERFACE mode=m_axi bundle=gmem0 max_read_burst_length=64 port=ab
#pragma HLS INTERFACE mode=m_axi bundle=gmem0 max_write_burst_length=64 port=out
#pragma HLS DATAFLOW
    hls::stream<int> stream_local_0;
    hls::stream<int> stream_local_1;
    unsigned int count = 0;
    load_stream(ab, stream_local_0);
    count_divisible_by_two(stream_local_0, stream_local_1, count);
    store_stream(stream_local_1, out, count);
};

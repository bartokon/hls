#ifndef CONTROL_DATA_DRIVEN_DF_
#define CONTROL_DATA_DRIVEN_DF_

#include <hls_stream.h>

extern "C"
void control_data_driven_df(int ab[2][512], int out[512]);

#endif

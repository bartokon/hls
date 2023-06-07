#!/bin/bash
set -e
echo "# $0"
export LIBRARY_PATH=/usr/lib/x86_64-linux-gnu
source /tools/Xilinx/Vitis/2023.1/settings64.sh
source /opt/xilinx/xrt/setup.sh >/dev/null
VITIS_PLATFORM=xilinx_u50_gen3x16_xdma_5_202210_1
cat <<cut >hls.tcl
open_project -reset proj_hls
open_solution -reset solution -flow_target vitis

set script_path [file dirname [ file normalize [ info script ] ] ]

# Define technology and clock rate
set_part  {xcu50-fsvh2104-2-e}
# peroid = 1/f * ns/s [ns]
create_clock -period [expr {1.0 / 300000000.0 * 1000000000}]

#config_compile -pipeline_style frp
config_interface -m_axi_addr64
config_compile -name_max_length 256
config_interface -m_axi_max_widen_bitwidth 512
config_interface -m_axi_alignment_byte_size 64
config_interface -m_axi_auto_max_ports

set CFLAGS "-DDEBUG"

add_files -tb ../src/tb_access_pattern.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb ../src/access_pattern.hpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"

add_files ../src/access_pattern.cpp
add_files ../src/access_pattern.hpp

set_top access_pattern

#csim_design
csynth_design
cosim_design -enable_dataflow_profiling -trace_level port
#cosim_design -O -wave_debug -enable_dataflow_profiling -trace_level port

cut

#https://docs.xilinx.com/r/2022.1-English/ug1399-vitis-hls/Vitis-HLS-Command-Reference
vitis_hls hls.tcl -nosplash=true
grep "INFO:" vitis_hls.log > info.txt
grep "WARNING:" vitis_hls.log > warnings.txt
grep "ERROR:" vitis_hls.log > errors.txt

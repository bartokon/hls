open_project -reset proj_hls
open_solution -reset solution -flow_target vivado

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

add_files -tb ../src/tb_fft.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb ../src/fft.hpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"

add_files ../src/fft.cpp
add_files ../src/fft.hpp

set_top fft

#csim_design
csynth_design
cosim_design -enable_dataflow_profiling -trace_level port
#cosim_design -O -wave_debug -enable_dataflow_profiling -trace_level port


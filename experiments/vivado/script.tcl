############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2013 Xilinx Inc. All rights reserved.
##config_bind -effort high
##config_schedule -effort high
############################################################
#set projectName  $::env(projectName)
#set clock       $::env(projectClock)

set topFunction hardware_top 
set sourceFile  gaussian_debug.cpp 
set testFile    main.cc 
set clock       10.0 

open_project anydsl_fpga 
set_top   $topFunction
add_files $sourceFile
add_files -tb $testFile
open_solution "solution1"
set_part {xc7z100ffg900-2}
create_clock -period ${clock} -name default
csim_design -ldflags {-lrt} -clean
csynth_design
cosim_design -ldflags {-lrt} -trace_level none
export_design -format ip_catalog -evaluate verilog
exit

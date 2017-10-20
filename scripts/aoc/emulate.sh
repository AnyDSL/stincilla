source ~/init_opencl.sh
app=gaussian_debug
#
echo "compile host code and generate .cl file!"
make ${app}
#
echo "compile kernel code!"
aoc --report -march=emulator "${app}.cl" -o "${app}_fpga.aocx"
mv "./${app}_fpga.aocx" "./${app}.aocx"
#
echo "run emulation!"
CL_CONTEXT_EMULATOR_DEVICE_ALTERA=1 ./${app}

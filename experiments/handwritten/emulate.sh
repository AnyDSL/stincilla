aoc --report -march=emulator gaussian_debug.cl -o comp/gaussian_debug.aocx
cd comp
ln -s ../gaussian_debug ./host
CL_CONTEXT_EMULATOR_DEVICE_ALTERA=1 ./host

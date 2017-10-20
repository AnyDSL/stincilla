app=gaussian_debug

echo "compile kernel code!"
aoc --report "${app}.cl" -o "${app}_fpga.aocx"

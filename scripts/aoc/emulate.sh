#!/bin/bash

if [ -z "$1" ]
then
    echo "Error!: No option (application name) were passed."
   exit
fi

APP="$1"
dir="anydsl_aocl_emu"
if [[ ! -e $dir ]]; then
    mkdir $dir
else
    echo "Emulating device code in $dir"
fi
aoc -report -march=emulator $APP.cl -o $dir/$APP.aocx
ln -sf $dir/$APP.aocx ./$APP.aocx
CL_CONTEXT_EMULATOR_DEVICE_INTELFPGA=1 ./$APP

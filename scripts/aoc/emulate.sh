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
aoc -report -march=emulator -v $APP.cl -o $dir/$APP.aocx
ln -sf $dir/$APP.aocx ./$APP.aocx

if [ "$SELECTED_VERSION" == "19.*" ]
then
    CL_CONFIG_CPU_EMULATE_DEVICES=1 ./$APP
else
    CL_CONTEXT_EMULATOR_DEVICE_INTELFPGA=1 ./$APP
fi

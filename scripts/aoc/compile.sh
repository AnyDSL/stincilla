#!/bin/bash

if [ -z "$1" ]
 then
     echo "Error!: No option (application name) were passed."
    exit
 fi

APP="$1"
dir="anydsl_aocl"
if [[ ! -e $dir ]]; then
    mkdir $dir
else
    echo "synthesizing kernel code in $dir"
fi

if [[ ! -e $dir/$APP.aocx ]]; then
aoc -report $APP.cl -o $dir/$APP.aocx
fi

ln -sf $dir/$APP.aocx ./$APP.aocx
./$APP

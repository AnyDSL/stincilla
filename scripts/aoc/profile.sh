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
    echo "Profling in $dir"
fi

if [[ -e $dir/$APP.aocx ]]; then
    ln -sf $dir/$APP.aocx ./$APP.aocx
    export ACL_PROFILE_TIMER=1
    export ANYDSL_PROFILE="full fpga_dynamic"
    ./$APP
    aocl report $APP.aocx profile.mon $dir/$APP.source
fi

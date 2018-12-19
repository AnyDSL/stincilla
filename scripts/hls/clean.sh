#!/bin/bash
# Removing all hls-related files

if ls *hls* >/dev/null 2>&1; then

    find . -type f -executable -exec sh -c "file -i '{}' | grep -q 'x-executable; charset=binary'" \; -print | xargs rm -f
    rm -r *_tb.cpp *hls* *.ll *.orig *.tcl *.o  anydsl_fpga/

fi

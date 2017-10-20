#!/bin/bash

if [ -f "$1" ]; then
  if [ $2 ]; then
    echo "ALUTs   Registers    LU    BRAM   DSP   Freq"
    cat $1 | egrep "ALUTs|Registers|Logic|M10K|RAM|DSP|freq" | sed 's/,//g' | xargs | awk '{ print $2" "$4" "$7*100/$9" "$21" "$16" "$27}'
  else
    echo "Logic   BRAM   DSP   Freq"
    cat $1 | egrep "Logic|M10K|RAM|DSP|freq" | sed 's/,//g' | xargs | awk '{ print $3*100/$5" "$17*100/$19" "$12*100/$14" "$23}'
  fi
else
  II=$(cat $1/gaussian_debug.log | grep cycles | awk '{ print $6 }' | sort | tail -n1)
  if [ "$II" == "" ]; then II=1; fi
  if [ $2 ]; then
      echo "II   ALUTs   Registers    LU(%)    BRAM   DSP   Freq"
    #RES=$(cat $1/acl_quartus_report.txt | egrep "ALUTs|Registers|Logic|RAM blocks|RAM|DSP|freq" | sed 's/,//g' | xargs | awk  '{ print $2" "$4" "$7*100/$9" "$25" "$16" "$35}')
     RES=$(cat $1/acl_quartus_report.txt | egrep "ALUTs|Registers|Logic|RAM blocks|RAM|DSP|freq" | sed 's/,//g' | xargs | awk  '{ print $2" "$4" "$7"        "$25" "$16" "$35}')
    #RES=$(cat $1/acl_quartus_report.txt | egrep "ALUTs|Registers|Logic|RAM blocks|RAM|DSP|freq" | sed 's/,//g' | xargs | awk -v chr=' & ' '{ print $2 chr $4 chr $7*100/$9 chr $25 chr $16 chr $35}')
  else
      echo "II  Logic(%)   BRAM(%)   DSP(%)   Freq"
    RES=$(cat $1/acl_quartus_report.txt | egrep "Logic|RAM blocks|RAM|DSP|freq" | sed 's/,//g' | xargs | awk '{ print $3*100/$5" "$21*100/$23" "$12*100/$14" "$31}')
  fi
  echo $II $RES
fi


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
ACL_PROFILE_TIMER=1
./$APP
aocl report $APP.aocx profile.mon $dir/$APP.source
fi



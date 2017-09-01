## Akif

## Check if board is set
[ -z "$SELECTED_BOARD" ] && SELECTED_BOARD="abc"
if env | grep -q ^SELECTED_BOARD=
then
  #echo SELECTED_BOARD is already exported as ${SELECTED_BOARD}
  : 
else
  export SELECTED_BOARD=c5gt
  #echo ${SELECTED_BOARD} is selected
fi


## Get the path of the script
SCRIPTPATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
#echo $SCRIPTPATH


### Set aocl env variables (This is enough if you have absolute paths)
#export ALTERAROOT=~/opt/altera/17.0
export ALTERAROOT=$SCRIPTPATH
export ALTERAOCLSDKROOT=$ALTERAROOT/hld

#export AOCL_BOARD_PACKAGE_ROOT=${ALTERAOCLSDKROOT}/board/c5gt
export AOCL_BOARD_PACKAGE_ROOT=${ALTERAOCLSDKROOT}/board/${SELECTED_BOARD}

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${ALTERAOCLSDKROOT}/host/linux64/lib:${AOCL_BOARD_PACKAGE_ROOT}/linux64/lib
export QUARTUS_ROOTDIR=$ALTERAROOT/quartus
export PATH=$PATH:${QUARTUS_ROOTDIR}/bin:${ALTERAOCLSDKROOT}/linux64/bin:${ALTERAOCLSDKROOT}/bin:${ALTERAOCLSDKROOT}/host/linux64/bin

export QUARTUS_64BIT=1
export LM_LICENSE_FILE=27000@134.96.220.21

# For quartus and nios binaries (not really necessary for AOCL)
export PATH=$PATH:QUARTUS_ROOTDIR/bin
export PATH=$PATH:${ALTERAROOT}/nios2eds/bin

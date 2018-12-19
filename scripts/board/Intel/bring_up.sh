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
#export INTELFPGAROOT=/opt/intelFPGA/18.1
export INTELFPGAROOT=${SCRIPTPATH}
export INTELFPGAOCLSDKROOT=${INTELFPGAROOT}/hld
## Don't remove variables starting with ALTERA
## Platform Designer scripts (formly Qsys, still uses ALTERA variables)
export ALTERAOCLSDKROOT=${INTELFPGAROOT}/hld
export AOCL_BOARD_PACKAGE_ROOT=${INTELFPGAOCLSDKROOT}/board/${SELECTED_BOARD}

export LD_LIBRARY_PATH=${INTELFPGAOCLSDKROOT}/host/linux64/lib:${AOCL_BOARD_PACKAGE_ROOT}/linux64/lib:$LD_LIBRARY_PATH
export QUARTUS_ROOTDIR=${INTELFPGAROOT}/quartus
export QSYS_ROOTDIR=${QUARTUS_ROOTDIR}/sopc_builder/bin
export PATH=${QUARTUS_ROOTDIR}/bin:${INTELFPGAOCLSDKROOT}/linux64/bin:${INTELFPGAOCLSDKROOT}/bin:${INTELFPGAOCLSDKROOT}/host/linux64/bin:$PATH

export QUARTUS_64BIT=1
export LM_LICENSE_FILE=27000@134.96.220.21

# For quartus and nios binaries (not really necessary for AOCL)
export PATH=${QUARTUS_ROOTDIR}/bin:$PATH
export PATH=${INTELFPGAROOT}/nios2eds/bin:$PATH

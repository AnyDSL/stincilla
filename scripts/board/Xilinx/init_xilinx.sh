mode=$1
#export SELECTED_BOARD=zcu
export SELECTED_VERSION=2018.2
path="/opt/Xilinx"
source $path/Vivado/${SELECTED_VERSION}/settings64.sh
if [ "$1" = "soc" ];
then
    echo "SDSoC got initialized"
    source $path/SDx/${SELECTED_VERSION}/settings64.sh
fi

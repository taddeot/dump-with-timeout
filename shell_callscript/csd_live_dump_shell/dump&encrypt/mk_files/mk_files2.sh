#!/bin/sh
mk_files2()
{
    local __FILE_PATH=$1
    mkdir -p ${__FILE_PATH}conf/CSD/
    #sleep 100
    echo "Host related events">>${__FILE_PATH}conf/CSD/host_ecent.host
    echo "Inventory change history">>${__FILE_PATH}conf/CSD/inventory_change.ring
    echo "IPMIMain related error logs">>${__FILE_PATH}conf/CSD/ipmi_error.ring
    echo "Redfish related error logs">>${__FILE_PATH}conf/CSD/redfish_error.ring
    echo "FW flash history">>${__FILE_PATH}conf/CSD/flash_history.ring
}
   
mk_files2 $*

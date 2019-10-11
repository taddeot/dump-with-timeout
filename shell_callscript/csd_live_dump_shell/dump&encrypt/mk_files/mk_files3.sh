#!/bin/sh
mk_files3()
{
    local __FILE_PATH=$1
    mkdir -p ${__FILE_PATH}tmp/CSD/
    
    while [ 1 ]
    do 
        sleep 100
        echo "aaa"
    done
    echo "Host related events">>${__FILE_PATH}tmp/CSD/ipmi_warning.ring
    echo "Inventory change history">>${__FILE_PATH}tmp/CSD/redfish_warning.ring
    echo "IPMIMain related error logs">>${__FILE_PATH}tmp/CSD/ipmi_debug.ring
    echo "Redfish related error logs">>${__FILE_PATH}tmp/CSD/redfish_debug.ring
    echo "FW flash history">>${__FILE_PATH}tmp/CSD/bios_setup.bios
}
   
mk_files3 $*

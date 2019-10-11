#!/bin/sh
mk_files4()
{
    local __FILE_PATH=$1
    mkdir -p ${__FILE_PATH}tmp/CSD/
    mkdir -p ${__FILE_PATH}tmp/CSD_LIVE/
    echo "Host related events">>${__FILE_PATH}tmp/CSD/bios_port80.port80
    echo "Inventory change history">>${__FILE_PATH}tmp/CSD/ses_debug_db.ses
    echo "IPMIMain related error logs">>${__FILE_PATH}tmp/CSD_LIVE/hw_test.log
    echo "Redfish related error logs">>${__FILE_PATH}tmp/CSD_LIVE/ipmi_dump.log
    echo "FW flash history">>${__FILE_PATH}tmp/CSD_LIVE/redfish_dump.log
}
   
mk_files4 $*

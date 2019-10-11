#!/bin/sh
mk_files5()
{
    local __FILE_PATH=$1
    mkdir -p ${__FILE_PATH}tmp/CSD_LIVE/
while [ 1 ]
    do 
        sleep 100
        echo "aaa"
    done
    echo "Host related events">>${__FILE_PATH}tmp/CSD_LIVE/bmc_health.log
    echo "Inventory change history">>${__FILE_PATH}tmp/CSD_LIVE/ses_health.log
    echo "IPMIMain related error logs">>${__FILE_PATH}tmp/CSD_LIVE/networking.log
    echo "Redfish related error logs">>${__FILE_PATH}tmp/CSD_LIVE/env.log
    
}
   
mk_files5 $*

#!/bin/sh
mk_files1()
{
    local __FILE_PATH=$1
    mkdir -p ${__FILE_PATH}conf/CSD/

    while [ 1 ]
    do 
        sleep 100
        echo "aaa"
    done

    echo "The lastest 3 times bmc booting log with timestamp 001">>${__FILE_PATH}conf/CSD/bmc_boot_now.log
    echo "The lastest 3 times bmc booting log with timestamp 002">>${__FILE_PATH}conf/CSD/bmc_boot_prev.log
    echo "The lastest 3 times bmc booting log with timestamp 003">>${__FILE_PATH}conf/CSD/bmc_boot_old.log
    echo "Memory leak log BMC reset reason log">>${__FILE_PATH}conf/CSD/bmc_health.log
}
   
mk_files1 $*

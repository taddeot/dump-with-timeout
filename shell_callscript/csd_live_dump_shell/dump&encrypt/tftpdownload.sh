#!/bin/sh
#This script is used tftp transport to host
#
__TARGET_FILE_NAME=/tmp/CSD_PACK/csd_encd_file.tar.gz
source /tmp/CSD/ipaddr.dat
tftp -p -l ${__TARGET_FILE_NAME} -r ${__TARGET_FILE_NAME} ${__HOST_IPADDR}


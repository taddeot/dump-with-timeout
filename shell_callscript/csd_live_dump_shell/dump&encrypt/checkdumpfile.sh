#!/bin/bash
__TARGET_FILE_NAME="/tmp/CSD_PACK/csd_Originalfile.tar.gz"
__CHK_FILE_PATH="/tmp/CSD/"
__CHK_FILE_RST_NAME="${__CHK_FILE_PATH}dumpfileresult.dat"
mkdir -p ${__CHK_FILE_PATH}
if [ ! -f "$__TARGET_FILE_NAME" ]; then 
	echo "$__TARGET_FILE_NAME doesn't exist!"
	echo 0 > $__CHK_FILE_RST_NAME
	return 0
else
	echo 1 > $__CHK_FILE_RST_NAME
	return 0 
fi 

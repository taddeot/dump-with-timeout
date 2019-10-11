#!/bin/sh

__FILES_PATH=
__OPEN_SSL_PATH=
__CSD_PACK_PATH="${__FILES_PATH}tmp/CSD_PACK/"
prikey="${__FILES_PATH}rsa_prikey.pem"
__AES_KEY="${__CSD_PACK_PATH}csd_key.log"
#__PRINT_LOG="${__FILES_PATH}dump.log"
#touch ${__PRINT_LOG}

main(){

    #get package name
    if [ "$1" = "" ]
    then
        echo "Please input Package name ,for example:"
        echo "./dec_package.sh csd_athena_123.tar.gz"
        return 1
    fi
    package_name=$1
    if [ ! -f $package_name ]
    then 
        echo "File does not exist!"
        echo "Please input the correct file name"
        return 1
    fi
    print_log "+++++++++ Start ++++++++"
    echo
    #decompress
    tar -xzvf $package_name >/dev/null 2>&1
    [ $? -eq 0 ] || {
		print_log "decompress fail !!!"
		return 1
	}
    #get aes key
    csd_rsa_dec
    [ $? -eq 0 ] || {
		print_log "get aes key fail !!!"
		return 1
	}
    #get original data package
    #csd_aes_dec $package_name
    csd_aes_dec
    [ $? -eq 0 ] || {
		print_log "===================== Fail !!! ====================="
		return 1
	}

    sleep 1
    print_log "===================== END ====================="
    sync
    sleep 5

    return 0
}

csd_rsa_dec(){
    cmd=
    cmd_report=

    outfile="${__CSD_PACK_PATH}csd_aeskey.log"
    cmd="${__OPEN_SSL_PATH}openssl rsautl -decrypt -in $__AES_KEY -inkey $prikey  -out $outfile"
    cmd_report=`eval ${cmd} 2>&1`
    [ $? -eq 0 ] || {
        print_log  "$[$FUNCNAME] ${cmd} FAIL!!!"
		print_log  "RESULT: ${cmd_report}"
		return 1
    }
    rm -f $__AES_KEY


}

csd_aes_dec(){
    #outfile="${__CSD_PACK_PATH}$1"
    
    cmd=
    cmd_report=

    cmd="cat ${__CSD_PACK_PATH}csd_aeskey.log"
    aeskey=`${cmd}`
    infile="${__CSD_PACK_PATH}csd_enc.tar.gz"
    outfile="${__CSD_PACK_PATH}csd_dec_final.tar.gz"
    cmd="${__OPEN_SSL_PATH}openssl enc -d -aes-128-cbc -k $aeskey -in $infile -out $outfile"
    cmd_report=`eval ${cmd} 2>&1`
    [ $? -eq 0 ] || {
        print_log  "$[$FUNCNAME] ${cmd} FAIL!!!"
		print_log  "RESULT: ${cmd_report}"
		return 1
    }

    rm -f $infile
    rm -f ${__CSD_PACK_PATH}csd_aeskey.log

    #Calculate the MD5 value of the compressed package after decryption
    cmd="md5sum ${outfile} |cut -d ' ' -f 1"
    md5_num=`eval ${cmd}`
    cmd="cat ${__CSD_PACK_PATH}md5.log"
    md5_num_2=`${cmd}`
    
    if [ "$md5_num" != "$md5_num_2" ]
    then
        print_log "===================== ERROR! ======================="|tee -a ${__CSD_PACK_PATH}md5.log
        print_log "Warning:The MD5 value is different !"|tee -a ${__CSD_PACK_PATH}md5.log
        print_log "Please check whether the package has been changed !!!"|tee -a ${__CSD_PACK_PATH}md5.log 
        return 1
    else
        print_log "MD5 value is the same, decryption is complete."
    fi
    rm -f ${__CSD_PACK_PATH}md5.log
    
    return 0
}

print_log(){ 
	#echo -e "[`date +"%F_%H-%M-%S"`] $*" | tee -a ${__PRINT_LOG}
	# echo -e "$*" >> ${__PRINT_LOG}
	#sync
    echo  "[`date +"%F_%H-%M-%S"`] $*"
	return $?
}
##############
main $*
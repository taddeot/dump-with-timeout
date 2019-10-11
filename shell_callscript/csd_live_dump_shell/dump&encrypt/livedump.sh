#!/bin/sh
#BMC busy box use sh
#Will print extra information(kill) when use "/bin/bash"
#Mar 20,2019 Taddeo Tao 
#function key word remove
#
##path ofshell packages
#__SH_PATH="/conf/BMC2/"
__SH_PATH=
#target path of generated files
#__FILES_PATH="/"
__FILES_PATH=

#define OPEN SSL PATH
#__OPEN_SSL_PATH="/usr/local/bin/"
__OPEN_SSL_PATH=

#define __TOTAL_CASENUM for calculate percentage
__TOTAL_CASENUM=5

#define __DUMP_PERCENT_FILE 
__DUMP_PERCENT_PATH="/tmp/CSD/"
__DUMP_PERCENT_FILE="${__DUMP_PERCENT_PATH}dump_percent.dat"
__AES_KEY="${__FILES_PATH}csd_aeskey.log"

mkdir -p ${__DUMP_PERCENT_PATH}
pubkey="${__FILES_PATH}rsa_pubkey.pem"
#log file
#__PRINT_LOG="${__FILES_PATH}dump.log"
#touch ${__PRINT_LOG}

cmd="date +%Y_%m_%d-%H_%M_%S"
__date_time=`eval ${cmd} 2>&1`
#mkdir ${__SH_PATH}csd_call_shell$__date_time
#cd ${__SH_PATH}csd_call_shell$__date_time

live_dump()
{
    local cmd=
    local program_name=$1
    
    #cp ../$program_name ./


    #live dump 

    {
        #trap 'echo "${program_name} end."; return 1' SIGHUP
        sleep 2
        cmd="sh ${__SH_PATH}$program_name ${__FILES_PATH}"
        cmd_report=`eval ${cmd} 2>&1`
        return_fol=$?
       # echo "$return_fol:mkfolderfanhuizhi"
        [ $return_fol -eq 0 ] || {
          echo "error return of mkfol is $return_fol"
          echo " $[$FUNCNAME]_${cmd} FAIL!!..RESULT:${cmd_report}"
          
          return 1;
        }
        return 0
        
       
    } & 
    child1=$!
    #echo "child1 id is:${child1}"
    {
        #trap 'echo "${program_name} done."; return 0' SIGHUP
        #60s for time out protect
        #for var1 in {1..6}
        #do
        #wait to program run
        sleep 30
        echo "please waiting..."
        sleep 20
        echo "please waiting..."
        sleep 10
        
        #done
        print_log "Live dump :${program_name} timeout, stop program thread!!!"
        #check whether live dump is completed
        cmd="ps -ef|grep -w $program_name|grep -v grep|awk '{print\$2}'"
        child_loopp=`eval ${cmd}`
        if [ $? -eq 0 ]
        then
          kill  ${child_loopp}  >/dev/null 2>&1
          print_log "kill ${program_name}"
          #timeout
        else
          echo  "COMMAND:${cmd} FAIL."
          print_log "$program_name does not exist." 
          echo "RESULT: ${cmd} ${child_loopp}"
        fi 
        #kill -s SIGHUP $child1 >/dev/null 2>&1
        kill  $child1 >/dev/null 2>&1
        #sleep 2
        #return 1

    }& 
    child2=$!
    #echo "child2 id is:${child2}"
    wait $child1 
    wait_re=$?
    [ $wait_re -eq 0 ]||{
        #echo "error return of wait  is:$wait_re"
        print_log "time out"
        #kill -s SIGHUP $child2  >/dev/null 2>&1
        kill $child2 >/dev/null 2>&1
        sleep 2 
       
        return 1
    }
    #kill -s SIGHUP $child2  >/dev/null 2>&1
    kill $child2
    
    #sleep 2
    print_log "$program_name is OK."   
    return 0
}
############main+++++++++++++++++
main() 
{
    print_log "++++++++++++++start+++++++++++++++"
    #percentage for collection status
    print_log "0 ${__TOTAL_CASENUM}" > "${__DUMP_PERCENT_FILE}"

    sleep 2
    print_log "mk1"
    live_dump mk_files/mk_files1.sh
    if [ $? -eq 0 ]
    then
      status1="success"
    else
      
        print_log "mk_files1 timeout,please check ,fix then retry"
        status1="fail"
        sleep 10
        #return 1
    fi
    #percentage for collection status
    print_log "1 ${__TOTAL_CASENUM}" > "${__DUMP_PERCENT_FILE}"
    sleep 5
    print_log "mk2"

    live_dump mk_files/mk_files2.sh
    if [ $? -eq 0 ]
    then
      status2="success"
    else
      
        print_log "mk_files2 timeout,please check ,fix then retry"
        status2="fail"
        sleep 10
        #return 1
    fi
    #percentage for collection status
    print_log "2 ${__TOTAL_CASENUM}" > "${__DUMP_PERCENT_FILE}"
    sleep 5
    print_log "mk3"

    live_dump mk_files/mk_files3.sh
    if [ $? -eq 0 ]
    then
      status3="success"
    else
      
        print_log "mk_files3 timeout,please check ,fix then retry"
        status3="fail"
        sleep 10
        #return 1
    fi
    #percentage for collection status
    print_log "3 ${__TOTAL_CASENUM}" > "${__DUMP_PERCENT_FILE}"
    sleep 5
    print_log "mk4"

    live_dump mk_files/mk_files4.sh
    if [ $? -eq 0 ]
    then
      status4="success"
    else
      
        print_log "mk_files4 timeout,please check ,fix then retry"
        status4="fail"
        sleep 10
        #return 1
    fi
    #percentage for collection status
    print_log "4 ${__TOTAL_CASENUM}" > "${__DUMP_PERCENT_FILE}"
    sleep 5
    print_log "mk5"

    live_dump mk_files/mk_files5.sh
    if [ $? -eq 0 ]
    then
      status5="success"
    else
      
        print_log "mk_files5 timeout,please check ,fix then retry"
        status5="fail"
        sleep 10
        #return 1
    fi
    #percentage for collection status
    print_log "5 ${__TOTAL_CASENUM}" > "${__DUMP_PERCENT_FILE}"

    sleep 10
    #print the result :fail or success
    print_result
    
    #compress  
    if [  -d "${__FILES_PATH}tmp/CSD_PACK/" ];
    then
      rm -rf ${__FILES_PATH}tmp/CSD_PACK/
    fi
    mkdir -p  ${__FILES_PATH}tmp/CSD_PACK/
    foldersname="${__FILES_PATH}conf/  ${__FILES_PATH}tmp/CSD/ ${__FILES_PATH}tmp/CSD_LIVE/"
    tar -cvzf  ${__FILES_PATH}tmp/CSD_PACK/csd_Originalfile.tar.gz $foldersname >/dev/null 2>&1
    [ $? -eq 0 ] || {
      print_log "Compress Fail !!!"
      return 1
    }

    #calculate the md5 value of the compressed package
    cmd="md5sum ${__FILES_PATH}tmp/CSD_PACK/csd_Originalfile.tar.gz |cut -d ' ' -f 1 >${__FILES_PATH}tmp/CSD_PACK/md5.log"
    cmd_report=`eval ${cmd} 2>&1`
    [ $? -eq 0 ] || {
        print_log  "$[$FUNCNAME] ${cmd} FAIL!!!"
		print_log  "RESULT: ${cmd_report}"
		return 1
    }
    #md5_num=`${cmd}`
    #echo $md5_num >md5.log
    #tar -cvzf  ${__FILES_PATH}tmp/CSD_PACK/csd_Originalfile$__date_time.tar.gz $foldersname >/dev/null 2>&1
    #encrypt the compress package
    #${__OPEN_SSL_PATH}openssl  smime  -encrypt -aes256  -in  ${__FILES_PATH}tmp/CSD_PACK/csd_Originalfile$__date_time.tar.gz  -binary  -outform DEM  -out  ${__FILES_PATH}tmp/CSD_PACK/csd_encrypted_$__date_time.tar.gz  publickey.pem
    #${__OPEN_SSL_PATH}openssl  smime  -encrypt -aes256  -in  ${__FILES_PATH}tmp/CSD_PACK/csd_Originalfile.tar.gz  -binary  -outform DEM  -out  ${__FILES_PATH}tmp/CSD_PACK/csd_encrypted.tar.gz  publickey.pem
    
    #Encrypt the compressed package (AES)
    csd_aes_enc
    [ $? -eq 0 ] || {
      print_log "Fail to encrypt the compressed package !"
      return 1
    }
    sleep 1
    csd_rsa_enc
    [ $? -eq 0 ] || {
      print_log "Fail to encrypt the aeskey !"
      return 1
    }
    sleep 1
    csd_data_pack
    [ $? -eq 0 ] || {
      print_log "Fail to  compressed package !"
      return 1
    }
    sleep 5
    print_log "end"
    sync
    sleep 5
    return 0 
}

csd_aes_enc(){
    cmd=

    cmd="${__OPEN_SSL_PATH}openssl rand -base64 128"
    aeskey=`${cmd}`
    cmd="echo ${aeskey} | sed s/[[:space:]]//g"
    aeskey=`eval ${cmd}`

    #echo ${aeskey} |cut -c 1-10
    #aeskey=${aeskey// /-}
    #cmd="echo ${aeskey:0:128} | sed s/[[:space:]]//g"
    #aeskey=`eval ${cmd}`
    #aeskey=${aeskey// /-}
    ###generate aes key
    #aeskey=`echo ${aeskey:0:128}`
    #aeskey=${aeskey// /-}
    echo $aeskey > $__AES_KEY
    infile="${__FILES_PATH}tmp/CSD_PACK/csd_Originalfile.tar.gz"
    outfile="${__FILES_PATH}tmp/CSD_PACK/csd_enc.tar.gz"
    cmd="${__OPEN_SSL_PATH}openssl enc -e -aes-128-cbc -k $aeskey -in $infile -out $outfile"
    cmd_report=`eval ${cmd} 2>&1`
    [ $? -eq 0 ] || {
        print_log  "$[$FUNCNAME] ${cmd} FAIL!!!"
		print_log  "RESULT: ${cmd_report}"
		return 1
    }
    
    #rm -f $infile
    #[ $? -eq 0 ] || {
        #print_log  "Remove Originalfile.tar.gz FAIL!!!"
		#return 1
    #}

    return 0
}
csd_rsa_enc(){
    
    cmd=
    cmd_report=

    outfile="${__FILES_PATH}tmp/CSD_PACK/csd_key.log"
    cmd="${__OPEN_SSL_PATH}openssl rsautl -encrypt -in $__AES_KEY -inkey $pubkey -pubin -out $outfile"
    cmd_report=`eval ${cmd} 2>&1`
    [ $? -eq 0 ] || {
        print_log  "$[$FUNCNAME] ${cmd} FAIL!!!"
		print_log  "RESULT: ${cmd_report}"
		return 1
    }
    rm -f $__AES_KEY
    [ $? -eq 0 ] || {
        print_log "Warning: can't remove aeskey file !!"
        return 1
    }
    return 0

}

csd_data_pack(){
    if [ -f $__AES_KEY ]
    then
        rm -f $__AES_KEY
        if [ -f $__AES_KEY ]
        then
            print_log "Warning:aeskey still exists!!!"
            return 1
        fi
    fi
    filesname="${__FILES_PATH}tmp/CSD_PACK/csd_key.log ${__FILES_PATH}tmp/CSD_PACK/md5.log ${__FILES_PATH}tmp/CSD_PACK/csd_enc.tar.gz"
    tar -cvzf  ${__FILES_PATH}tmp/CSD_PACK/csd_encd_file.tar.gz $filesname >/dev/null 2>&1
    rm -f $filesname
    [ $? -eq 0 ] || {
        print_log "Warning: can't remove Original file !!"
        return 1
    }

    return 0


}

print_result()
{
    echo "==========================================================="
    print_log "Result:"
    echo "livedump1:$status1"
    echo "livedump2:$status2"
    echo "livedump3:$status3"
    echo "livedump4:$status4"
    echo "livedump5:$status5"
   
}

print_log(){ 
	#echo -e "[`date +"%F_%H-%M-%S"`] $*" | tee -a ${__PRINT_LOG}
	# echo -e "$*" >> ${__PRINT_LOG}
	#sync
    echo  "[`date +"%F_%H-%M-%S"`] $*"
	return $?
}

###############################################
main
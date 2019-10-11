/*******************************************************************************
 ** (C)Copyright Celestica Inc. 2015. All rights reserved.				
 *
 ** CSDOEMCmds.c
 **	Define all CSD OEM IPMI commands.
 ** Created on: 	Dec 30, 2018
 ** Author: 		Simon Sun
 *******************************************************************************/
#include "IPMIDefs.h"
#include "API.h"
#include "cmdselect.h"
#include "PDKCmdselect.h"
#include "hal_hw.h"
//#include "Ocelot_Cooling.h"
#include "OEMPDK.h"
#include "IPMI_FRU.h"
#include "PDKEEPROM.h"
#include "NVRAPI.h"
#include "OEMCSDCmds.h"
#include "CSDDynLog.h"
//#include "math.h"

#define CSD_DUMP_TYPE_FULL 	0x00
#define CSD_DUMP_TYPE_MINI 	0x01

#define CSD_TFTP_SRVIP_V4 	0x01
#define CSD_TFTP_SRVIP_V6 	0x02

#define MIN_DUMP_SCRIPT_FULLPATH "/conf/BMC2/mindumpentry.sh"
#define CHECK_DUMP_FILEEXIST "/conf/BMC2/checkdumpfile.sh"
#define DUMP_PERCENT_FILE "/tmp/CSD/dump_percent.dat"
#define FILE_EXIST_CHK_RESULT "/tmp/CSD/dumpfileresult.dat"
#define IP_ADDR_FILE      "/tmp/CSD/ipaddr.dat"
#define TFTP_DWNLD_SCRIPT  "/conf/BMC2/tftpdownload.sh"



pthread_mutex_t mutexDumpFlag = PTHREAD_MUTEX_INITIALIZER; //mutex for dump process flag

static UINT32 gDumpProcStat = NOT_DUMP;  //flag indicate Dump status

pthread_mutex_t mutexTftpFlag = PTHREAD_MUTEX_INITIALIZER; //mutex for tftp transfer flag

static UINT32 gTftpStat = NOT_TRANS;  //flag indicate Tftp status


extern int InitCSDDynLog();



/**
 * @fn ClsFullDumpFunc
 * @brief This function work as thread call bash script.
 * It need modify 
 * @param FullDump
 * @return zero means OK. others Err.
 */
//void* ClsFullDumpFunc(void* pArg)
//{
//	
//}


/**
 * @fn ClsMinDumpFunc
 * @brief This function work as thread call bash script.
 * It need modify 
 * @param FullDump or MinDump
 * @return zero means OK. others Err.
 */
void* ClsMinDumpFunc(void* pArg)
{
    #define TMP_BUFF_LEN 200
	UN_USED(pArg);
	INT8 shCmds[TMP_BUFF_LEN] = {0};
	memset(shCmds,0,TMP_BUFF_LEN);
    sprintf(shCmds,"sh %s ",MIN_DUMP_SCRIPT_FULLPATH);
    system(shCmds);
//	system("sh /conf/BMC2/hello.sh");
	
	if(pthread_mutex_lock(&mutexDumpFlag) != 0 ){
//		suppose not run here 
//		and can't use try because if not block here gDumpProcStat can't be IN_DUMP again
		//TDBG("pthread_mutex_trylock failed in Cmd_DumpTrigger\n");
		printf("pthread_mutex_lock failed in ClsMinDumpFunc\n");	
		return NULL ;
	}
	
	gDumpProcStat = NOT_DUMP;
	
	if(pthread_mutex_unlock(&mutexDumpFlag) != 0){
		//TDBG("pthread_mutex_unlock failed in Cmd_DumpTrigger\n");
		printf("pthread_mutex_unlock failed in ClsMinDumpFunc\n");
		
	}
	printf("finished ClsMinDumpFunc\n");
	return NULL;
}

/**
 * @fn TriggerDump
 * @brief This function Create Dump thread.
 * @param FullDump or MinDump
 * @return zero means OK. others Err.
 */
static int TriggerDump(INT8U dumpType)
{
	//start thread to do dump mission
	if(CSD_DUMP_TYPE_FULL == dumpType)
	{
		
	}else
	{
		pthread_t pThreadID; 
		gthreadIndex++;
		printf("Creating Minium dump thread with index %d\n", gthreadIndex);
		OS_CREATE_TASK_THREAD(ClsMinDumpFunc, NULL,err,pThreadID);

	}
	
	return 0;
}


/**
 * @fn Cmd_DumpTrigger
 * @brief This function trigger CSD dump.
 * @param Request message and BMC instance
 * @return Completion code
 */
static int Cmd_DumpTrigger(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst)
{
	_NEAR_ CSDOEMDumpTriggerReq_T* pDumpTriggerReq = (_NEAR_ CSDOEMDumpTriggerReq_T*) pReq;
	_NEAR_ CSDOEMDumpTriggerRes_T* pDumpTriggerRes = (_NEAR_ CSDOEMDumpTriggerRes_T*) pRes;
	TDBG("\n pReq,ReqLen,BMCInst parameters : %d\t%c\t%d\n",pReq,ReqLen,BMCInst);
	pDumpTriggerRes->CompletionCode = CC_NORMAL;
	
	if ((CSD_DUMP_TYPE_FULL != pDumpTriggerReq->Dump_Type) &&
		(CSD_DUMP_TYPE_MINI != pDumpTriggerReq->Dump_Type))
	{
		pDumpTriggerRes->CompletionCode = CC_PARAM_OUT_OF_RANGE;
		return sizeof(CSDOEMDumpTriggerRes_T);
	}
	//Need add mutex to avoid competition
	if(pthread_mutex_trylock(&mutexDumpFlag) != 0 )
	{
		//TDBG("pthread_mutex_trylock failed in Cmd_DumpTrigger\n");
		printf("pthread_mutex_trylock failed in Cmd_DumpTrigger\n");
		pDumpTriggerRes->CompletionCode = CC_GET_SESSION_INVALID_USER;
		return sizeof(CSDOEMDumpTriggerRes_T);
	}
	printf("run Cmd_DumpTrigger here\n");
	if(IN_DUMP==gDumpProcStat)
	{
		//release lock
		if(pthread_mutex_unlock(&mutexDumpFlag) != 0){
			//TDBG("pthread_mutex_unlock failed in Cmd_DumpTrigger\n");
			printf("pthread_mutex_unlock failed in Cmd_DumpTrigger\n");
		    pDumpTriggerRes->CompletionCode = IPMI_CMD_UNKNOWN;
		    return sizeof(CSDOEMDumpTriggerRes_T);
		}	
		pDumpTriggerRes->CompletionCode = CC_GET_SESSION_INVALID_USER;
		return sizeof(CSDOEMDumpTriggerRes_T);
	}
	
	gDumpProcStat = IN_DUMP;
	//release lock
	if(pthread_mutex_unlock(&mutexDumpFlag) != 0){
		//TDBG("pthread_mutex_unlock failed in Cmd_DumpTrigger\n");
		printf("pthread_mutex_unlock failed in Cmd_DumpTrigger\n");
	    pDumpTriggerRes->CompletionCode = IPMI_CMD_UNKNOWN;
	    return sizeof(CSDOEMDumpTriggerRes_T);
	}
	//Trigger Dump progress
	if(0 != TriggerDump(pDumpTriggerReq->Dump_Type))
	{
		pDumpTriggerRes->CompletionCode = IPMI_CMD_UNKNOWN;
	}	
	
	

	
	return sizeof(CSDOEMDumpTriggerRes_T);
	
}


/**
 * @fn check_dump_exist
 * @brief This function check value of script check dump file.
 * @param Request message and BMC instance
 * @return 0 no file, 2 existed, 0xff unknown error
 */
INT8U check_dump_exist()
{
	FILE *fd; 
	UINT32 data_len = 0;
	INT8 checkResult[10];
    fd = fopen(FILE_EXIST_CHK_RESULT,"rb+");
    if(!fd)
    {
    	printf("Open check dump file result error\n");
    	return IPMI_CMD_UNKNOWN;
    }
    fseek(fd,0,SEEK_SET);
    data_len = fread(checkResult,sizeof(INT8U),1,fd);
    if(data_len<1)
    {
    	printf("error read dump file check result\n");
    	fclose(fd);
    	return IPMI_CMD_UNKNOWN;
    }
    if(strstr(checkResult,"1")==NULL)
    {
    	return NO_DUMP_EXIST;
    }
	return EXISTED_DUMP;
}


/**
 * @fn getDumpPercent
 * @brief This function check value of dump percentage.
 * @param None.
 * @return 0 - 99 UINT8 value mean percentage,FF mean error
 */
static INT8U getDumpPercent()
{
	#define READBUFF_LEN 100
	FILE *fd; 
	UINT32 data_len = 0;
	INT8 checkResult[READBUFF_LEN];
	fd = fopen(DUMP_PERCENT_FILE,"rb+");
	if(!fd)
	{
		printf("Open getDumpPercent file error\n");
	    return IPMI_CMD_UNKNOWN;
	}
	fseek(fd,0,SEEK_SET);
	data_len = fread(checkResult,1,READBUFF_LEN,fd);
	if(data_len<1)
	{
	    printf("error read dump file check result\n");
	    fclose(fd);
	    return IPMI_CMD_UNKNOWN;
	}
	INT8 *pend;
    UINT32 dumpProcNum = 0;
    UINT32 dumpAllNum = 1; //not 0 avoid divided by 0
    //printf("data is %x %x %x %x\n",checkResult[0],checkResult[1],checkResult[2],checkResult[3]);
    //strtoul need blank to sp
    dumpProcNum = (UINT32)strtoul(checkResult,&pend,10);
    dumpAllNum = (UINT32)strtoul(pend,NULL,10);
//    printf("up is %d, down is %d\n",dumpProcNum,dumpAllNum);
    if(dumpAllNum)
    {
    	return (UINT8)(((float)dumpProcNum*100)/((float)dumpAllNum));
    }else{
    	printf("getDumpPercent: divided by zero\n");
    	return IPMI_CMD_UNKNOWN;
    }
}


/**
 * @fn Cmd_GetCollectStatus
 * @brief This function get collection status.
 * @param Request message and BMC instance
 * @return Completion code
 */
static int Cmd_GetCollectStatus(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst)
{
    #define BUFF_LEN 200
	UN_USED(pReq);
	UN_USED(ReqLen);
	UN_USED(BMCInst);
	INT8 shCmds[BUFF_LEN] = {0};
	memset(shCmds,0,BUFF_LEN);
	_NEAR_ CSDGetCollectStatusRes_T* pGetCollectStatusRes = (_NEAR_ CSDGetCollectStatusRes_T*) pRes;
	
	pGetCollectStatusRes->CompletionCode = CC_NORMAL;
	
	//test gDumpProcStat
	//don't need get lock because we don't modify data
	if(IN_DUMP==gDumpProcStat)
	{
        //get percentage
	    pGetCollectStatusRes->DumpStatus = DUMP_ON_WAY;
	    pGetCollectStatusRes->CompletionCode = CC_SUCCESS; 
	    pGetCollectStatusRes->DumpPercentage = getDumpPercent();
		return sizeof(CSDGetCollectStatusRes_T);
	}else
	{
		//call ash shell check file existed
	    sprintf(shCmds,"sh %s ",CHECK_DUMP_FILEEXIST);
	    system(shCmds);
	    pGetCollectStatusRes->DumpStatus = check_dump_exist();
	    pGetCollectStatusRes->CompletionCode = CC_SUCCESS; 		
	    return (sizeof(CSDGetCollectStatusRes_T) - 1);
	}

	
}

/**
 * @fn Cmd_ReadLogMask
 * @brief This function set log mask.
 * @param Request message and BMC instance
 * @return Completion code
 */
static int Cmd_ReadLogMask(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst)
{
	_NEAR_ CSDOEMReadLogMaskReq_T* pReadLogMaskReq = (_NEAR_ CSDOEMReadLogMaskReq_T*) pReq;
	_NEAR_ CSDOEMReadLogMaskRsp_T* pReadLogMaskRes = (_NEAR_ CSDOEMReadLogMaskRsp_T*) pRes;
	TDBG("\n pReq,ReqLen,BMCInst parameters : %d\t%c\t%d\n",pReq,ReqLen,BMCInst);
	TDBG("\n pSetLogMaskReq: %x %x %x\n",pReadLogMaskReq->Task_ID,pReadLogMaskReq->Component_ID);
	
	int ret = CSDReadLogMask(pReadLogMaskReq->Task_ID, 
			pReadLogMaskReq->Component_ID, 
			&(pReadLogMaskRes->MASK));
	pReadLogMaskRes->Task_ID = pReadLogMaskReq->Task_ID;
	pReadLogMaskRes->Component_ID = pReadLogMaskReq->Component_ID;
	if (CSD_CONFIG_SUCCESS == ret)
	{
		pReadLogMaskRes->CompletionCode = CC_SUCCESS;

	}else if(CSD_CONFIG_FAILURE>ret)
	{
		if(CSD_READLOG_NOSERVICE==ret){
			pReadLogMaskRes->CompletionCode = IPMI_CMD_READLOGMSK_NOSERVICE;
		}else{
			pReadLogMaskRes->CompletionCode = IPMI_CMD_UNKNOWN;
		}
	}
	else
	{
		pReadLogMaskRes->CompletionCode = IPMI_CMD_UNKNOWN;
	}
	
	return sizeof(CSDOEMReadLogMaskRsp_T);
}



/**
 * @fn ClsTftpDownloadFunc
 * @brief This function work as thread call bash script.
 * @param transfer file to host
 * @return zero means OK. others Err.
 */
void* ClsTftpDownloadFunc(void* pArg)
{
    #define TMP_BUFF_LEN 200
	UN_USED(pArg);
	INT8 shCmds[TMP_BUFF_LEN] = {0};
	
	memset(shCmds,0,TMP_BUFF_LEN);
    sprintf(shCmds,"sh %s ",TFTP_DWNLD_SCRIPT);
    system(shCmds);

	if(pthread_mutex_lock(&mutexTftpFlag) != 0 ){
//		suppose not run here 
//		and can't use try because if not block here gTftpStat can't be IN_TRANS again
		printf("pthread_mutex_lock failed in ClsTftpDownloadFunc\n");	
		return NULL ;
	}
	
	gTftpStat = NOT_TRANS;
	
	if(pthread_mutex_unlock(&mutexTftpFlag) != 0){
		printf("pthread_mutex_unlock failed in ClsTftpDownloadFunc\n");
		
	}
	printf("finished ClsTftpDownloadFunc\n");
	return NULL;
}


/**
 * @fn TriggerTftpTrans
 * @brief This function set host IP address into file and trigger trans thread
 * @param Request message and BMC instance
 * @return Completion code
 */
INT8U TriggerTftpTrans(INT8U addrType,INT32U IPAddr)
{
    #undef TMP_BUFF_LEN
	#define TMP_BUFF_LEN 200
	INT8 shCmds[TMP_BUFF_LEN] = {0};
	memset(shCmds,0,TMP_BUFF_LEN);
	
	system(shCmds);
	//create IP value in data file
    if(CSD_TFTP_SRVIP_V4==addrType)
    {
    	INT8 *addr = (INT8*)(&IPAddr);
        sprintf(shCmds,"echo __HOST_IPADDR=%d.%d.%d.%d > %s",addr[0],addr[1],addr[2],addr[3],IP_ADDR_FILE);
    	system(shCmds);
    	
		pthread_t pThreadID; 
		gthreadIndex++;
		printf("Creating tftp transfer thread with index %d\n", gthreadIndex);
		OS_CREATE_TASK_THREAD(ClsTftpDownloadFunc, NULL,err,pThreadID);

    	
    }else{
    	
    	
    }
	return 0;
}


/**
 * @fn Cmd_TftpDownload
 * @brief This function set host IP address
 * And trigger push sh shell script to download file to server.
 * @param Request message and BMC instance
 * @return Completion code
 */
static int Cmd_TftpDownload(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst)
{
	_NEAR_ CSDOEMTftpDwnldReq_T* pTftpDwnldReq = (_NEAR_ CSDOEMTftpDwnldReq_T*) pReq;
	_NEAR_ CSDOEMTftpDwnldRsp_T* pTftpDwnldRsp = (_NEAR_ CSDOEMTftpDwnldRsp_T*) pRes;
	TDBG("\n pReq,ReqLen,BMCInst parameters : %d\t%c\t%d\n",pReq,ReqLen,BMCInst);
	printf("\n pTftpDwnldReq: %d %x\n",pTftpDwnldReq->AddressType,pTftpDwnldReq->IPv4Addr);//,pTftpDwnldReq->IPv6Addr);
	
	pTftpDwnldRsp->CompletionCode = CC_NORMAL;
		
		if ((CSD_TFTP_SRVIP_V4 != pTftpDwnldReq->AddressType) &&
			(CSD_TFTP_SRVIP_V6 != pTftpDwnldReq->AddressType))
		{
			pTftpDwnldRsp->CompletionCode = CC_PARAM_OUT_OF_RANGE;
			return sizeof(CSDOEMTftpDwnldRsp_T);
		}
		//Need add mutex to avoid competition
		if(pthread_mutex_trylock(&mutexTftpFlag) != 0 )
		{
			//TDBG("pthread_mutex_trylock failed in Cmd_DumpTrigger\n");
			printf("pthread_mutex_trylock failed in Cmd_TftpDownload\n");
			pTftpDwnldRsp->CompletionCode = CC_GET_SESSION_INVALID_USER;
			return sizeof(CSDOEMTftpDwnldRsp_T);
		}
		printf("run Cmd_TftpDownload here\n");
		if(IN_TRANS==gTftpStat)
		{
			//release lock
			if(pthread_mutex_unlock(&mutexTftpFlag) != 0){
				//should not go here
				printf("pthread_mutex_unlock failed in Cmd_TftpDownload\n");
				pTftpDwnldRsp->CompletionCode = IPMI_CMD_UNKNOWN;
				return sizeof(CSDOEMTftpDwnldRsp_T);
			}	
			pTftpDwnldRsp->CompletionCode = CC_GET_SESSION_INVALID_USER;
			return sizeof(CSDOEMTftpDwnldRsp_T);
		}
		
		gTftpStat = IN_TRANS;
		//release lock
		if(pthread_mutex_unlock(&mutexTftpFlag) != 0){
			printf("pthread_mutex_unlock failed in Cmd_TftpDownload\n");
			pTftpDwnldRsp->CompletionCode = IPMI_CMD_UNKNOWN;
		    return sizeof(CSDOEMTftpDwnldRsp_T);
		}

		//Trigger Tftp transfer progress
		if(0 != TriggerTftpTrans(pTftpDwnldReq->AddressType,pTftpDwnldReq->IPv4Addr))
		{
			pTftpDwnldRsp->CompletionCode = IPMI_CMD_UNKNOWN;
		}	
		
		

		
		return sizeof(CSDOEMTftpDwnldRsp_T);
	
}




/**
 * @fn Cmd_SetLogMask
 * @brief This function set log mask.
 * @param Request message and BMC instance
 * @return Completion code
 */
static int Cmd_SetLogMask(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst)
{
	_NEAR_ CSDOEMSetLogMaskReq_T* pSetLogMaskReq = (_NEAR_ CSDOEMSetLogMaskReq_T*) pReq;
	_NEAR_ CSDOEMSetLogMaskRes_T* pSetLogMaskRes = (_NEAR_ CSDOEMSetLogMaskRes_T*) pRes;
	TDBG("\n pReq,ReqLen,BMCInst parameters : %d\t%c\t%d\n",pReq,ReqLen,BMCInst);
	TDBG("\n pSetLogMaskReq: %x %x %x\n",pSetLogMaskReq->Task_ID,pSetLogMaskReq->Component_ID,pSetLogMaskReq->MASK);
	
	//Set log mask method
	
	int ret = CSDSetLogMask(pSetLogMaskReq->Task_ID, 
						 pSetLogMaskReq->Component_ID, 
						 pSetLogMaskReq->MASK);
	
	if (0 == ret)
	{
		pSetLogMaskRes->CompletionCode = CC_SUCCESS;
	}
	else
	{
		pSetLogMaskRes->CompletionCode = IPMI_CMD_UNKNOWN;
	}
	
	
	return sizeof(CSDOEMSetLogMaskRes_T);
	
}

/**
 * @fn Cmd_ClearLogMask
 * @brief This function set log mask.
 * @param Request message and BMC instance
 * @return Completion code
 */
static int Cmd_ClearLogMask(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst)
{
	_NEAR_ CSDOEMClearLogMaskReq_T* pClearLogMaskReq = (_NEAR_ CSDOEMClearLogMaskReq_T*) pReq;
	_NEAR_ CSDOEMClearLogMaskRes_T* pClearLogMaskRes = (_NEAR_ CSDOEMClearLogMaskRes_T*) pRes;
	TDBG("\n pReq,ReqLen,BMCInst parameters : %d\t%c\t%d\n",pReq,ReqLen,BMCInst);
	TDBG("\n pClearLogMaskReq: %x\n",pClearLogMaskReq->Task_ID);
	//Clear log mask method
	/*
	int ret = ClearLogMask(pClearLogMaskReq->Task_ID);
	
	if (0 == ret)
	{
		pClearLogMaskRes->CompletionCode = CC_SUCCESS;
	}
	else
	{
		pClearLogMaskRes->CompletionCode = IPMI_CMD_UNKNOWN;
	}
	*/
	pClearLogMaskRes->CompletionCode = CC_SUCCESS;
	return sizeof(CSDOEMClearLogMaskRes_T);
	
}


/*NetFn -Application OEM Command Handler to override generic IPMI cmd 
	Commands can be added to the Handler as explained below 
   { CMD_GET_DEV_ID, PRIV_USER, GETDEV_ID,	0x00,  0xAAAA },
   where CMD_GET_DEV_ID - Command no.
			 PRIV_USER			  - Privilege level like administrator,user
			 GETDEV_ID			 -	Function for the command to override
			 0x00					  -  Request length for the command
			 0xAAAA 			   -   Firewall settings 
 */
 CmdHndlrMap_T g_CLS_CSDCmdHndlr[] =	
 {
 /*	 cmd			                    privilege	    cmdhndlr		 	        reqlen 	                            ffconfig    ifcsupport  */
 	{ CMD_CSD_OEM_DUMP_TRIGGER, 	  	PRIV_ADMIN,		Cmd_DumpTrigger, 			sizeof(CSDOEMDumpTriggerReq_T),   	0xAAAA,	  	0xFFFF},
	{ CMD_CSD_OEM_GET_COLLECT_STATUS, 	PRIV_ADMIN,		Cmd_GetCollectStatus, 		0, 	 	                            0xAAAA,   	0xFFFF},
	{ CMD_CSD_OEM_TFTP_DNLD, 	        PRIV_ADMIN,		Cmd_TftpDownload, 		    sizeof(CSDOEMTftpDwnldReq_T), 	 	                            0xAAAA,   	0xFFFF},
	{ CMD_CSD_OEM_READ_LOG_MASK,        PRIV_ADMIN,     Cmd_ReadLogMask,            sizeof(CSDOEMReadLogMaskReq_T),		0xAAAA,	  	0xFFFF},
	{ CMD_CSD_OEM_SET_LOG_MASK,			PRIV_ADMIN,		Cmd_SetLogMask,				sizeof(CSDOEMSetLogMaskReq_T),		0xAAAA,	  	0xFFFF},
	{ CMD_CSD_OEM_CLEAR_LOG_MASK,		PRIV_ADMIN,		Cmd_ClearLogMask,			sizeof(CSDOEMClearLogMaskReq_T), 	0xAAAA,   	0xFFFF},
 };

 
/* Individual command can be Enabled/Disabled using the below tables.
    To Enable/Disable the command "Set BMC GLOBA ENABLES" should be added 
    in table g_app which corresponds to its Net Function (0x6). 
    1) The first entry 'CMD_SET_BMC_GBL_ENABLES' denotes command number. 
    2) The second entry can be ENABLED or DISABLED. 
    3) The third entry should be changed only if logging of 
        "IPMI command support" is enabled. The third entry can be 
        NONE                      - Command will not be logged
        EXT_REQ_LOG         - IPMI command reqest will be logged into extended log (SD Card)
        EXT_RES_LOG         - IPMI command response will be logged into extended log (SD Card)
        VOL_REQ_RES_LOG - Both request and response will be logged into /var/log
*/

 const NetFnCmds_T g_csdOem[] = 
 {
	{ CMD_CSD_OEM_DUMP_TRIGGER        , 	ENABLED, 	NONE},
	{ CMD_CSD_OEM_GET_COLLECT_STATUS	,	ENABLED,	NONE},
	{ CMD_CSD_OEM_TFTP_DNLD	,	            ENABLED,	NONE},
	{ CMD_CSD_OEM_READ_LOG_MASK   ,         ENABLED,    NONE},
	{ CMD_CSD_OEM_SET_LOG_MASK, 			ENABLED, 	NONE},
	{ CMD_CSD_OEM_CLEAR_LOG_MASK, 			ENABLED,	NONE},
	{ 0 					    ,           0,    		NONE},
 };
 


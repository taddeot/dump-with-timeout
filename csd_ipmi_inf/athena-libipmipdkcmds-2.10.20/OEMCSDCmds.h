/*
 *  ** (C)Copyright Celestica Inc. 2015. All rights reserved.
 * OEMCSDCmds.h
 *
 *  Created on: Dec 28, 2018
 *      Author: Simon Sun
 *      This header is for CSD IPMI Commands.
 */

#ifndef OEMCSDCMDS_H_
#define OEMCSDCMDS_H_


#include "Types.h"
#define NETFN_CSD_OEM	0x3E  // 0x3a/0x3b pair request response netfun, 0x3c/0x3d used by ddn, temp use 0x3e

#define CMD_CSD_OEM_DUMP_TRIGGER		0x01
#define CMD_CSD_OEM_GET_COLLECT_STATUS	0x02
#define CMD_CSD_OEM_TFTP_DNLD	        0x03
#define CMD_CSD_OEM_READ_LOG_MASK       0x04
#define CMD_CSD_OEM_SET_LOG_MASK		0x05
#define CMD_CSD_OEM_CLEAR_LOG_MASK		0x06




#define IPMI_CMD_READLOGMSK_NOSERVICE                  0x93

extern  CmdHndlrMap_T g_CLS_CSDCmdHndlr[];  //CLS CSD


/*dump process status*/
enum {
	NOT_DUMP = 0,
	IN_DUMP = 1
};

/*Dump FILE status*/
enum{
	NO_DUMP_EXIST = 0,
	DUMP_ON_WAY = 1,
	EXISTED_DUMP = 2,
};

/*tftp trans status*/
enum {
	NOT_TRANS = 0,
	IN_TRANS = 1
};




/*Cmd_DumpTrigger structure*/
typedef struct
{
	INT8U	 Dump_Type;
} PACKED CSDOEMDumpTriggerReq_T;

typedef struct
{
	INT8U	CompletionCode;
} PACKED CSDOEMDumpTriggerRes_T;


/*Cmd_GetCollectStatus structure*/
typedef struct
{
	INT8U	CompletionCode;
	INT8U	DumpStatus;
	INT8U	DumpPercentage;
} PACKED CSDGetCollectStatusRes_T;

/*Cmd_ReadLogMask structure*/
typedef struct
{
	 INT8U	 Task_ID;
	 INT8U	 Component_ID;
} PACKED CSDOEMReadLogMaskReq_T;


/*TFPT Download request command*/
typedef struct
{
	INT8U	AddressType;
	union{
	INT32U	IPv4Addr;
	//INT32U  IPv6Addr[4];
	};
	
} PACKED CSDOEMTftpDwnldReq_T;

typedef struct
{
	INT8U	CompletionCode;
} PACKED CSDOEMTftpDwnldRsp_T;


typedef struct
{
	INT8U	CompletionCode;
	INT8U	Task_ID;
	INT8U	Component_ID;
	INT32U	MASK;
} PACKED CSDOEMReadLogMaskRsp_T;

/*Cmd_SetLogMask structure*/
typedef struct
{
	 INT8U	 Task_ID;
	 INT8U	 Component_ID;
	 INT32U	 MASK;
} PACKED CSDOEMSetLogMaskReq_T;

typedef struct
{
	INT8U	CompletionCode;
} PACKED CSDOEMSetLogMaskRes_T;

/*Cmd_ClearLogMask structure*/
typedef struct
{
	 INT8U	 Task_ID;
} PACKED CSDOEMClearLogMaskReq_T;

typedef struct
{
	INT8U	CompletionCode;
} PACKED CSDOEMClearLogMaskRes_T;



#endif /* OEMCSDCMDS_H_ */

/*
 * ThorPDK.h
 *
 *  Created on: May 13, 2015
 *      Author: author@celestica.com
 *      ThorPDK.h
 *      Define basic protypes, macros etc.
 */

#ifndef THORPDK_H_
#define THORPDK_H_

#include "Types.h"
#include "hal_hw.h"
#include "Debug.h"
//#include "IPMIConf.h"

extern UINT8 g_DebugLevel;

#define HEALTH_MODULE 			5
#define SENSOR_MODULE 			6
#define STORAGE_MODULE 			7
#define COOLING_MODULE 			8
#define NODE_MANAGER_MODULE 	9
#define COOLING_0		(COOLING_MODULE << 4 | 0x0)
#define COOLING_1		(COOLING_MODULE << 4 | 0x1)
#define COOLING_2		(COOLING_MODULE << 4 | 0x2)
#define NM_0			(NODE_MANAGER_MODULE << 4 | 0x0)
#define NM_2			(NODE_MANAGER_MODULE << 4 | 0x2)
#define NM_(level)		(NODE_MANAGER_MODULE << 4 | (level))
#define SENSOR_(level)	(SENSOR_MODULE << 4 | (level))
#define HEALTH_(level)	(HEALTH_MODULE << 4 | (level))
#define STORAGE_(level)	(STORAGE_MODULE << 4 | (level))
#define NVME_TEST				(0xF0)
#define COLD_RESET_TEST			(0xF1)
#define ENABLE_FAN_FAIL			(0xFC)
#define DISABLE_FAN_FAIL		(0xFD)
#define NO_SENSOR_READING		(0xFE)
#define NO_PRINT				(0xFF)


#define DEBUG_PRINT(level, args...) \
	if ((level) <= g_DebugLevel && ((level) >> 4 == (g_DebugLevel) >> 4)) \
		printf(args)


#define ENABLE 				1
#define DISABLE 			0
#define GPIO_LOW			0
#define GPIO_HIGH			1

#define SKU_LOKI 			0x01
#define SKU_TYR 			0x10
#define SKU_LOKI_2NVME 		2
#define SKU_LOKI_4NVME 		4
#define SKU_LOKI_10NVME 	10
#define SKU_TYR_0NVME 		0
#define SKU_TYR_35_HDD 		(12 | 0x80)   //0x8c
#define SKU_TYR_4NVME 		4
#define SKU_TYR_8NVME 		8
#define SKU_TYR_12NVME 		12
#define SKU_TYR_24NVME 		24

#define RISER_16X_4NVME 	1
#define RISER_8X_2NVME		4
#define RISER_16X_SLOT		14
#define RISER_6NVME			9
#define RISER_PN_LENGTH		14

#define MFG_HGST			31563	// 7B4B
#define MFG_CELESTICA		12290 	// 3002h
#define MFG_SANGFOR			35047	// 88E7h
#define MFG_TRUMP			2905	// B59h

enum {
	GPIO_A0=0, 	GPIO_A1,GPIO_A2, GPIO_A3, GPIO_A4, GPIO_A5, GPIO_A6, GPIO_A7,
	GPIO_B0=8,	GPIO_B1,GPIO_B2,GPIO_B3,GPIO_B4,GPIO_B5,GPIO_B6,GPIO_B7,
	GPIO_C0=16,	GPIO_C1,GPIO_C2,GPIO_C3,GPIO_C4,GPIO_C5,GPIO_C6,GPIO_C7,
	GPIO_D0=24,	GPIO_D1,GPIO_D2,GPIO_D3,GPIO_D4,GPIO_D5,GPIO_D6,GPIO_D7,
	GPIO_E0=32,	GPIO_E1,GPIO_E2,GPIO_E3,GPIO_E4,GPIO_E5,GPIO_E6,GPIO_E7,
	GPIO_F0=40,	GPIO_F1,GPIO_F2,GPIO_F3,GPIO_F4,GPIO_F5,GPIO_F6,GPIO_F7,
	GPIO_G0=48,	GPIO_G1,GPIO_G2,GPIO_G3,GPIO_G4,GPIO_G5,GPIO_G6,GPIO_G7,
	GPIO_H0=56,	GPIO_H1,GPIO_H2,GPIO_H3,GPIO_H4,GPIO_H5,GPIO_H6,GPIO_H7,
	GPIO_I0=64,	GPIO_I1,GPIO_I2,GPIO_I3,GPIO_I4,GPIO_I5,GPIO_I6,GPIO_I7,
	GPIO_J0=72,	GPIO_J1,GPIO_J2,GPIO_J3,GPIO_J4,GPIO_J5,GPIO_J6,GPIO_J7,
	GPIO_K0=80,	GPIO_K1,GPIO_K2,GPIO_K3,GPIO_K4,GPIO_K5,GPIO_K6,GPIO_K7,
	GPIO_L0=88,	GPIO_L1,GPIO_L2,GPIO_L3,GPIO_L4,GPIO_L5,GPIO_L6,GPIO_L7,
	GPIO_M0=96,	GPIO_M1,GPIO_M2,GPIO_M3,GPIO_M4,GPIO_M5,GPIO_M6,GPIO_M7,
	GPIO_N0=104,GPIO_N1,GPIO_N2,GPIO_N3,GPIO_N4,GPIO_N5,GPIO_N6,GPIO_N7,
	GPIO_O0=112,GPIO_O1,GPIO_O2,GPIO_O3,GPIO_O4,GPIO_O5,GPIO_O6,GPIO_O7,
	GPIO_P0=120,GPIO_P1,GPIO_P2,GPIO_P3,GPIO_P4,GPIO_P5,GPIO_P6,GPIO_P7,
	GPIO_Q0=128,GPIO_Q1,GPIO_Q2,GPIO_Q3,GPIO_Q4,GPIO_Q5,GPIO_Q6,GPIO_Q7,
	GPIO_R0=136,GPIO_R1,GPIO_R2,GPIO_R3,GPIO_R4,GPIO_R5,GPIO_R6,GPIO_R7,
	GPIO_S0=144,GPIO_S1,GPIO_S2,GPIO_S3,GPIO_S4,GPIO_S5,GPIO_S6,GPIO_S7,
	GPIO_T0=152,GPIO_T1,GPIO_T2,GPIO_T3,GPIO_T4,GPIO_T5,GPIO_T6,GPIO_T7,
	GPIO_U0=160,GPIO_U1,GPIO_U2,GPIO_U3,GPIO_U4,GPIO_U5,GPIO_U6,GPIO_U7,
	GPIO_V0=168,GPIO_V1,GPIO_V2,GPIO_V3,GPIO_V4,GPIO_V5,GPIO_V6,GPIO_V7,
	GPIO_W0=176,GPIO_W1,GPIO_W2,GPIO_W3,GPIO_W4,GPIO_W5,GPIO_W6,GPIO_W7,
	GPIO_X0=184,GPIO_X1,GPIO_X2,GPIO_X3,GPIO_X4,GPIO_X5,GPIO_X6,GPIO_X7,
	GPIO_Y0=192,GPIO_Y1,GPIO_Y2,GPIO_Y3,GPIO_Y4,GPIO_Y5,GPIO_Y6,GPIO_Y7,
	GPIO_Z0=200,GPIO_Z1,GPIO_Z2,GPIO_Z3,GPIO_Z4,GPIO_Z5,GPIO_Z6,GPIO_Z7,
	GPIO_AA0=208,GPIO_AA1,GPIO_AA2,GPIO_AA3,GPIO_AA4,GPIO_AA5,GPIO_AA6,GPIO_AA7,
	GPIO_AB0=216,GPIO_AB1,GPIO_AB2,GPIO_AB3,GPIO_AB4,GPIO_AB5,GPIO_AB6,GPIO_AB7,
};

/*Loki GPIO define*/
#define	IO_IRQ_PSU_ALERT_BUF_N		25		//GPIOD1
#define	IO_BMC_PWRBTN_IN_L			GPIO_E0 //32		//GPIOE0
#define	IO_BMC_PWRBTN_OUT_L			33		//GPIOE1
#define	IO_RST_BMC_RSTBTN_OUT_L		35		//GPIOE3
#define IO_PANEL_UID_BTN_L  		36   	//GPIOE4
#define IO_FP_ID_LED_N  			40   	//GPIOF0
#define IO_PWRGD_PS_PWROK1			42
#define IO_PWRGD_SYS_PWROK  		43   	//GPIOF3
#define IO_BIOS_POST_COMPLETE_N  	GPIO_F5
#define IO_BACK_UID_BUTTON			GPIO_J3 
#define IO_PWRGD_PS_PWROK0			101		//GPIOM5	
#define IO_FP_LED_STATUS_AMBER_R_N 	139   	//GPIOR3
#define IO_CPU0_SKTOCC_N 			140   	
#define IO_CPU1_SKTOCC_N 			141   	
#define IO_PCH_SLP_S4_N  			193   	//GPIOY1
#define IO_BMC_PCH_NMI  			214   	//GPIOAA6



// Loki Sensor Number definition
#define SN_INLET1_TEMP                  1
#define SN_INLET2_TEMP                  2
#define SN_PCI_ZONE1_TEMP               3
#define SN_PCI_ZONE2_TEMP               4
#define SN_FP_INLET_TEMP                5
#define SENSOR_CPU0_TEMP				(0x6)
#define SENSOR_CPU1_TEMP				(0x7)
#define SENSOR_CPU0_DIMMM0_TEMP			(0x8)
#define SENSOR_CPU0_DIMMM1_TEMP			(0x9)
#define SENSOR_CPU0_DIMMM2_TEMP			(0xA)
#define SENSOR_CPU0_DIMMM3_TEMP			(0xB)
#define SENSOR_CPU0_DIMMM4_TEMP			(0xC)
#define SENSOR_CPU0_DIMMM5_TEMP			(0xD)
#define SENSOR_CPU0_DIMMM6_TEMP			(0xE)
#define SENSOR_CPU0_DIMMM7_TEMP			(0xF)
#define SENSOR_CPU0_DIMMM8_TEMP			(0x10)
#define SENSOR_CPU0_DIMMM9_TEMP			(0x11)
#define SENSOR_CPU0_DIMMM10_TEMP		(0x12)
#define SENSOR_CPU0_DIMMM11_TEMP		(0x13)
#define SENSOR_CPU1_DIMMM0_TEMP			(0x14)
#define SENSOR_CPU1_DIMMM1_TEMP			(0x15)
#define SENSOR_CPU1_DIMMM2_TEMP			(0x16)
#define SENSOR_CPU1_DIMMM3_TEMP			(0x17)
#define SENSOR_CPU1_DIMMM4_TEMP			(0x18)
#define SENSOR_CPU1_DIMMM5_TEMP			(0x19)
#define SENSOR_CPU1_DIMMM6_TEMP			(0x1A)
#define SENSOR_CPU1_DIMMM7_TEMP			(0x1B)
#define SENSOR_CPU1_DIMMM8_TEMP			(0x1C)
#define SENSOR_CPU1_DIMMM9_TEMP			(0x1D)
#define SENSOR_CPU1_DIMMM10_TEMP		(0x1E)
#define SENSOR_CPU1_DIMMM11_TEMP		(0x1F)
#define SENSOR_PCH_TEMP					(0x20)

#define SENSOR_NVME1_TEMP               (0x21)
#define SENSOR_NVME2_TEMP               (0x22)
#define SENSOR_NVME3_TEMP               (0x23)
#define SENSOR_NVME4_TEMP               (0x24)
#define SENSOR_NVME5_TEMP               (0x25)
#define SENSOR_NVME6_TEMP               (0x26)
#define SENSOR_NVME7_TEMP               (0x27)
#define SENSOR_NVME8_TEMP               (0x28)
#define SENSOR_NVME9_TEMP            	(0x29)
#define SENSOR_NVME10_TEMP              (0x2a)
//#define SENSOR_NVME_BP1_TEMP            (0x2b)
//#define SENSOR_NVME_BP2_TEMP            (0x2c)
//#define SENSOR_NVME_SW1_TEMP            (0x2d)
//#define SENSOR_NVME_SW2_TEMP            (0x2e)
#define SENSOR_GPU1_TEMP1 	           	(0x2f)
#define SENSOR_GPU1_TEMP2 	           	(0x30)
#define SENSOR_GPU2_TEMP1 	           	(0x31)
#define SENSOR_GPU2_TEMP2	            (0x32)

#define SENSOR_PVCCIN_CPU0                                        (57) //0x39
#define SENSOR_PVCCIN_CPU1                                        (58) //0x3a
//#define SENSOR_PVDDQ_CPU0_ABC									  (0x2E)
//#define SENSOR_PVDDQ_CPU0_DEF									  (0x2F)
//#define SENSOR_PVDDQ_CPU1_GHJ									  (0x30)
//#define SENSOR_PVDDQ_CPU1_KLM									  (0X31)
//#define SENSOR_PVCCIO_CPU0										  (0x32)
#define SENSOR_PVCCIO_CPU1										  (0X33)
#define SENSOR_P1V05_PCH										  (0x34)
#define SENSOR_PVNN_PCH											  (0x35)
#define SENSOR_PGPPA_AUX										  (0x36)
#define SENSOR_PV3V3											  (0x37)
#define SENSOR_P5V												  (0x38)
//#define SENSOR_P12V												  (0x39)
//#define SENSOR_NODE_VOLT										  (0x3A)
#define SENSOR_NODE_CURRENT										  (0x3B)
#define SENSOR_NODE_PWR_CONSUME									  (0x3C)

#define SENSOR_PSU0_TEMP									      (0x41)
//#define SENSOR_PSU0_VOLT									      (0x42)
#define SENSOR_PSU0_FAN									          (0x42)
#define SENSOR_PSU0_CURRENT									      (0x43)
//#define SENSOR_PSU0_PWR_CONSUME									  (0x45)
#define SENSOR_PSU1_TEMP									      (0x46)
//#define SENSOR_PSU1_VOLT									      (0x47)
#define SENSOR_PSU1_FAN									          (0x47)
#define SENSOR_PSU1_CURRENT									      (0x48)
//#define SENSOR_PSU1_PWR_CONSUME									  (0x4a)

#define SENSOR_PSU0_STATUS                                        (0x60)
#define SENSOR_PSU1_STATUS                                        (0x61)

#define SENSOR_FAN_FAIL                                           (0x67)
#define SENSOR_FAN_TACH0                                          (0x71)
#define SENSOR_FAN_TACH1                                          (0x72)
#define SENSOR_FAN_TACH2                                          (0x73)
#define SENSOR_FAN_TACH3                                          (0x74)
#define SENSOR_FAN_TACH4                                          (0x75)
#define SENSOR_FAN_TACH5                                          (0x76)
#define SENSOR_FAN_TACH6                                          (0x77)
#define SENSOR_FAN_TACH7                                          (0x78)
#define SENSOR_FAN_TACH8                                          (0x79)
#define SENSOR_FAN_TACH9                                          (0x7a)

#define SENSOR_DRIVE_HOTSWAP                                      (0x90)



#define SENSOR_UNIT_STATUS                                        (0x80)
#define SENSOR_FP_BUTTON                                          (0x81)
#define SENSOR_LOG_STAT                                           (0x82)
#define SENSOR_CRI_INTERRUPT                                      (0x85)


typedef struct
{
	INT8U	Enable;
	INT8U	GpioNum;	
} GpioState_T;

#define REG_RW_API

#define LED_BMC_HEARTBEAT 	0x00
#define LED_BMC_UID 	    0x01


#define NODE_NUM0            0
#define NODE_NUM1            1
#define NODE_NUM2            2
#define NODE_NUM3            3

#define MAX_NODE_NUM            1
#define MAX_SLOT_INFO_LEN		128

int PullGpio(UINT8 pinNum, UINT8 level);
int WriteReadI2C_Fixed(INT8U Bus,     INT8U SlaveID,
                        INT8U NumWrite, _NEAR_ INT8U* WriteBuf,
                        INT8U NumRead,  _NEAR_ INT8U* ReadBuf);
int FaultLedControl(bool on);
int BackUidControl(bool on);

int PreMonitorPSU(SensorInfo_T *pSensorInfo, int BMCInst);
int PreMonitorCPU(SensorInfo_T *pSensorInfo);
int NVMeTempRead(hal_t *phal, UINT8 NVMeIndex);
int PDK_PreMonitorCriInterrupt (void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PreMonitorFanFail (void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PreMonitorDriveHotswap(void*  pSenInfo,INT8U *pReadFlags,int BMCInst);
int PDK_PreMonitorPsuStatus (void* pSenInfo, INT8U *pReadFlags, int BMCInst);
INT8U GetSkuType(void);
INT8U GetRiserType(void);
INT16U GetCpldVersion(void);
int SetPowerCapping(bool on);
void AcquireI2CMutex(bool bAcquire);
bool isSkuTyr(void);
INT8U GetGPUDeviceID(void);
int CheckGPUTempSensors(int BMCInst);

//modify by zwt
//move from CLSOEMCmds.c
#if 1
#define CMD_SET_DEBUG_LEVEL 			0xA0
#define CMD_SET_FAN_CONTROL 			0x01
#define CMD_GET_FAN_STATUS 				0x02
#define CMD_GET_VPD_DATA 				0x03
#define CMD_GET_CPLD_INFO 				0x04
#define CMD_GET_BOARD_INFO 				0x05
#define CMD_VMD_ENABLE 					0x06

#define CMD_OEM_SET_SYSTEM_INFO			0x07
#define CMD_OEM_GET_SYSTEM_INFO			0x08

#define CMD_OEM_GET_PSU_INFO			0x09
#define CMD_OEM_SNMP_GET_TRAP_FORMAT                0xF2
#define CMD_OEM_SNMP_SET_TRAP_FORMAT                0xF3
#define CMD_OEM_SET_POWER_CAPPING                   0xF4  //DUNCAN ADD 

//Added by Jeffery
#define CMD_CSD_OEM_DUMP_TRIGGER		0x01
#define CMD_CSD_OEM_GET_COLLECT_STATUS	0x02
#define CMD_CSD_OEM_SET_LOG_MASK		0x05
#define CMD_CSD_OEM_CLEAR_LOG_MASK		0x06

	
enum {
	TRAP_NONE_PET,
	TRAP_PET
};

typedef struct {

   INT8U   trapFormat;

} PACKED SNMP_TRAPFORMAT_T;

typedef struct
{
    INT8U   CompletionCode;
    INT8U   trapFormat;

} PACKED CLSOEMGetSNMPTRAPFORMATRes_T;


typedef struct
{
	INT8U   trapFormat;
} PACKED CLSOEMSetSNMPTRAPFORMATReq_T;

typedef struct
{
    INT8U   CompletionCode;

} PACKED CLSOEMSetSNMPTRAPFORMATRes_T;

int OEM_GetSNMPTrapFormat(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst);
int OEM_SetSNMPTrapFormat(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst);
int OEM_SetPowerCapping(_NEAR_ INT8U* pReq, INT8U ReqLen, _NEAR_ INT8U* pRes,int BMCInst);


#define SNMP_EVT_TYPE_FILE(Instance,filename) \
 sprintf(filename,"%s%d/%s",NV_DIR_PATH,Instance,"SnmpEvent.dat")
//#define EVTTYPE_OFFSET 0
//#define EVTTYPE_LEN    0
#define TRAPFORMAT_OFFSET 0
#define TRAPFORMAT_LEN (sizeof(SNMP_TRAPFORMAT_T))

/*OEM_GetFanStatus structure*/
#if 0
typedef struct
{
   INT8U   Fan_Number;

} PACKED CLSOEMGetFanStatusReq_T;
#endif

typedef struct
{
	INT8U	CompletionCode;
	INT8U	ControlMode;
	INT16U	FanFail;
	INT8U	PWMValue;
} PACKED CLSOEMGetFanStatusRes_T;

 /*OEM_SetFanControl structure*/
 typedef struct
 {
	 INT8U	 Fan_Number;
	 INT8U	 Fan_Control;
 
 } PACKED CLSOEMSetFanControlReq_T;
 
 typedef struct
 {
	 INT8U	 CompletionCode;
 
 } PACKED CLSOEMSetFanControlRes_T;
 
 typedef struct
 {
	 INT8U	RiserIndex;
 
 } PACKED CLSOEMGetVPDDataReq_T;

 typedef struct
 {
	 INT8U	 CompletionCode;
	 INT8U	 RiserIndex;
	 INT8U	PartNumber[RISER_PN_LENGTH];
	 INT8U	Address;
	 INT8U 	BusNum;
	 INT8U	Path0;
	 INT8U  Path1;
	 INT8U 	FRUData[MAX_SLOT_INFO_LEN];
 
 } PACKED CLSOEMGetVPDDataRes_T;

typedef struct
{
	INT8U	CompletionCode;
	INT8U	Temp;
	INT8U  	Voltage;
	INT8U  	Current;
//	INT8U  	PowerConsumption;
	INT8U  	FanSpeed;
	INT8U	Mfg_Revision[4];
	INT8U	FW_Revision[8];
} PACKED CLSOEMGetPsuDataRes_T;

typedef struct
{
	INT8U	CompletionCode;
	INT8U	Cpu0DiskNum;
	INT16U	Cpu0DiskPresent;
	INT8U	Cpu1DiskNum;
	INT16U	Cpu1DiskPresent;
} PACKED CLSOEMGetHddInfoRes_T;


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


#define Max_System_Info_Size  100
 
 //CPU
#define Max_CPU_Databuffer_Size  50
#define Max_CPU_Signature_Size  8
#define Max_CPU_CPU_Microcode_Size  10
#define Max_CPU_CPU_Max_Speed_Size  10
#define Max_CPU_Number  2
 
 //DIMM
#define Max_DIMM_Manufacturer_Size  10
#define Max_DIMM_SN_Size  10
#define Max_DIMM_Number 24
 
 //HDD
#define Max_HDD_Capacity_Size  20
#define Max_HDD_Model_Size  20
#define Max_HDD_SN_Size  20
#define Max_HDD_Number  24
 
 //BIOS/ME
#define Max_BIOS_DevName_Size  15
#define Max_BIOS_DevRev_Size  15
#define Max_BIOS_BuildTime_Size  20
#define Max_FW_Number 2
 
 //PCIE
#define Max_PCIE_Number 8
 
 typedef enum
 {
	 SYSINFO_CPU = 1,
	 SYSINFO_DIMM,
	 SYSINFO_HDD,
	 SYSINFO_BIOS,
	 SYSINFO_PCIE,
	 SYSINFO_LAST,
 } SYSINFO_TYPE_T;
 
 typedef struct {
 
	INT8U	CPU_Present;
	INT8U	CPU_DataBuffer[Max_CPU_Databuffer_Size];
	INT8U	CPU_Signature[Max_CPU_Signature_Size];
	INT8U	CPU_Microcode[Max_CPU_CPU_Microcode_Size];
	INT8U	CPU_Max_Speed[Max_CPU_CPU_Max_Speed_Size];
	INT8U	CPU_Core;
	INT8U	CPU_Used_Cores;
	INT16U	 CPU_TDP;
 } PACKED SYSINFO_CPU_T;
 
 typedef struct {
 
	INT8U	DIMM_Present;
	INT8U	DIMM_Manufacturer[Max_DIMM_Manufacturer_Size];
	INT8U	DIMM_SN[Max_DIMM_SN_Size];
	INT16U	 DIMM_Capability;
	INT16U	 DIMM_Speed;
 } PACKED SYSINFO_DIMM_T;
 
 typedef struct {
 
	INT8U	HDD_Present;
	INT8U	HDD_Capacity[Max_HDD_Capacity_Size];
	INT8U	HDD_Model[Max_HDD_Model_Size];
	INT8U	HDD_SN[Max_HDD_SN_Size];
 
 } PACKED SYSINFO_HDD_T;
 
 typedef struct {
 
	INT8U	BIOS_DevName[Max_BIOS_DevName_Size];
	INT8U	BIOS_DevRev[Max_BIOS_DevRev_Size];
	INT8U	BIOS_BuildTime[Max_BIOS_BuildTime_Size];
 
 } PACKED SYSINFO_BIOS_T;
 
 typedef struct {
 
	INT8U	PCIE_Index;
	INT8U	PCIE_Present;
	INT16U	 PCIE_VendorID;
	INT16U	 PCIE_DeviceID;
	INT8U	PCIE_Width;
	INT8U	PCIE_SpeedCapbility;
	INT8U	PCIE_Type;
	INT8U	PCIE_Slot;
	INT8U	PCIE_OnwhichCPU;
	INT8U	PCIE_RiserType;
	INT8U	PCIE_Location;
 } PACKED SYSINFO_PCIE_T;
 
 /**
  * @struct SYSINFO_Hardware_T
 **/
 typedef struct
 {
	SYSINFO_CPU_T		  SysInfo_CPU[Max_CPU_Number+1];
	SYSINFO_DIMM_T		 SysInfo_DIMM[Max_DIMM_Number+1];
	SYSINFO_HDD_T		   SysInfo_HDD[Max_HDD_Number+1];
	SYSINFO_BIOS_T		  SysInfo_FW[Max_FW_Number+1];
	SYSINFO_PCIE_T	 SysInfo_PCIE[Max_PCIE_Number+1];
 
 } PACKED  SYSINFO_Hardware_T;
 
  /*CMD_OEM_GET_SYSTEM_INFO*/
 typedef struct
 {
	 INT8U	 Device_type;
	 INT8U	 NumberofDevice;
 } PACKED CLSOEMGetSysInfoReq_T;
 
 typedef struct
 {
	 INT8U	 CompletionCode;
	 INT8U	 Device_type;
	 INT8U	 NumberofDevice;
	 INT8U	 Information_Data[Max_System_Info_Size];
 
 } PACKED CLSOEMGetSysInfoRes_T;
 
  /*CMD_OEM_SET_SYSTEM_INFO*/
 typedef struct
 {
	 INT8U	 Device_type;
	 INT8U	 NumberofDevice;
	 INT32U   AllPresentMask;
	 INT8U	 Information_Data[Max_System_Info_Size];
 } PACKED CLSOEMSetSysInfoReq_T;
 
 typedef struct
 {
	 INT8U	 CompletionCode;
 
 } PACKED CLSOEMSetSysInfoRes_T;
#endif


#endif






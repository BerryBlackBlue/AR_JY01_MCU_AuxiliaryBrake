#ifndef __CAN_H
#define __CAN_H
#include "sys.h"


#define JY01_EXTID0		0x10F8E8F3	//下位机--->>>居逸驱动器，下位机控制居逸驱动器
#define JY01_EXTID1		0x10F8189A	//居逸驱动器--->>>下位机，居逸驱动器消息反馈

typedef struct {
	u8  DriveSta;
	u8  RunSta;
	u8  SonicSta;
	u8  TargetBrakeVal;
	s16 RealSpeed;
	s16 Alpha;
} LowerHost_info_t;

extern LowerHost_info_t LowerHost_info;

#define CAN_RX0_INT_ENABLE	1		//0,不使能;1,使能.								    

u8 CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);	//CAN初始化
void Get_LowerHost_Data(LowerHost_info_t *LowerHost_info,u8 *buf);
u8 Can_Send_Msg(u8* msg,u8 len,u32 stdId);					//发送数据
u8 Can_Receive_Msg(u8 *buf,u32 *stdId);

#endif


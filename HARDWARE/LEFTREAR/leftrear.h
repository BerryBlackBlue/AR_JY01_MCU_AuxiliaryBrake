#ifndef	__LEFTREAR_H
#define __LEFTREAR_H

#include "sys.h"


/*左后电机控制引脚定义*/
//左后使能（刹车）引脚
//LR_EL -> PA.12	
#define	LR_EL_PORT		GPIOA
#define LR_EL_PIN		GPIO_Pin_12

//左后Z/F引脚
//LR_ZF -> PB.4
#define LR_ZF_PORT		GPIOB
#define LR_ZF_PIN		GPIO_Pin_4

//左后VR引脚
//LR_VR -> PA.11
#define LR_VR_PORT		GPIOA
#define LR_VR_PIN		GPIO_Pin_11

//左后M引脚
//LR_M -> PB.13
#define LR_M_PORT		GPIOB
#define LR_M_PIN		GPIO_Pin_13


extern u16 LR_Count,RR_Count;

void LeftRear_Init(void);
void LeftRear_Ctrl(u8 Dir,u8 throttle,u8 brake);

#endif

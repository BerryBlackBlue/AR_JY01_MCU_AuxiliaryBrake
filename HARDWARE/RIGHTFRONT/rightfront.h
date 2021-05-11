#ifndef	__RIGHTFRONT_H
#define __RIGHTFRONT_H

#include "sys.h"


/*右前电机控制引脚定义*/
//右前使能（刹车）引脚
//RR_EL -> PA.7 -> TIM3_CH2
#define	RF_EL_PORT		GPIOA
#define RF_EL_PIN			GPIO_Pin_7

//右前Z/F引脚
//RR_ZF -> PB.5
#define RF_ZF_PORT		GPIOB
#define RF_ZF_PIN			GPIO_Pin_5

//右前VR引脚
//RR_VR -> PA.9	-> TIM1_CH2
#define RF_VR_PORT		GPIOA
#define RF_VR_PIN			GPIO_Pin_9

//右前M引脚
//RR_M -> PB.11
#define RF_M_PORT		GPIOB
#define RF_M_PIN		GPIO_Pin_11


extern u16 LR_Count,RR_Count;

void RightFront_Init(void);
void RightFront_Ctrl(u8 Dir,u8 throttle,u8 brake);

#endif

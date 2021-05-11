#ifndef	__LEFTFRONT_H
#define __LEFTFRONT_H

#include "sys.h"


/*左前电机控制引脚定义*/
//左前使能（刹车）引脚
//LF_EL -> PB.0	->TIM3_CH3
#define	LF_EL_PORT		GPIOB
#define LF_EL_PIN			GPIO_Pin_0

//左前Z/F引脚
//LF_ZF -> PB.2
#define LF_ZF_PORT		GPIOB
#define LF_ZF_PIN			GPIO_Pin_2

//左前VR引脚
//LF_VR -> PA.8 -> TIM1_CH1
#define LF_VR_PORT		GPIOA
#define LF_VR_PIN			GPIO_Pin_8

//左前M引脚
//LF_M -> PB.10
#define LF_M_PORT		GPIOB
#define LF_M_PIN		GPIO_Pin_10


void LeftFront_Init(void);
void LeftFront_Ctrl(u8 Dir,u8 throttle,u8 brake);

#endif

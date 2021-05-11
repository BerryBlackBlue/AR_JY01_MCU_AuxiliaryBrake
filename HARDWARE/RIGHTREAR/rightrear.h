#ifndef	__RIGHTREAR_H
#define __RIGHTREAR_H

#include "sys.h"

#define MAX_BRAKE_VAL		96
#define MAX_BK		90

/*右后电机控制引脚定义*/
//右后使能（刹车）引脚
//RR_EL -> PB.1 -> TIM3_CH4
#define	RR_EL_PORT		GPIOB
#define RR_EL_PIN			GPIO_Pin_1

//右后Z/F引脚
//RR_ZF -> PB.3
#define RR_ZF_PORT		GPIOB
#define RR_ZF_PIN			GPIO_Pin_3

//右后VR引脚
//RR_VR -> PA.10	-> TIM1_CH3
#define RR_VR_PORT		GPIOA
#define RR_VR_PIN			GPIO_Pin_10

//右后M引脚
//RR_M -> PB.12
#define RR_M_PORT			GPIOB
#define RR_M_PIN			GPIO_Pin_12


extern u16 LR_Count,RR_Count;

void RightRear_Init(void);
void RightRear_Ctrl(u8 Dir,u8 throttle,u8 brake);

#endif

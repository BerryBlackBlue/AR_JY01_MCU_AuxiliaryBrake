#ifndef	__RIGHTFRONT_H
#define __RIGHTFRONT_H

#include "sys.h"


/*��ǰ����������Ŷ���*/
//��ǰʹ�ܣ�ɲ��������
//RR_EL -> PA.7 -> TIM3_CH2
#define	RF_EL_PORT		GPIOA
#define RF_EL_PIN			GPIO_Pin_7

//��ǰZ/F����
//RR_ZF -> PB.5
#define RF_ZF_PORT		GPIOB
#define RF_ZF_PIN			GPIO_Pin_5

//��ǰVR����
//RR_VR -> PA.9	-> TIM1_CH2
#define RF_VR_PORT		GPIOA
#define RF_VR_PIN			GPIO_Pin_9

//��ǰM����
//RR_M -> PB.11
#define RF_M_PORT		GPIOB
#define RF_M_PIN		GPIO_Pin_11


extern u16 LR_Count,RR_Count;

void RightFront_Init(void);
void RightFront_Ctrl(u8 Dir,u8 throttle,u8 brake);

#endif

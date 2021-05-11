#include "timer.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "leftfront.h"
#include "rightfront.h"
#include "leftrear.h"
#include "rightrear.h"
#include "can.h"


/*
*********************************************************************
* @  name :Timer4_Init
* @  func :��ʼ��TIM4���ж�ʱ
* @ prama :��
* @retval :��
*********************************************************************
* @attention :ʹ��TIM4�����ж�
*********************************************************************
*/
void Timer4_Init(void)
{
    TIM_TimeBaseInitTypeDef		TIM_TimeInitStructure;
    NVIC_InitTypeDef			NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

    TIM_TimeInitStructure.TIM_Prescaler = 719;
    TIM_TimeInitStructure.TIM_Period = 99;
    TIM_TimeInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4,&TIM_TimeInitStructure);

    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_ClearFlag(TIM4,TIM_FLAG_Update);

    TIM_Cmd(TIM4,ENABLE);
}

u8 JY_RepMsg[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
/*
*********************************************************************
* @  name :TIM4_IRQHandler
* @  func :TIM4�����жϷ��������
* @ prama :��
* @retval :��
*********************************************************************
* @attention :ÿ1ms����һ�θ����ж�
*********************************************************************
*/
u8 Dir,CtrlSpeed,CtrlBrake;
void TIM4_IRQHandler(void)
{
    static u8 flag_1ms;


    if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)
    {
        TIM_ClearITPendingBit(TIM4,TIM_IT_Update);

        flag_1ms ++;
    }

    if(flag_1ms%60==0)
    {
        /*����״̬*/
        if(LowerHost_info.RunSta==3)
        {
            /*����������*/
            if(LowerHost_info.SonicSta==0)
            {
								CtrlBrake = LowerHost_info.TargetBrakeVal;
								CtrlSpeed = 0;
            }
            /*����������*/
            else
            {
                Dir = 0;
                CtrlSpeed = 0;
                CtrlBrake = MAX_BK;
            }
        }
        /*ɲ��״̬*/
        else
        {
            Dir = 0;
            CtrlSpeed = 0;
            CtrlBrake = MAX_BK;
        }
    }
    if(flag_1ms%70 == 0)
    {
        RightFront_Ctrl(Dir,CtrlSpeed,CtrlBrake);
        RightRear_Ctrl(Dir,CtrlSpeed,CtrlBrake);

//			printf("��ǰ���ţ�%d,��ǰɲ����%d,�Һ����ţ�%d,�Һ�ɲ����%d,RunSta:%d,TargetBrakeVal:%d,Dir:%d,Speed:%d,Brake:%d \r\n",
//               TIM1->CCR2,TIM3->CCR2,TIM1->CCR4,TIM3->CCR4,LowerHost_info.RunSta,LowerHost_info.TargetBrakeVal,Dir,CtrlSpeed,CtrlBrake);
    }
}

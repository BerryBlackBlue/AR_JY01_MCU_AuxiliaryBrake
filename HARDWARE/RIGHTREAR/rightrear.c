#include "pedal.h"
#include "rightrear.h"
#include "leftrear.h"
#include "rightfront.h"
#include "leftfront.h"
#include "usart.h"
#include "key.h"

/*
*********************************************************************
* @  name :Right_Init
* @  func :右后电机接口初始化
* @ prama :无
* @retval :无
*********************************************************************
* @attention :
*********************************************************************
*/
void RightRear_Init(void)
{
    GPIO_InitTypeDef					GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef					TIM_OCInitStructure;
    TIM_BDTRInitTypeDef				TIM_BDTRInitStructure;
    EXTI_InitTypeDef					EXTI_InitStructure;
    NVIC_InitTypeDef					NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

    //右后电机使能（刹车）引脚设置
    GPIO_InitStructure.GPIO_Pin = RR_EL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RR_EL_PORT,&GPIO_InitStructure);

    //右后电机正反引脚设置
    GPIO_InitStructure.GPIO_Pin = RR_ZF_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RR_ZF_PORT,&GPIO_InitStructure);

    //右后电机VR引脚设置
    GPIO_InitStructure.GPIO_Pin = RR_VR_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RR_VR_PORT,&GPIO_InitStructure);

    //右后电机M引脚设置
    GPIO_InitStructure.GPIO_Pin = RR_M_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RR_M_PORT,&GPIO_InitStructure);

    //右后电机M引脚设置为外部触发测速
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12);

    EXTI_InitStructure.EXTI_Line = EXTI_Line12;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel  = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    //右后使能（刹车）引脚复用为TIM3_CH4,10KHz
    TIM_TimeBaseInitStructure.TIM_Prescaler = 71;
    TIM_TimeBaseInitStructure.TIM_Period = 99;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC2Init(TIM3,&TIM_OCInitStructure);
    TIM_OC3Init(TIM3,&TIM_OCInitStructure);
    TIM_OC4Init(TIM3,&TIM_OCInitStructure);

    TIM_Cmd(TIM3,ENABLE);

    //右后VR引脚复用为TIM1_CH4,10KHz
    TIM_TimeBaseInitStructure.TIM_Prescaler = 71;
    TIM_TimeBaseInitStructure.TIM_Period = 99;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = RESET;
    TIM_OCInitStructure.TIM_OCNIdleState = RESET;
    TIM_OC1Init(TIM1,&TIM_OCInitStructure);
    TIM_OC2Init(TIM1,&TIM_OCInitStructure);
    TIM_OC3Init(TIM1,&TIM_OCInitStructure);
    TIM_OC4Init(TIM1,&TIM_OCInitStructure);

    TIM_BDTRInitStructure.TIM_OSSIState = ENABLE;
    TIM_BDTRInitStructure.TIM_OSSRState = ENABLE;
    TIM_BDTRInitStructure.TIM_DeadTime = 0xCD;
    TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
    TIM_BDTRInitStructure.TIM_Break = DISABLE;
    TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
    TIM_BDTRInitStructure.TIM_AutomaticOutput = ENABLE;
    TIM_BDTRConfig(TIM1,&TIM_BDTRInitStructure);

    TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);

    TIM_CtrlPWMOutputs(TIM1,ENABLE);
    TIM_Cmd(TIM1,ENABLE);
}


u16 LR_Count,RR_Count;
void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line12)!=RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line12);

        if(GPIO_ReadOutputDataBit(RR_ZF_PORT,RR_ZF_PIN))
            RR_Count ++;
        else
            RR_Count --;
    }
    if(EXTI_GetITStatus(EXTI_Line13)!=RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line13);

        if(GPIO_ReadOutputDataBit(LR_ZF_PORT,LR_ZF_PIN))
            LR_Count ++;
        else
            LR_Count --;
    }
}

/*
*********************************************************************
* @  name :RightRear_Ctrl
* @  func :控制右后电机
* @ prama :throttle:油门值，符号代表方向；brake:刹车值
* @retval :无
*********************************************************************
* @attention :
*********************************************************************
*/
void RightRear_Ctrl(u8 Dir,u8 throttle,u8 brake)
{
    //油门、刹车值最大限制
    if(throttle>MAX_BRAKE_VAL)
        throttle = MAX_BRAKE_VAL;

    if(brake>MAX_BK)
        brake = MAX_BK;

    if(Dir)
        GPIO_ResetBits(RR_ZF_PORT,RR_ZF_PIN);
    else
        GPIO_SetBits(RR_ZF_PORT,RR_ZF_PIN);

    TIM_SetCompare3(TIM1,throttle);
    TIM_SetCompare4(TIM3,brake);
}




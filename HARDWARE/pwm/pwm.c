#include "pwm.h"
#include "pedal.h"

void TIM1_GPIO_Init(void)
{
    GPIO_InitTypeDef	GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

    /*-----------------------------------------------------
    速度控制GPIO端口定义
    左前：VR_LF -> TIM1_CH1 -> PA.8
    右前：VR_RF -> TIM1_CH2 -> PA.9
    左后：VR_LR -> TIM1_CH3 -> PA.10
    右后：VR_RR -> TIM1_CH4 -> PA.11
    ------------------------------------------------------*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void TIM1_PWM_Init(void)
{
    TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef		TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);

    TIM_TimeBaseInitStructure.TIM_Prescaler = PWM_PSC;
    TIM_TimeBaseInitStructure.TIM_Period = PWM_PERIOD;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    TIM_OCInitStructure.TIM_Pulse = 0x00;

    TIM_OC1Init(TIM1,&TIM_OCInitStructure);
    TIM_OC2Init(TIM1,&TIM_OCInitStructure);
    TIM_OC3Init(TIM1,&TIM_OCInitStructure);
    TIM_OC4Init(TIM1,&TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);

    TIM_CtrlPWMOutputs(TIM1,ENABLE);
    TIM_Cmd(TIM1,ENABLE);
}

void TIM1_Init(void)
{
    TIM1_GPIO_Init();
    TIM1_PWM_Init();
}


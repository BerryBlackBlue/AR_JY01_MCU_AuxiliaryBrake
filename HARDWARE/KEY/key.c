#include "key.h"
#include "delay.h"
#include "led.h"

/**
*********************************************************************
* @brief :按键初始化函数
* @func :初始化DIR引脚
* @prama :无
* @retval :无
********************************************************************
* @attention :
*********************************************************************
*/
void Key_Init(void)
{
    GPIO_InitTypeDef	GPIO_InitStructure;
    EXTI_InitTypeDef	EXTI_InitStructure;
    NVIC_InitTypeDef	NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6);

    EXTI_InitStructure.EXTI_Line = EXTI_Line6;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

u8 Back_Flag;
void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line6)!=RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line6);

        if(DIR==0)
            Back_Flag = 1;
        else
            Back_Flag = 0;
    }
}

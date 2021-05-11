#include "led.h"


void LED_Init(void)
{
    GPIO_InitTypeDef	GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

    PWR_BackupAccessCmd( ENABLE );/* 允许修改RTC和后备寄存器*/
    RCC_LSEConfig( RCC_LSE_OFF ); /* 关闭外部低速时钟,PC14+PC15可以用作普通IO*/
    BKP_TamperPinCmd(DISABLE);  /* 关闭入侵检测功能,PC13可以用作普通IO*/

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    PWR_BackupAccessCmd(DISABLE);/* 禁止修改RTC和后备寄存器*/

    GPIO_SetBits(GPIOC,GPIO_Pin_13);
}

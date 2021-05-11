#include "led.h"


void LED_Init(void)
{
    GPIO_InitTypeDef	GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

    PWR_BackupAccessCmd( ENABLE );/* �����޸�RTC�ͺ󱸼Ĵ���*/
    RCC_LSEConfig( RCC_LSE_OFF ); /* �ر��ⲿ����ʱ��,PC14+PC15����������ͨIO*/
    BKP_TamperPinCmd(DISABLE);  /* �ر����ּ�⹦��,PC13����������ͨIO*/

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    PWR_BackupAccessCmd(DISABLE);/* ��ֹ�޸�RTC�ͺ󱸼Ĵ���*/

    GPIO_SetBits(GPIOC,GPIO_Pin_13);
}

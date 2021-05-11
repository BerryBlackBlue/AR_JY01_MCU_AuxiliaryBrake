#include "leftfront.h"
#include "rightrear.h"
#include "key.h"

/*
*********************************************************************
* @  name :LeftFront_Init
* @  func :������ӿڳ�ʼ��
* @ prama :��
* @retval :��
*********************************************************************
* @attention :
*********************************************************************
*/
void LeftFront_Init(void)
{
    GPIO_InitTypeDef			GPIO_InitStructure;
    EXTI_InitTypeDef			EXTI_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);

    //��ǰ���ʹ�ܣ�ɲ������������
    GPIO_InitStructure.GPIO_Pin = LF_EL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LF_EL_PORT,&GPIO_InitStructure);

    //��ǰ���������������
    GPIO_InitStructure.GPIO_Pin = LF_ZF_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LF_ZF_PORT,&GPIO_InitStructure);

    //��ǰ���VR��������
    GPIO_InitStructure.GPIO_Pin = LF_VR_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LF_VR_PORT,&GPIO_InitStructure);

    //��ǰ���M��������
    GPIO_InitStructure.GPIO_Pin = LF_M_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LF_M_PORT,&GPIO_InitStructure);

    //��ǰ���M��������Ϊ�ⲿ��������
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10);

    EXTI_InitStructure.EXTI_Line = EXTI_Line10;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}


/*
*********************************************************************
* @  name :LeftFront_Ctrl
* @  func :������ǰ���
* @ prama :Dir-����[0-��ת,1-��ת]��throttle:����ֵ�����Ŵ�����brake:ɲ��ֵ
* @retval :��
*********************************************************************
* @attention :
*********************************************************************
*/
void LeftFront_Ctrl(u8 Dir,u8 throttle,u8 brake)
{

    //���š�ɲ��ֵ�������
    if(throttle>MAX_BRAKE_VAL)
        throttle = MAX_BRAKE_VAL;

    if(brake>MAX_BK)
        brake = MAX_BK;

    if(Dir)
        GPIO_SetBits(LF_ZF_PORT,LF_ZF_PIN);
    else
        GPIO_ResetBits(LF_ZF_PORT,LF_ZF_PIN);
		
    TIM_SetCompare1(TIM1,throttle);
    TIM_SetCompare3(TIM3,brake);
}


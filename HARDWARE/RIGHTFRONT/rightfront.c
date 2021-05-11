#include "rightfront.h"
#include "rightrear.h"
#include "key.h"

/*
*********************************************************************
* @  name :RightFront_Init
* @  func :��ǰ����ӿڳ�ʼ��
* @ prama :��
* @retval :��
*********************************************************************
* @attention :
*********************************************************************
*/
void RightFront_Init(void)
{
    GPIO_InitTypeDef					GPIO_InitStructure;
    EXTI_InitTypeDef					EXTI_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);

    //��ǰ���ʹ�ܣ�ɲ������������
    GPIO_InitStructure.GPIO_Pin = RF_EL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RF_EL_PORT,&GPIO_InitStructure);

    //��ǰ���������������
    GPIO_InitStructure.GPIO_Pin = RF_ZF_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RF_ZF_PORT,&GPIO_InitStructure);

    //��ǰ���VR��������
    GPIO_InitStructure.GPIO_Pin = RF_VR_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RF_VR_PORT,&GPIO_InitStructure);

    //��ǰ���M��������
    GPIO_InitStructure.GPIO_Pin = RF_M_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RF_M_PORT,&GPIO_InitStructure);

    //��ǰ���M��������Ϊ�ⲿ��������
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource11);

    EXTI_InitStructure.EXTI_Line = EXTI_Line11;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}


/*
*********************************************************************
* @  name :RightFront_Ctrl
* @  func :������ǰ���
* @ prama :throttle:����ֵ�����Ŵ�����brake:ɲ��ֵ
* @retval :��
*********************************************************************
* @attention :
*********************************************************************
*/
void RightFront_Ctrl(u8 Dir,u8 throttle,u8 brake)
{
    //���š�ɲ��ֵ�������
    if(throttle>MAX_BRAKE_VAL)
        throttle = MAX_BRAKE_VAL;

    if(brake>MAX_BK)
        brake = MAX_BK;

    //�����������
    if(Dir)
        GPIO_SetBits(RF_ZF_PORT,RF_ZF_PIN);
    else
        GPIO_ResetBits(RF_ZF_PORT,RF_ZF_PIN);
		
    TIM_SetCompare2(TIM1,throttle);
    TIM_SetCompare2(TIM3,brake);
}


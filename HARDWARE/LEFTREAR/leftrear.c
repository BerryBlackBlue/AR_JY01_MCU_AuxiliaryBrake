#include "leftrear.h"
#include "rightrear.h"
#include "key.h"

/*
*********************************************************************
* @  name :Left_Init
* @  func :������ӿڳ�ʼ��
* @ prama :��
* @retval :��
*********************************************************************
* @attention :
*********************************************************************
*/
void LeftRear_Init(void)
{
    GPIO_InitTypeDef			GPIO_InitStructure;
    EXTI_InitTypeDef			EXTI_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

    //�����ʹ�ܣ�ɲ������������
    GPIO_InitStructure.GPIO_Pin = LR_EL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LR_EL_PORT,&GPIO_InitStructure);

    //�����������������
    GPIO_InitStructure.GPIO_Pin = LR_ZF_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LR_ZF_PORT,&GPIO_InitStructure);

    //�����VR��������
    GPIO_InitStructure.GPIO_Pin = LR_VR_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LR_VR_PORT,&GPIO_InitStructure);

    //�����M��������
    GPIO_InitStructure.GPIO_Pin = LR_M_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LR_M_PORT,&GPIO_InitStructure);

    //�����M��������Ϊ�ⲿ��������
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13);

    EXTI_InitStructure.EXTI_Line = EXTI_Line13;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}


/*
*********************************************************************
* @  name :LeftRear_Ctrl
* @  func :���������
* @ prama :throttle:����ֵ�����Ŵ�����brake:ɲ��ֵ
* @retval :��
*********************************************************************
* @attention :
*********************************************************************
*/
void LeftRear_Ctrl(u8 Dir,u8 throttle,u8 brake)
{

    //���š�ɲ��ֵ�������
    if(throttle>MAX_BRAKE_VAL)
        throttle = MAX_BRAKE_VAL;

    if(brake>MAX_BK)
        brake = MAX_BK;

    if(Dir)
        GPIO_SetBits(LR_ZF_PORT,LR_ZF_PIN);
    else
        GPIO_ResetBits(LR_ZF_PORT,LR_ZF_PIN);

    TIM_SetCompare3(TIM1,throttle);
    TIM_SetCompare1(TIM3,brake);
}


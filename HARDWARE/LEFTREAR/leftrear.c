#include "leftrear.h"
#include "rightrear.h"
#include "key.h"

/*
*********************************************************************
* @  name :Left_Init
* @  func :左后电机接口初始化
* @ prama :无
* @retval :无
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

    //左后电机使能（刹车）引脚设置
    GPIO_InitStructure.GPIO_Pin = LR_EL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LR_EL_PORT,&GPIO_InitStructure);

    //左后电机正反引脚设置
    GPIO_InitStructure.GPIO_Pin = LR_ZF_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LR_ZF_PORT,&GPIO_InitStructure);

    //左后电机VR引脚设置
    GPIO_InitStructure.GPIO_Pin = LR_VR_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LR_VR_PORT,&GPIO_InitStructure);

    //左后电机M引脚设置
    GPIO_InitStructure.GPIO_Pin = LR_M_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LR_M_PORT,&GPIO_InitStructure);

    //左后电机M引脚设置为外部触发测速
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
* @  func :控制左后电机
* @ prama :throttle:油门值，符号代表方向；brake:刹车值
* @retval :无
*********************************************************************
* @attention :
*********************************************************************
*/
void LeftRear_Ctrl(u8 Dir,u8 throttle,u8 brake)
{

    //油门、刹车值最大限制
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


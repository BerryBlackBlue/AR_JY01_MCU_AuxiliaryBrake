#include "leftfront.h"
#include "rightrear.h"
#include "key.h"

/*
*********************************************************************
* @  name :LeftFront_Init
* @  func :左后电机接口初始化
* @ prama :无
* @retval :无
*********************************************************************
* @attention :
*********************************************************************
*/
void LeftFront_Init(void)
{
    GPIO_InitTypeDef			GPIO_InitStructure;
    EXTI_InitTypeDef			EXTI_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);

    //左前电机使能（刹车）引脚设置
    GPIO_InitStructure.GPIO_Pin = LF_EL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LF_EL_PORT,&GPIO_InitStructure);

    //左前电机正反引脚设置
    GPIO_InitStructure.GPIO_Pin = LF_ZF_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LF_ZF_PORT,&GPIO_InitStructure);

    //左前电机VR引脚设置
    GPIO_InitStructure.GPIO_Pin = LF_VR_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LF_VR_PORT,&GPIO_InitStructure);

    //左前电机M引脚设置
    GPIO_InitStructure.GPIO_Pin = LF_M_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LF_M_PORT,&GPIO_InitStructure);

    //左前电机M引脚设置为外部触发测速
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
* @  func :控制左前电机
* @ prama :Dir-方向[0-正转,1-反转]；throttle:油门值，符号代表方向；brake:刹车值
* @retval :无
*********************************************************************
* @attention :
*********************************************************************
*/
void LeftFront_Ctrl(u8 Dir,u8 throttle,u8 brake)
{

    //油门、刹车值最大限制
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


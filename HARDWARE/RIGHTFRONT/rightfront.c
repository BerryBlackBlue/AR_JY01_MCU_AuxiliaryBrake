#include "rightfront.h"
#include "rightrear.h"
#include "key.h"

/*
*********************************************************************
* @  name :RightFront_Init
* @  func :右前电机接口初始化
* @ prama :无
* @retval :无
*********************************************************************
* @attention :
*********************************************************************
*/
void RightFront_Init(void)
{
    GPIO_InitTypeDef					GPIO_InitStructure;
    EXTI_InitTypeDef					EXTI_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);

    //右前电机使能（刹车）引脚设置
    GPIO_InitStructure.GPIO_Pin = RF_EL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RF_EL_PORT,&GPIO_InitStructure);

    //右前电机正反引脚设置
    GPIO_InitStructure.GPIO_Pin = RF_ZF_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RF_ZF_PORT,&GPIO_InitStructure);

    //右前电机VR引脚设置
    GPIO_InitStructure.GPIO_Pin = RF_VR_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RF_VR_PORT,&GPIO_InitStructure);

    //右前电机M引脚设置
    GPIO_InitStructure.GPIO_Pin = RF_M_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RF_M_PORT,&GPIO_InitStructure);

    //右前电机M引脚设置为外部触发测速
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
* @  func :控制右前电机
* @ prama :throttle:油门值，符号代表方向；brake:刹车值
* @retval :无
*********************************************************************
* @attention :
*********************************************************************
*/
void RightFront_Ctrl(u8 Dir,u8 throttle,u8 brake)
{
    //油门、刹车值最大限制
    if(throttle>MAX_BRAKE_VAL)
        throttle = MAX_BRAKE_VAL;

    if(brake>MAX_BK)
        brake = MAX_BK;

    //电机方向设置
    if(Dir)
        GPIO_SetBits(RF_ZF_PORT,RF_ZF_PIN);
    else
        GPIO_ResetBits(RF_ZF_PORT,RF_ZF_PIN);
		
    TIM_SetCompare2(TIM1,throttle);
    TIM_SetCompare2(TIM3,brake);
}


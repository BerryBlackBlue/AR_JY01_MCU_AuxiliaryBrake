#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "leftfront.h"
#include "rightfront.h"
#include "rightrear.h"
#include "leftrear.h"
#include "can.h"

int main(void)





{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_Normal);
    delay_init();
    uart_init(115200);

    LED_Init();
    Timer4_Init();
	
    RightFront_Init();		//开启右前电机控制
    RightRear_Init();			//开启右后电机控制

    delay_ms(100);

//    printf("system ok \r\n");

    while(1)
    {
        delay_ms(200);
        MCU_Light = !MCU_Light;
    }
}



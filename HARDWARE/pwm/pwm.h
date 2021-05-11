#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

/*设定TIM1输出频率为10KHz的PWM*/
#define PWM_PSC			71
#define PWM_PERIOD	99

void TIM1_GPIO_Init(void);
void TIM1_PWM_Init(void);
void TIM1_Init(void);

#endif



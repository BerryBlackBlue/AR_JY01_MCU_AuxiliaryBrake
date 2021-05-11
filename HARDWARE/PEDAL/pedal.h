#ifndef	__PEDAL_H
#define __PEDAL_H

#include "sys.h"

#define ADC1_DR_Address	((u32)0x4001244C)

/*������������*/
#define TR_GPIO_PORT	GPIOB
#define TR_GPIO_PIN		GPIO_Pin_0
#define TR_ADC_CH		ADC_Channel_8

/*ɲ����������*/
#define BK_GPIO_PORT	GPIOB
#define BK_GPIO_PIN		GPIO_Pin_1
#define BK_ADC_CH		ADC_Channel_9

/*����������������*/
#define LFIS_GPIO_PORT	GPIOA
#define LFIS_GPIO_PIN	GPIO_Pin_0
#define LFIS_ADC_CH		ADC_Channel_0

#define RFIS_GPIO_PORT	GPIOA
#define RFIS_GPIO_PIN	GPIO_Pin_1
#define RFIS_ADC_CH		ADC_Channel_1

#define LRIS_GPIO_PORT	GPIOA
#define LRIS_GPIO_PIN	GPIO_Pin_2
#define LRIS_ADC_CH		ADC_Channel_2

#define RRIS_GPIO_PORT	GPIOA
#define RRIS_GPIO_PIN	GPIO_Pin_3
#define RRIS_ADC_CH		ADC_Channel_3


/*�����Сֵ��Χ����*/
#define TR_MAX			90
#define TR_MIN			10
#define BK_MAX			90
#define BK_MIN			10

extern u8 TR_Val;
extern u8 BK_Val;
extern u16 LFI_Val;
extern u16 RFI_Val;
extern u16 LRI_Val;
extern u16 RRI_Val;

void Pedal_GPIO_Init(void);
void Pedal_ADC_Init(void);
void Pedal_DMA_Init(void);
void Pedal_Init(void);

#endif


#include "pedal.h"
#include "usart.h"
#include "timer.h"


void Pedal_GPIO_Init(void)
{
    GPIO_InitTypeDef	GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);

    /*GPIO引脚配置
      Throttle -> PB.0
	  Brake    -> PB.1
    */
    GPIO_InitStructure.GPIO_Pin = TR_GPIO_PIN|BK_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    /*GPIO引脚设置
      LFIS -> PA.0
      RFIS -> PA.1
      LRIS -> PA.2
      RRIS -> PA.3
    */
    GPIO_InitStructure.GPIO_Pin = LFIS_GPIO_PIN|RFIS_GPIO_PIN|LRIS_GPIO_PIN|RRIS_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void Pedal_ADC_Init(void)
{
    ADC_InitTypeDef		ADC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_NbrOfChannel = 6;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_Init(ADC1,&ADC_InitStructure);

    ADC_RegularChannelConfig(ADC1,TR_ADC_CH,1,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,BK_ADC_CH,2,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,LFIS_ADC_CH,3,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,RFIS_ADC_CH,4,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,LRIS_ADC_CH,5,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,RRIS_ADC_CH,6,ADC_SampleTime_55Cycles5);

    ADC_DMACmd(ADC1,ENABLE);

    ADC_Cmd(ADC1,ENABLE);

    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));

    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));

    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

u16 ADC_ConvertedValue[6] = {0,0,0,0,0,0};

void Pedal_DMA_Init(void)
{
    DMA_InitTypeDef		DMA_InitStructure;
    NVIC_InitTypeDef	NVIC_InitStrucutre;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

    DMA_DeInit(DMA1_Channel1);

    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&(ADC1->DR);
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32) &ADC_ConvertedValue;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_BufferSize = 6;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1,&DMA_InitStructure);

    NVIC_InitStrucutre.NVIC_IRQChannel = DMA1_Channel1_IRQn;
    NVIC_InitStrucutre.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStrucutre.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStrucutre.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStrucutre);

    DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);

    DMA_ClearITPendingBit(DMA1_IT_TC1);

    DMA_Cmd(DMA1_Channel1,ENABLE);
}


void Pedal_Init(void)
{
    Pedal_GPIO_Init();
    Pedal_DMA_Init();
    Pedal_ADC_Init();
}

u8 TR_Val;
u8 BK_Val;
u16 LFI_Val;
u16 RFI_Val;
u16 LRI_Val;
u16 RRI_Val;

void DMA1_Channel1_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC1)!=RESET)
    {
        DMA_ClearITPendingBit(DMA1_IT_TC1);

        TR_Val = ADC_ConvertedValue[0]*100/4096;

        if(TR_Val<=TR_MIN)
            TR_Val = 0;
        else if(TR_Val>=TR_MAX)
            TR_Val = TR_MAX-TR_MIN;
        else
            TR_Val = (TR_Val-TR_MIN);

        BK_Val = ADC_ConvertedValue[1]*100/4096;

        if(BK_Val<=BK_MIN)
            BK_Val = 0;
        else if(BK_Val>=BK_MAX)
            BK_Val = BK_MAX-BK_MIN;
        else
            BK_Val = BK_Val-BK_MIN;
//		printf("油门值：%d, 刹车值：%d \r\n",ADC_ConvertedValue[0],BK_Val);
    }
}


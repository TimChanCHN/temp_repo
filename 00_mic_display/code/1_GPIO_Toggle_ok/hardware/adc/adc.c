#include "adc.h"
#include "hk32f030m.h"

void adc1_init(void)
{
    // 1. 设置PD2为ADC input
	GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_2 ;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_7);

    // 2. 初始化ADC
    ADC_InitTypeDef ADC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC ,ENABLE);

	ADC_DeInit(ADC1);
	ADC_StructInit(&ADC_InitStructure);
	
    ADC_InitStructure.ADC_ContinuousConvMode    = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv      = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign             = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ScanDirection         = ADC_ScanDirection_Upward;
    ADC_Init(ADC1,&ADC_InitStructure);

    /* ADC1 regular channels configuration */ 
    ADC_ChannelConfig(ADC1, ADC_Channel_4 , ADC_SampleTime_239_5Cycles);
    ADC_GetCalibrationFactor(ADC1);

    /* Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE);

	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY)); 
	ADC_StartOfConversion(ADC1);
}

void adc1_enable(void)
{
    ADC_Cmd(ADC1, ENABLE);
}

void adc1_disable(void)
{
    ADC_Cmd(ADC1, DISABLE);
}

void adc1_value_get(uint16_t *p_value)
{
    ADC_ChannelConfig(ADC1, ADC_Channel_4, ADC_SampleTime_239_5Cycles);

    /**
     * 启动转换
     */
    ADC_StartOfConversion(ADC1);

    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

    *p_value = ADC_GetConversionValue(ADC1);
}



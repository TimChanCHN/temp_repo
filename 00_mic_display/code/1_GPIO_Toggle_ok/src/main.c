#include "digital_tube.h"
#include "tim.h"
#include "delay.h"
#include "trace.h"
#include "usart.h"
#include "adc.h"

int main(void)
{
	digital_tube_pin_init();
	TIM_Config();
	trace_init();
	adc1_init();

	uint32_t ADCConvertedValue, ADCConvertedVoltage;
	
	trace_info("hello world!\r\n");

	while (1)
	{
		ADCConvertedValue = ADC_GetConversionValue(ADC1);
		ADCConvertedVoltage = (ADCConvertedValue * 3300)/4095;	
		ADCConvertedVoltage = ADCConvertedVoltage*411/323;			
		trace_info("ADC_DR register of CH4 : 0x%04X \r\n", ADCConvertedValue);
		trace_info("ADC_V of CH4 : %d mV\r\n", ADCConvertedVoltage);
		trace_info("\r\n");

		delayms(2000);
		softWareDelay();
	}
}




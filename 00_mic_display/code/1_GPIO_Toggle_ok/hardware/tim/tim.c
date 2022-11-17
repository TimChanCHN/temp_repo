#include "tim.h"
#include "hk32f030m.h"

/*TIMER配置*/
void TIM_Config(void)
{
	uint16_t prescaler_value = 0;

	// 配置1M时钟，分频系数32-1
    prescaler_value = (SystemCoreClock / 1000000) - 1;

    TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
    NVIC_InitTypeDef            NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel         = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_TimeBaseStructure.TIM_Period        = 1000;					// 计数1000下，触发定时器中断
    TIM_TimeBaseStructure.TIM_Prescaler     = prescaler_value;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	// TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);

    TIM_Cmd(TIM2, ENABLE);
}

// 1ms中断
void TIM2_IRQHandler(void)
{
	static uint16_t i = 0;

    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

		i++;

		if (i == 1000)
		{
			i = 0;
			GPIOA->ODR ^= GPIO_Pin_1;
		}
    }
}


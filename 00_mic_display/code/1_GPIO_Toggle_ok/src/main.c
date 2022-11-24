#include "digital_tube.h"
#include "tim.h"
#include "delay.h"
#include "trace.h"
#include "usart.h"
#include "adc.h"

#define LEVEL_0			0
#define LEVEL_1			1
#define LEVEL_2			2
#define LEVEL_3			3

uint8_t g_tube_status = 0;
typedef void (*p_fun)(void);
p_fun func_light_ctrl[4];
uint16_t vbat = 0;

void get_adc_value_ave(void)
{
	uint16_t value[5] = {0};
	uint16_t i = 0;
	uint16_t sum = 0;

	for (i = 0; i < 5; i++)
	{
		adc1_enable();
		adc1_value_get(&value[i]);
		adc1_disable();
		sum += value[i];
	}

	// TODO: 电阻分压比例估计需要再调
	vbat = sum / 5;
	vbat = (vbat * 3300)/4095;
	vbat = (vbat * 42)/33;
	trace_info("sum = %d, vbat = %d mv\r\n", sum, vbat);
}

// 4.2V满格
// 3.9V两格
// 3.7V一格
void run_display_digital(void)
{
	uint8_t voltage_level;
	// vbat = 3600;				// for debug

	if (vbat < 3700)
	{
		voltage_level = LEVEL_0;
	}
	else if (vbat < 3900)
	{
		voltage_level = LEVEL_1;
	}
	else if (vbat < 4200)
	{
		voltage_level = LEVEL_2;
	}
	else		
	{
		voltage_level = LEVEL_3;
	}

	if (g_tube_status == 3)
	{
		g_tube_status = voltage_level-1;
	}
	g_tube_status++;
}

void init_display_digital(void)
{
	// vbat = 3600;				// for debug

	if (vbat < 3700)
	{
		g_tube_status = 0;
	}
	else if (vbat < 3900)
	{
		g_tube_status = 1;
	}
	else if (vbat < 4200)
	{
		g_tube_status = 2;
	}
	else		
	{
		g_tube_status = 3;
	}
}


int main(void)
{
	uint8_t cnt = 0;

	func_light_ctrl[0] = display_boader;
	func_light_ctrl[1] = display_battery1;
	func_light_ctrl[2] = display_battery2;
	func_light_ctrl[3] = display_battery3;

	digital_tube_pin_init();
	TIM_Config();
	trace_init();
	adc1_init();

	trace_info("hello world!\r\n");

	get_adc_value_ave();
	init_display_digital();

	while (1)
	{
		if (get_swtimer_value() == 1)
		{
			clear_swtimer();
			run_display_digital();
			
			cnt++;
			trace_info("cnt = %d\r\n", cnt);
			trace_info("\r\n");

			if (cnt == 10)
			{
				cnt = 0;
				get_adc_value_ave();
			}
		}

		func_light_ctrl[g_tube_status]();
	}
}


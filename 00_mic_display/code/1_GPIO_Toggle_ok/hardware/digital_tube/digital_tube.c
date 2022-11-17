#include "digital_tube.h"
#include "hk32f030m_gpio.h"
#include "hk32f030m.h"

void digital_tube_pin_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIOA->ODR |= (1 << 1);
	GPIOA->ODR &= ~(1 << 2);
}

#define LOW_LEVEL       0
#define HIGH_LEVEL      1

void turn_on_light(uint16_t pin_low, uint16_t pin_high)
{
    #if 0
    gpio_cfg_t *p_gpio_cfg = &g_dig_tube_obj.gpio_cfg;

    uint32_t input_pin = 0xFF & (~(pin_low | pin_high));
    uint32_t output_pin = (pin_low | pin_high);

    p_gpio_cfg->gpio_pin = input_pin;
    p_gpio_cfg->gpio_dir = GPIO_DIR_INPUT;
    p_gpio_cfg->mode     = GPIO_Mode_IPD;
    g_dig_tube_obj.gpio_ops.gpio_init(&g_dig_tube_obj.gpio_cfg);

    p_gpio_cfg->gpio_pin = output_pin;
    p_gpio_cfg->gpio_dir = GPIO_DIR_OUTPUR;
    g_dig_tube_obj.gpio_ops.gpio_init(&g_dig_tube_obj.gpio_cfg);

    p_gpio_cfg->gpio_pin = pin_low ;
    g_dig_tube_obj.gpio_ops.gpio_output_set(&g_dig_tube_obj.gpio_cfg, LOW_LEVEL);

    p_gpio_cfg->gpio_pin = pin_high;
    g_dig_tube_obj.gpio_ops.gpio_output_set(&g_dig_tube_obj.gpio_cfg, HIGH_LEVEL);

    g_systick_obj.systick_ops.delay_ms(1);
    p_gpio_cfg->gpio_pin = pin_high;
    g_dig_tube_obj.gpio_ops.gpio_output_set(&g_dig_tube_obj.gpio_cfg, LOW_LEVEL);
    #endif
}

void display_boader(void)
{
    // 边框
    turn_on_light(DIGITAL_PIN3, DIGITAL_PIN7);        // J1
    turn_on_light(DIGITAL_PIN6, DIGITAL_PIN1|DIGITAL_PIN3);        // J2/J3
    // turn_on_light(DIGITAL_PIN6, DIGITAL_PIN3);        // J3
    turn_on_light(DIGITAL_PIN7, DIGITAL_PIN3);        // J4

    // turn_on_light(DIGITAL_PIN5, DIGITAL_PIN1);        // K2
    // turn_on_light(DIGITAL_PIN2, DIGITAL_PIN6);        // K3
    // turn_on_light(DIGITAL_PIN2, DIGITAL_PIN7);        // K4
}

void display_battery1(void)
{
    display_boader();

    turn_on_light(DIGITAL_PIN7, DIGITAL_PIN4);        // K8
}

void display_battery2(void)
{
    display_boader();

    turn_on_light(DIGITAL_PIN7, DIGITAL_PIN4 | DIGITAL_PIN2);        // K8
    // turn_on_light(DIGITAL_PIN7, DIGITAL_PIN2);        // K7
}

void display_battery3(void)
{
    display_boader();

    turn_on_light(DIGITAL_PIN7, DIGITAL_PIN4|DIGITAL_PIN2|DIGITAL_PIN1);        // K8
    // turn_on_light(DIGITAL_PIN7, DIGITAL_PIN2);        // K7
    // turn_on_light(DIGITAL_PIN7, DIGITAL_PIN1);        // K6
}

// update in main.c
TIMER_DEF(m_test_timer);
uint8_t g_tube_status = 0;
typedef void (*p_fun)(void);
p_fun func_light_ctrl[4];
uint16_t adc_value[6] = {0};


void test_timer_handler(void *p_data)
{
	uint8_t vbat = 1;
	uint8_t voltage_level;

	if (vbat < 2)
	{
		voltage_level = LEVEL_0;
	}
	else if (vbat < 3)
	{
		voltage_level = LEVEL_1;
	}
	else if (vbat < 4)
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

	// func_light_ctrl[0] = display_boader;
	// func_light_ctrl[1] = display_battery1;
	// func_light_ctrl[2] = display_battery2;
	// func_light_ctrl[3] = display_battery3;

	func_light_ctrl[g_tube_status](); 
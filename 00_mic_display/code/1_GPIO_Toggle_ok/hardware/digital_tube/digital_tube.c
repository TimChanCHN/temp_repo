#include "digital_tube.h"
#include "hk32f030m_gpio.h"
#include "hk32f030m.h"
#include "sys.h"
#include "delay.h"

#include "trace.h"

// 数码管管脚图:
// 		PA1, PA2, PC3, PC4, PC5, PC6, PC7
void digital_tube_pin_init(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
}

uint8_t get_bitorder(uint16_t num)
{
	uint8_t i = 0;

	while (num)
	{
		num = num >> 1;
		i++;
	}
	i--;

	return i;
}

void set_gpio_value(GPIO_TypeDef *gpio_port , uint32_t gpio_pin ,uint8_t value)
{
	#if 0
    if(value)
    {
        gpio_port->BSRR = gpio_pin;
    }
    else
    {
        gpio_port->BRR = gpio_pin;
    }
	#else 
    if(value)
    {
        gpio_port->ODR |= (1 << get_bitorder(gpio_pin));
    }
    else
    {
        gpio_port->ODR &= ~(1 << get_bitorder(gpio_pin));
    }
	#endif
}

// PIN1-->PC7
// PIN2-->PC6
// PIN3-->PC5
// PIN4-->PC4
// PIN5-->PC3
// PIN6-->PA2
// PIN7-->PA1
void turn_on_light(uint16_t pin_low, uint16_t pin_high)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	uint32_t output_pin_portA 	= 0;
	uint32_t output_pin_portC 	= 0;
	uint16_t pin = pin_low | pin_high;

	// 1. set var value
	output_pin_portA	= pin & 0x06;
	output_pin_portC	= pin & 0xF8;

	// 2. GPIO init
	GPIO_DeInit(GPIOA);
	GPIO_DeInit(GPIOC);

	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin 	= output_pin_portA;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin 	= output_pin_portC;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	// 3. set output
	if (pin == 0x06)
	{
		set_gpio_value(GPIOA, pin_low, 0);
		set_gpio_value(GPIOA, pin_high, 1);
		delayus(200);
		set_gpio_value(GPIOA, pin_high, 0);
		delayus(200);
	}
	else if ((pin & 0x06) == 0)
	{
		set_gpio_value(GPIOC, pin_low, 0);
		set_gpio_value(GPIOC, pin_high, 1);
		delayus(200);
		set_gpio_value(GPIOC, pin_high, 0);
		delayus(200);
	}
	else if ((pin_low == 0x02) || (pin_low == 0x04))		
	{
		set_gpio_value(GPIOA, pin_low, 0);
		set_gpio_value(GPIOC, pin_high, 1);
		delayus(200);
		set_gpio_value(GPIOC, pin_high, 0);
		delayus(200);
	}
	else if ((pin_high == 0x02) || (pin_high == 0x04))		
	{
		set_gpio_value(GPIOC, pin_low, 0);
		set_gpio_value(GPIOA, pin_high, 1);
		delayus(200);
		set_gpio_value(GPIOA, pin_high, 0);
		delayus(200);
	}
}

void display_boader(void)
{
	turn_on_light(DIGITAL_PIN3, DIGITAL_PIN7);			// J1
	turn_on_light(DIGITAL_PIN6, DIGITAL_PIN1);			// J2
	turn_on_light(DIGITAL_PIN6, DIGITAL_PIN3);			// J3
	turn_on_light(DIGITAL_PIN7, DIGITAL_PIN3);        	// J4
}

void display_battery1(void)
{
    display_boader();

    turn_on_light(DIGITAL_PIN7, DIGITAL_PIN4);        // K8
}

void display_battery2(void)
{
    display_boader();

    turn_on_light(DIGITAL_PIN7, DIGITAL_PIN4);        // K8
    turn_on_light(DIGITAL_PIN7, DIGITAL_PIN2);        // K7
}

void display_battery3(void)
{
    display_boader();

    turn_on_light(DIGITAL_PIN7, DIGITAL_PIN4);        // K8
    turn_on_light(DIGITAL_PIN7, DIGITAL_PIN2);        // K7
    turn_on_light(DIGITAL_PIN7, DIGITAL_PIN1);        // K6
}



#ifndef __DIGITAL_TUBE_H
#define __DIGITAL_TUBE_H

#include "hk32f030m.h"

#define DIGITAL_PIN1                             GPIO_Pin_7
#define DIGITAL_PIN2                             GPIO_Pin_6
#define DIGITAL_PIN3                             GPIO_Pin_5
#define DIGITAL_PIN4                             GPIO_Pin_4
#define DIGITAL_PIN5                             GPIO_Pin_3
#define DIGITAL_PIN6                             GPIO_Pin_2
#define DIGITAL_PIN7                             GPIO_Pin_1

void digital_tube_pin_init(void);
void turn_on_light(uint16_t pin_low, uint16_t pin_high);
void display_boader(void);
void display_battery1(void);
void display_battery2(void);
void display_battery3(void);


#endif

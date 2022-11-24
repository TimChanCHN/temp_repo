#ifndef __TIM_H
#define __TIM_H

#include "hk32f030m.h"

void TIM_Config(void);
void set_swtimer(uint8_t value);
uint8_t get_swtimer_value(void);
void clear_swtimer(void);

#endif


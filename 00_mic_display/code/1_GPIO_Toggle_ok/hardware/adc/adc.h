#ifndef __ADC_H
#define __ADC_H

#include "hk32f030m.h"

void adc1_init(void);
void adc1_disable(void);
void adc1_enable(void);
void adc1_value_get(uint16_t *p_value);

#endif

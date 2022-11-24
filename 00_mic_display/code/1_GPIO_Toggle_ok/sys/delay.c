#include "delay.h"

void delayus(uint32_t i)
{
	i*=5;					//1US
	while(i--);
} 

void delayms(uint32_t i)
{
  delayus(740*i);			//740
}

void softWareDelay(void)
{
	uint16_t i;
	uint16_t j;
	
	for(i=0;i<500;i++)
	{
		for(j=0;j<1000;j++)
		{
			__NOP();
		}
	}
}

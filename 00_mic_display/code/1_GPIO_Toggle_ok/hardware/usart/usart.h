#ifndef __USART_H
#define __USART_H

#include "hk32f030m.h"
#include "hk32f030m_gpio.h"
#include "hk32f030m_usart.h"
	
#define  USART1_TX_PORT         GPIOD
#define  USART1_TX_PIN          GPIO_Pin_1
	
#define  USART1_RX_PORT         GPIOD
#define  USART1_RX_PIN          GPIO_Pin_6

void usart_configure(void);
void USART_SendByte(uint8_t ch);
void USART_SendStringLen(uint8_t *p,uint16_t len);


#endif


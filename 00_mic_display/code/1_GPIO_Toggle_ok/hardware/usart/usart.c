#include "usart.h"

void usart_configure(void)
{
    // 1. config GPIO, PD1--TX, PD6--RX
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin     = USART1_TX_PIN;
	GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(USART1_TX_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(USART1_TX_PORT,GPIO_PinSource1,GPIO_AF_1);
	
	GPIO_InitStructure.GPIO_Pin     = USART1_RX_PIN;
	GPIO_Init(USART1_RX_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(USART1_RX_PORT,GPIO_PinSource6,GPIO_AF_1);

    // 2. config usart
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    USART_InitTypeDef USART_InitStruct;

	USART_InitStruct.USART_BaudRate             = 115200;
	USART_InitStruct.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity               = USART_Parity_No;
	USART_InitStruct.USART_StopBits             = USART_StopBits_1;
	USART_InitStruct.USART_WordLength           = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStruct);
	USART_Cmd(USART1, ENABLE);
	
	// USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	// USART_NVIC_Configurature();
}

void USART_SendByte(uint8_t ch)
{
	while((USART1->ISR & USART_ISR_TXE) == 0);
	USART1->TDR = ch;
}

void USART_SendStringLen(uint8_t *p,uint16_t len)
{
	while(len--)
	{
		USART_SendByte(*(p++));
	}
}

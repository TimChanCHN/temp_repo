#include "hk32f030m.h"

// //IO口操作宏定义
// #define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
// #define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
// #define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

// //IO口地址映射
// #define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x48000000 
// #define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40010C0C 
// #define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x4001100C 
// #define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x4001140C 
// #define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x4001180C 
// #define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40011A0C    
// #define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40011E0C    

// //IO口操作,只对单一的IO口!
// //确保n的值小于16!
// #define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 

// #define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 

typedef struct
{
    uint16_t bit0 : 1;
    uint16_t bit1 : 1;
    uint16_t bit2 : 1;
    uint16_t bit3 : 1;
    uint16_t bit4 : 1;
    uint16_t bit5 : 1;
    uint16_t bit6 : 1;
    uint16_t bit7 : 1;
    uint16_t bit8 : 1;
    uint16_t bit9 : 1;
    uint16_t bit10 : 1;
    uint16_t bit11 : 1;
    uint16_t bit12 : 1;
    uint16_t bit13 : 1;
    uint16_t bit14 : 1;
    uint16_t bit15 : 1;
} Bits16_TypeDef;

#define PAout(n)  ( ((Bits16_TypeDef *)(&(GPIOA->ODR)))->bit##n )
#define PBout(n)  ( ((Bits16_TypeDef *)(&(GPIOB->ODR)))->bit##n )
#define PCout(n)  ( ((Bits16_TypeDef *)(&(GPIOC->ODR)))->bit##n )
#define PDout(n)  ( ((Bits16_TypeDef *)(&(GPIOD->ODR)))->bit##n )
#define PEout(n)  ( ((Bits16_TypeDef *)(&(GPIOE->ODR)))->bit##n )
#define PFout(n)  ( ((Bits16_TypeDef *)(&(GPIOF->ODR)))->bit##n )

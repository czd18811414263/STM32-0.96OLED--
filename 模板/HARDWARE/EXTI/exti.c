#include "exti.h"
#include "led.h"
#include "beep.h"
#include "delay.h"
#include "usart.h"
#include "key.h"
#include "sys.h"

void EXTIx_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	KEY_Init();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	/*GPIOE.2 KEY2*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line2;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	/*GPIOE.3 KEY0*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);
	EXTI_InitStruct.EXTI_Line=EXTI_Line3;
	EXTI_Init(&EXTI_InitStruct);
	
	/*GPIOE.4 KEY1*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);
	EXTI_InitStruct.EXTI_Line=EXTI_Line4;
	EXTI_Init(&EXTI_InitStruct);
	
	/*GPIOA.0 WK_UP*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_Line=EXTI_Line0;
	EXTI_Init(&EXTI_InitStruct);
	
	/*NVIC中断初始化*/
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x02;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x03;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x02;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x02;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x02;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x01;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x02;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x00;
	NVIC_Init(&NVIC_InitStruct);
}
 /*中断服务函数*/
void EXTI0_IRQHandler(void)
{
	delay_ms(10);
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)/*WK_UP*/
	{
		BEEP=!BEEP;
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler(void)
{
	delay_ms(10);
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)/*WK_UP*/
	{
		BEEP=!BEEP;
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}
void EXTI2_IRQHandler(void)
{
	delay_ms(10);
	if(KEY2==0)
	{
		LED0=!LED0;
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
}

void EXTI3_IRQHandler(void)
{
	delay_ms(10);
	if(KEY1==0)
	{
		LED1=!LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
}

void EXTI4_IRQHandler(void)
{
	delay_ms(10);
	if(KEY0==0)
	{
		LED0=!LED0;
		LED1=!LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}


#include "iwdg.h"
#include "stm32f10x.h"
#include "sys.h"
#include "led.h"
#include "delay.h"
//初始化独立看门狗
//prer:分频数:0~7(只有低3位有效!)
//分频因子=4*2^prer.但最大值只能是256!
//rlr:重装载寄存器值:低11位有效.
//时间计算(大概):Tout=((4*2^prer)*rlr)/40 (ms).
void IWDG_Init(u8 prer,u16 rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(prer);
	IWDG_SetReload(rlr);
	IWDG_ReloadCounter();
	IWDG_Enable();
}


void IWDG_Feed(void)
{
	IWDG_ReloadCounter();
}	

//保存WWDG计数器的设置值,默认为最大. 
u8 WWDG_CNT=0x7f; 
//初始化窗口看门狗 	
//tr   :T[6:0],计数器值 
//wr   :W[6:0],窗口值 
//fprer:分频系数（WDGTB）,仅最低2位有效 
//Fwwdg=PCLK1/(4096*2^fprer). 
void WWDG_Init(u8 tr, u8 wr, u32 fprer)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	WWDG_CNT = WWDG_CNT&tr;
	WWDG_SetPrescaler(fprer);
	WWDG_SetWindowValue(wr);
	WWDG_Enable(WWDG_CNT);
	WWDG_ClearFlag();
	WWDG_NVIC_Init();
	WWDG_EnableIT();
}

void WWDG_Set_Counter(u8 cnt)
{
	WWDG_Enable(cnt);
}

void WWDG_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel=WWDG_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	
	NVIC_Init(&NVIC_InitStruct);
}

void WWDG_IRQHandler(void)
{
	WWDG_Set_Counter(WWDG_CNT);
	WWDG_ClearFlag();
	LED1=!LED1;
}


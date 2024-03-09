#include "timer.h"
#include "led.h"
/*计时器中断*/
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn ;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);

	TIM_Cmd(TIM3, ENABLE);
}

void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		LED1=!LED1;
	}
	
}

void TIM3_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM2;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC2Init(TIM3, &TIM_OCInitStruct);
	
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM3, ENABLE);
}


void TIM5_Cap_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStruct);
	
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICFilter=0x00;
	TIM_ICInit(TIM5, &TIM_ICInitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=TIM5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_ITConfig(TIM5, TIM_IT_Update | TIM_IT_CC1, ENABLE);
	
	TIM_Cmd(TIM5, ENABLE);
}

/*输入捕获专用变量*/
u8 TIM5CH1_CAPTURE_STA=0;//****输入捕获状态
u16 TIM5CH1_CAPTURE_VAL;//****输入捕获值

//输入捕获中断函数
void TIM5_IRQHandler(void)
{
	if((TIM5CH1_CAPTURE_STA&0x80)==0)//未捕获
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update)!=RESET)
		{
			if(TIM5CH1_CAPTURE_STA&0x40)//捕获到高电平
			{
				if((TIM5CH1_CAPTURE_STA&0x3F)==0x3F)//高电平过长
				{
					TIM5CH1_CAPTURE_STA|=0x80;//标记成功捕获一次
					TIM5CH1_CAPTURE_VAL=0xFFFF;
				}
				else TIM5CH1_CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC1)!=RESET)//捕获CC1发生捕获事件
		{
			if(TIM5CH1_CAPTURE_STA&0x40)//捕获到下降沿
			{
				TIM5CH1_CAPTURE_STA|=0x80;
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
				TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Falling);
			}
		}
	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update | TIM_IT_CC1);
}




#include "exti.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "beep.h"
#include "usart.h"
#include "iwdg.h"
#include "timer.h"
#include "oled.h"
#include "bmp.h"
#include "rtc.h"
//#include "usmart.h"
 int main(void)
 {	
 	u8 t=0;	
//	u8 i=0;
//	u8 n=0;
//	u8 d=0;
//	unsigned cmdn=1;
//	unsigned datn=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	OLED_Init();
	OLED_Clear(0);	 
	//usmart_dev.init(SystemCoreClock/1000000);	//��ʼ��USMART	
	RTC_Init();	  			//RTC��ʼ��
	//OLED_ShowString(16,2,"year",16);	
	OLED_ShowCHinese(40,2,0);//��
	OLED_ShowCHinese(70,2,1);//��
	OLED_ShowCHinese(112,2,2);//��
	OLED_ShowString(22,4,":",16);
	OLED_ShowString(48,4,":",16);
	while(1) 
	{		
		if(t!=calendar.sec)
		{
//			OLED_Clear(0);
			t=calendar.sec;
			//OLED_ShowNum(6, 0, t, 2, 16);
			OLED_ShowNum(6,2,calendar.w_year,4,16);
			//OLED_ShowString(40,2,"year",16);
//			OLED_ShowCHinese(40,2,0);//��
			OLED_ShowNum(54,2,calendar.w_month,2,16);	
//			OLED_ShowCHinese(70,2,1);//��
			OLED_ShowNum(86,2,calendar.w_date,2,16);
//			OLED_ShowCHinese(112,2,2);//��
			switch(calendar.week)
			{
				case 0:
					OLED_ShowString(30,0,"sunday",16);
					break;
				case 1:
					OLED_ShowString(30,0,"Monday",16);
					break;
				case 2:
					OLED_ShowString(30,0,"Tuesday",16);
					break;
				case 3:
					OLED_ShowString(30,0,"Wednesday",16);
					break;
				case 4:
					OLED_ShowString(30,0,"Thursday",16);
					break;
				case 5:
					OLED_ShowString(30,0,"Friday",16);
					break;
				case 6:
					OLED_ShowString(30,0,"Saturday",16);
					break;  
			}
			OLED_ShowNum(6,4,calendar.hour,2,16);
//			OLED_ShowString(22,4,":",16);
			
			OLED_ShowNum(30,4,calendar.min,2,16);
//			OLED_ShowString(48,4,":",16);
			
			OLED_ShowNum(56,4,calendar.sec,2,16);
			
/*����ģ�飬������oled.h��*/
//			if(i<100)
//			{
//			for(d=0;d<2;d++)
//			{
//				OLED_WR_Byte (0xb6+d,OLED_CMD);    //����ҳ��ַ��0~7��
//				OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
//				OLED_WR_Byte (0x10,OLED_CMD);
//				for(n=0;n<128;n++)OLED_WR_Byte(datn,cmdn); 
//			}//��ˢ�»���ģ������ҳ
//			
//			/*-------����ģ��-----------*/
//			OLED_ShowCHinese(6*i+6,6,3);//����ʵ��ģ��
//			OLED_ShowCHinese(6*i+24,6,4);//����ʵ��ģ��
//			OLED_ShowCHinese(6*i+42,6,5);
//			OLED_ShowCHinese(6*i+60,6,6);
//			/*--------------------------*/
//			i++;
//			
//			}
//			else i=0;
			
			OLED_Roll(0, 15, 3);
			
//			LED0=!LED0;
		}	
		delay_ms(10);								  
		}
	};



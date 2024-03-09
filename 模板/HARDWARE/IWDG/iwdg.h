#ifndef __IWDG_H
#define __IWDG_H
#include "sys.h"

void IWDG_Init(u8 prer, u16 rlr);
void IWDG_Feed(void);

void WWDG_Init(u8 tr, u8 wr, u32 fprer);
void WWDG_Set_Counter(u8 cnt);
void WWDG_NVIC_Init(void);
//void WWDG_IRQHandler(void);

#endif


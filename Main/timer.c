#include "Main/timer.h"
void timeroz(void) {
	if (timer_update) {
		timer_update = 0;
		if (++ledtime > 250) {
			ledtime = 0;
//			GPIO_ToggleBits(GPIOD,GPIO_Pin_12);
			if ((((GPIOD->ODR) & (1 << 12)) - (1 << 12)) == 0) {
				GPIOD->ODR &= ~0b00000000000000000001000000000000; //0b11111111111111111110111111111111; //0b00000000000000000001000000000000;
			} else
				GPIOD->ODR |= 0b00000000000000000001000000000000;
		}
	}

//	ODR 	= 01000100;
//	yeni	= 00000100;
//
//	ODR 	~ 11111011;
//	ODR		= 01000000; <= (01000100 & 11111011);
//
//
//	ODR	  &=~ 00000000;
//	//hangi bit 0 olacaksa 1 yap�lmas� laz�m
//
//	ODR		| 00000110;
}


void init_tim7(void) {
	TIM_TimeBaseInitTypeDef TIM_TBInitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM7EN, ENABLE); // Timer saat kayna��n� a�
	TIM_TBInitStruct.TIM_Prescaler = 4199; // �nB�l�c� (PSC) de�eri 4199
	TIM_TBInitStruct.TIM_Period = 1; // Otomatik geri y�kleme (ARR) e�i�i 1
	TIM_TimeBaseInit(TIM7, &TIM_TBInitStruct); // Timeri init et

	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE); // Timer Update olay�nda interrupt istesin.
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM7, ENABLE); // Timeri ba�lat
}

void TIM7_IRQHandler(void) {
	TIM7->SR = 0;
	timer_update = 1;
	timeroz();
}

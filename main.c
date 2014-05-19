#include "main.h"
uint8_t timer_update2 = 0;
uint32_t ledtime2 = 0;
void timergok(void);

int main(void) {

	SystemInit(); // cmsis_boot/system_stm32f4xx.c dosyasinda tanimli (satir:209)
	init_gpio();
	init_tim7();
	SysTick_Config(SystemCoreClock / 1000); //1milisaniyelik system clock elde edelim
	while (1) {

//		GPIO_ToggleBits(GPIOD, GPIO_Pin_13); //turuncu led
		DelayMs(1000);
	}
}
void DelayMs(int miliseconds) {
	int i = 0, j = 0;
	for (i = 0; i < miliseconds; i++) {
		for (j = 0; j < 8388; j++) {

		}
	}
}

void SysTick_Handler() {
	timer_update2 = 1;

	timergok();

//	SysTick_Config(SysTick_LOAD_RELOAD_Pos);
//	STK_CTRL&=~0x00010000;//count flag slincek
}
void timergok(void) {
	if (timer_update2) {
		timer_update2 = 0;
		if (++ledtime2 > 1000) {
			ledtime2 = 0;
//			GPIO_ToggleBits(GPIOD, GPIO_Pin_14); //kirmizi led
			GPIOD->ODR ^= 0x00004000; //toggle et
		}
	}
}

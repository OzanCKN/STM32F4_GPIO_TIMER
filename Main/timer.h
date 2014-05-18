#include "main.h"

void timeroz(void);
void init_tim7(void);
void TIM7_IRQHandler(void);
uint8_t timer_update = 0;
uint32_t ledtime = 0;

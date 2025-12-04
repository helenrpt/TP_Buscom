#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "util.h"
#include "onewire.h"

ONEWIRE_PINOUT D2 = {GPIOA,5};


int main(void)
{
	FPU_Init();
	GPIO_Init();
	GPIO_SetPullUp(GPIOA,5);
	USART2_Init();
	SYSTICK_Init();
	TIMER6_Init();
	while(1){
		//SYSTICK_Delay(1000);
		//TIMER_DelayUs(90000);
		ONEWIRE_RESET(&D2);
		TIMER_DelayUs(800);
		//ONEWIRE_Writebit0(&D2);
		//GPIOA->ODR ^= 1<<5;
		//printf("Hello\r\n");
	}
}

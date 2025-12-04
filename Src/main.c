#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "util.h"
#include "onewire.h"
#include "interrupt.h"

ONEWIRE_PINOUT PA6 = {GPIOA,6}; //PA6


int main(void)
{
	FPU_Init();
	GPIO_Init();
	GPIO_SetPullUp(GPIOA,6);
	USART2_Init();
	SYSTICK_Init();
	TIMER6_Init();
	EXTI7_Init();  // Configuration de l'interruption sur PA7
	while(1){
		//SYSTICK_Delay(1000);
		//TIMER_DelayUs(90000);
		ONEWIRE_RESET(&PA6);
		TIMER_DelayUs(800);
		//ONEWIRE_Writebit0(&PA6);
		//GPIOA->ODR ^= 1<<5;
		//printf("Hello\r\n");
	}
}

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

ONEWIRE_PINOUT PA10 = {GPIOA,10}; //PA6
uint8_t presence;
uint8_t consigne=18;


int main(void)
{
	FPU_Init();
	GPIO_Init();
	USART2_Init();
	TIMER6_Init();
	DWT_Init();

	PA7_Activation_Thermostat_Init();// Configuration de l'interruption sur PA7
	PushButtonInterrup_Init(); // Configuration de l'interruption sur PC13
	
	printf("init fait\n");
	while(1){
		//SYSTICK_Delay(1000);
		//TIMER_DelayUs(90000);
		//presence =ONEWIRE_RESET(&PA10);

		 //TIMER_DelayUs(480);
		//ONEWIRE_Writebit0(&PA6);
		//GPIOA->ODR ^= 1<<5;
		//printf("present %d",presence);
	}
}

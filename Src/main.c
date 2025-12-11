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
#include "ds18b20.h"

ONEWIRE_PINOUT PA10 = {GPIOA,10}; //PA6
uint8_t presence;
uint8_t consigne=18;
uint16_t temp =0;
float tempsensor =0;
int alarmSts =0;


int main(void)
{
	FPU_Init();
	GPIO_Init();
	USART2_Init();
	TIMER6_Init();
	DWT_Init();

	PA7_Activation_Thermostat_Init();// Configuration de l'interruption sur PA7
	PushButtonInterrup_Init(); // Configuration de l'interruption sur PC13
	printf("init fait\n\r");
	
	TIMER_DelayUs(1000);
	presence =ONEWIRE_RESET(&PA10);
	printf("present %d\n\r",presence);

	TIMER_DelayUs(1000);

	//write_scratchpad(&PA10 , 0 , 0, 0x7F);




	while(1){



		while(alarmSts ==1){
		 tempsensor = Temp_Convert(&PA10);

		 printf("temperature = %.2f °C\n\n\r", tempsensor);


		 if (DS18B20_CheckAlarm(&PA10))
		 {
		     printf(" ALARME DS18B20 ACTIVE !\n");
		     // ici : activer relais, LED, buzzer, etc.
		 }
		 else
		 {
		     printf("OK : pas d’alarme\n");
		 }


		 DWT_Delay(1000000);
		}


		 //temp = temp_calcul(tempsensor);

		 //printf("temperature %d \n",temp);





		//ONEWIRE_Writebit0(&PA6);
		//GPIOA->ODR ^= 1<<5;

	}
}

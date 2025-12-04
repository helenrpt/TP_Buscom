#include <stdint.h>
#include <stm32f446xx.h>
#include "main.h"
#include "gpio.h"

void GPIO_Init(void){
	/* Clock Init */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

	/* GPIO Init */
	GPIOA->MODER |= OUTPUT_MODE <<10;		// PA5 Output LED
	GPIOC->MODER |= INPUT_MODE	<< 26;		// PC13 Input Push-Button

	/*one wire Init PA6 */
	GPIOA->MODER  	|=1 << 12;	//mode out
	GPIOA->OTYPER	|=1 << 6; 	//mode open drain
	GPIOA->PUPDR	|=1 << 12; 	//pull up

	/* PA7 - digital input active thermostat*/
	GPIOA->MODER  	|= INPUT_MODE << 14;	//mode input
}


void GPIO_SetPin(GPIO_TypeDef* GPIO, uint16_t pin){
	GPIO->ODR |= 1 << pin ;
}

void GPIO_ResetPin(GPIO_TypeDef* GPIO, uint16_t pin){
	GPIO->ODR &= ~(1 << pin) ;
}

void GPIO_TogglePin(GPIO_TypeDef* GPIO, uint16_t pin){
	GPIO->ODR ^= 1 << pin ;
}

uint16_t GPIO_ReadPin(GPIO_TypeDef* GPIO, uint16_t pin){
	if((GPIO->IDR & (1 << pin)) !=0)	return 1;
	else 								return 0;
}

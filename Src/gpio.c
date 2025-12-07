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
	GPIOC->PUPDR |= (0x1 << 26);			// PC13 Pull-up resistor

	/*one wire Init PA10 */
	GPIOA->MODER  	|=1 << 20;	//mode out
	GPIOA->OTYPER	|=1 << 10; 	//mode open drain
	//GPIAO->OSPEEDR	|=3U << 20;
	GPIOA->PUPDR	|=1 << 20; 	//pull up

	/* PA7 - digital input for 3.3V signal */
	GPIOA->MODER  	&= ~(0x3 << 14);	// Clear mode bits (input mode = 00)
	GPIOA->PUPDR	&= ~(0x3 << 14);	// No pull-up/pull-down (floating input)
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

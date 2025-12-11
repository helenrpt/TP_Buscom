#include <stdint.h>
#include <stdio.h>
#include "stm32f446xx.h"
#include "interrupt.h"
#include "onewire.h"
#include "ds18b20.h"


extern uint32_t ticks;

// Interrupt Handler for SysTick Interrupt
void SysTick_Handler(void){
	ticks++;
}

//////////////// HOW TO SETUP INTERUPT ? ///////////
// 1. Activate the NVIC IT :  NVIC_EnableIRQ().
// 2. Define the Event that generate IT : GPIO Rising Edge, Timer Update, USART RX not empty...
// 3. Write the corresponding ISR (Interrupt Sub-Routine) code. Do not forget to reset IT Flag.

///////////////         EXTI             //////////
// When using EXTI, to define the Event that generate IT (2), we need :
// a. Enable SYSCFG peripheral clock.
// b. Select the right PORT connected to EXTIx : SYSCFR->EXTICR.
// c. Unmask IT on EXTIx : EXTI->IMR.
// d. Select Rising or falling trigger edge :  EXTI->RTSR or EXTI->FTSR.



/* ACTIVATION THERMOSTAT (PA7) INTERRUPT*/

void PA7_Activation_Thermostat_Init(void) {

	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[1] &= ~(0xF << 12);  // Clear bits for EXTI7
	SYSCFG->EXTICR[1] |= (0x0 << 12);   // PORTA (0x0)
	
	EXTI->IMR |= EXTI_IMR_MR7;
	EXTI->PR = EXTI_PR_PR7;
	
	EXTI->RTSR |= EXTI_RTSR_TR7;
	EXTI->FTSR |= EXTI_FTSR_TR7;  
	
	NVIC_EnableIRQ(EXTI9_5_IRQn);
}

// Interrupt Handler for EXTI9_5 (handles EXTI5 to EXTI9)

extern int alarmSts;

void EXTI9_5_IRQHandler(void) {
    // Premier if - vérifie EXTI_PR_PR7
    if (EXTI->PR & EXTI_PR_PR7) {
        EXTI->PR = EXTI_PR_PR7;
        // Lire l'état actuel de PA7
        if (GPIOA->IDR & GPIO_IDR_ID7) {
            // PA7 est HIGH → Rising edge
            printf("Alarm ON!\n\r");
            alarmSts = 1;

        } else {
            // PA7 est LOW → Falling edge
            printf("alarm OFF!\n\r");
            alarmSts = 0;
        }
    } 
}


/* PUSH BUTTON INTERRUPT*/
void PushButtonInterrup_Init(void) {
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[3] &= ~(0xF << 4);  // Clear bits for EXTI13
	SYSCFG->EXTICR[3] |= (0x2 << 4);   // PORTC (0x2)
	EXTI->IMR |= EXTI_IMR_MR13;
	EXTI->PR = EXTI_PR_PR13;

	EXTI->FTSR |= EXTI_FTSR_TR13;      // Enable falling edge
	EXTI->RTSR &= ~EXTI_RTSR_TR13;     // Disable rising edge

	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

// Interrupt Handler for EXTI15_10 (handles EXTI10 to EXTI15)
extern uint8_t consigne;
extern uint8_t PA10;
void EXTI15_10_IRQHandler(void) {

	if (EXTI->PR & EXTI_PR_PR13) {	// Check if EXTI13 triggered the interrupt
		EXTI->PR = EXTI_PR_PR13;
		consigne=(consigne+1)%30;
		printf("Consigne: %d\n\r", consigne);

		DS18B20_SetAlarm(&PA10, consigne, 0);




	}
}

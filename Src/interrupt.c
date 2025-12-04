
#include <stdint.h>
#include "stm32f446xx.h"
#include "interrupt.h"

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

// Configuration de l'interruption EXTI7 pour PA7 (front montant)
void EXTI7_Init(void) {
	// a. Enable SYSCFG peripheral clock
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	// b. Connect PA7 to EXTI7 (EXTICR2 for EXTI7, bits 12-15)
	// PORTA = 0000
	SYSCFG->EXTICR[1] &= ~(0xF << 12);  // Clear bits for EXTI7
	SYSCFG->EXTICR[1] |= (0x0 << 12);   // PORTA (0x0)
	
	// c. Unmask interrupt on EXTI7
	EXTI->IMR |= EXTI_IMR_MR7;
	
	// d. Select Rising edge trigger
	EXTI->RTSR |= EXTI_RTSR_TR7;
	EXTI->FTSR &= ~EXTI_FTSR_TR7;  // Disable falling edge
	
	// 1. Enable NVIC interrupt for EXTI9_5
	NVIC_EnableIRQ(EXTI9_5_IRQn);
}

// Interrupt Handler for EXTI9_5 (handles EXTI5 to EXTI9)
void EXTI9_5_IRQHandler(void) {
	// Check if EXTI7 triggered the interrupt
	if (EXTI->PR & EXTI_PR_PR7) {
		// Clear the interrupt flag
		EXTI->PR = EXTI_PR_PR7;
		
		// Your code here - what to do on rising edge of PA7
		// Example: toggle LED on PA5
		GPIOA->ODR ^= (1 << 5);
	}
}


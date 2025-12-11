#include <stdint.h>
#include "stm32f446xx.h"
#include "timer.h"
#include "interrupt.h"

uint32_t SystemCoreClock = 16000000;
uint32_t ticks = 0;



//Timer

void TIMER6_Init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

    TIM6->PSC = 8999;    // 90 MHz / 9000 = 10 kHz
    TIM6->ARR = 999;     // 100 ms (1000 ticks à 10 kHz)

    TIM6->DIER |= TIM_DIER_UIE; // autorise interruption update
    TIM6->CR1 |= TIM_CR1_CEN;   // démarre timer

    NVIC_EnableIRQ(TIM6_DAC_IRQn);

}




/*
void TIMER_DelayUs(uint16_t delayUs) {
    TIM6->ARR = delayUs;
    TIM6->CNT = 0;
    TIM6->SR &= ~TIM_SR_UIF;
    TIM6->CR1 |= TIM_CR1_CEN; // Démarrer
    while (!(TIM6->SR & TIM_SR_UIF));
    TIM6->CR1 &= ~TIM_CR1_CEN; // Stopper
}*/


//////////////////////////////////////////////
////////////// SYSTICK TIMER /////////////////
//////////////////////////////////////////////

void SYSTICK_Init(void){
	SysTick_Config(SystemCoreClock / 1000);
}

/**
 * Millisecond delays with Systick Timer, blocking function
 * @param delay : milliseconds to wait
 */
void SYSTICK_Delay(uint32_t Delay)
{
	uint32_t tickstart = SYSTICK_Get();

	while((SYSTICK_Get() - tickstart) < Delay);
}

uint32_t SYSTICK_Get(void){
	return ticks;
}

//////////////////////////////////////////////
////////////// DW TIMER //////////////////////
//////////////////////////////////////////////

void DWT_Init(void)
{
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	//    DWT->LAR = 0xC5ACCE55;  // For Cortex M7
	DWT->CYCCNT = 0;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

/**
 * Microsecond delays with DW Timer, blocking function
 * @param _us : microseconds to wait
 */
void DWT_Delay(uint32_t _us)
{
	uint32_t startTick  = DWT->CYCCNT;
	uint32_t targetTick = DWT->CYCCNT + _us * (SystemCoreClock/1000000);

	// No overflow
	if (targetTick > startTick)
		while (DWT->CYCCNT < targetTick);

	// With overflow
	else
		while (DWT->CYCCNT > startTick || DWT->CYCCNT < targetTick);

}



// Get MCO HSE to PA8 (D7)
// the MCO1PRE[2:0] and MCO1[1:0]


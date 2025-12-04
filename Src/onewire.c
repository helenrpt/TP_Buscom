//LIB ONE WIRE
#include <stdint.h>
#include <stm32f446xx.h>
#include "main.h"
#include "gpio.h"
#include "onewire.h"



uint16_t ONEWIRE_RESET(ONEWIRE_PINOUT* oneWirepinout){
    uint16_t presence;

    GPIO_Setpin(oneWirepinout->port, oneWirepinout->pin);
    GPIO_Resetpin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(480);
    GPIO_Setpin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(70);
    presence=GPIO_Readpin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(410);
    return!presence;
}


uint16_t ONEWIRE_Writebit0(ONEWIRE_PINOUT* oneWirepinout){
    GPIO_Resetpin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(60);
    GPIO_Setpin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(10);
}


uint16_t ONEWIRE_Writebit1(ONEWIRE_PINOUT* oneWirepinout){
    GPIO_Resetpin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(6);
    GPIO_Setpin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(74);

}


uint8_t ONEWIRE_Read(ONEWIRE_PINOUT* oneWirepinout){
	uint8_t data;
    GPIO_Resetpin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(6);
    GPIO_Setpin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(9);
    data=GPIO_Readpin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(45);
    return data;
}

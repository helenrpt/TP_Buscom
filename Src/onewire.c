//LIB ONE WIRE
#include <stdint.h>
#include <stm32f446xx.h>
#include "main.h"
#include "gpio.h"
#include "onewire.h"
#include "timer.h"



uint16_t ONEWIRE_RESET(ONEWIRE_PINOUT* oneWirepinout){
    uint16_t presence;

    GPIO_ResetPin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(480);
    GPIO_SetPin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(70);
    presence=GPIO_ReadPin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(410);
    return!presence;
}


void ONEWIRE_Writebit0(ONEWIRE_PINOUT* oneWirepinout){
    GPIO_ResetPin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(60);
    GPIO_SetPin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(10);
}


void ONEWIRE_Writebit1(ONEWIRE_PINOUT* oneWirepinout){
    GPIO_ResetPin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(6);
    GPIO_SetPin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(74);
}


uint8_t ONEWIRE_ReadBit(ONEWIRE_PINOUT* oneWirepinout){
	uint8_t data;
    GPIO_ResetPin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(6);
    GPIO_SetPin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(9);
    data=GPIO_ReadPin(oneWirepinout->port, oneWirepinout->pin);
    TIMER_DelayUs(45);
    return data;
}

void ONEWIRE_WriteByte(ONEWIRE_PINOUT* oneWire_Pinout, uint8_t data)
{

	for(int i = 0; i< 8; i++)
	{
		if((data & (1<<i)) == 0)
		{
			ONEWIRE_Writebit0(oneWire_Pinout);
		}
		else ONEWIRE_Writebit1(oneWire_Pinout);
	}
}

uint8_t ONEWIRE_ReadByte(ONEWIRE_PINOUT* oneWire_Pinout)
{
	uint8_t iByte_Sensor = 0;

	for(int i = 0; i< 8; i++)
	{
		iByte_Sensor |=  ONEWIRE_ReadBit(oneWire_Pinout) << i;
	}
	return iByte_Sensor;

}




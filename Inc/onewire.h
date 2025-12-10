#ifndef ONEWIRE_H_
#define ONEWIRE_H_
#include "gpio.h"
#include "stm32f446xx.h"


typedef struct {
	GPIO_TypeDef* 	port; // GPIO Port
	uint16_t		pin;  // GPIO Pin
}ONEWIRE_PINOUT;

uint16_t ONEWIRE_RESET(ONEWIRE_PINOUT* oneWirePinout);


void ONEWIRE_Writebit0(ONEWIRE_PINOUT* oneWirePinout);


void ONEWIRE_Writebit1(ONEWIRE_PINOUT* oneWirePinout);


uint8_t ONEWIRE_ReadBit(ONEWIRE_PINOUT* oneWirePinout);

void ONEWIRE_WriteByte(ONEWIRE_PINOUT* oneWire_Pinout, uint8_t data);

uint8_t ONEWIRE_ReadByte(ONEWIRE_PINOUT* oneWire_Pinout);

#endif

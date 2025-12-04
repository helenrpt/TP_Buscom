#ifndef ONEWIRE_H_
#define ONEWIRE_H_

typedef struct {
	GPIO_TypeDef* 	port; // GPIO Port
	uint16_t		pin;  // GPIO Pin
}ONEWIRE_PINOUT;

uint16_t ONEWIRE_RESET(ONEWIRE_PINOUT* oneWirePinout);


uint16_t ONEWIRE_Writebit0(ONEWIRE_PINOUT* oneWirePinout);


uint16_t ONEWIRE_Writebit1(ONEWIRE_PINOUT* oneWirePinout);


uint8_t ONEWIRE_Read(ONEWIRE_PINOUT* oneWirePinout);

#endif

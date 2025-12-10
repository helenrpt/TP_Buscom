#ifndef DS18B20_H_
#define DS18B20_H_
#include "onewire.h"
#include <stdio.h>
#include <stdint.h>

void write_scratchpad(ONEWIRE_PINOUT* oneWirePinout, uint8_t byte2, uint8_t byte3, uint8_t byte4);
uint16_t Temp_Convert(ONEWIRE_PINOUT* oneWirePinout);
uint32_t Search_Alarm (ONEWIRE_PINOUT* oneWirePinout);

#endif

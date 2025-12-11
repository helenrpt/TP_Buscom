#include <stdio.h>
#include <stdint.h>
#include "ds18b20.h"
#include "timer.h"


#define ADC_12bits 0x7F
#define ADC_11bits 0x5F
#define ADC_10bits 0x3F
#define ADC_9bits 0x1F
/* Transaction Sequence*/
// 1. Initialization: reset pulse from Master
// 2. ROM command or READ ROM if only one slave / SKIP ROM to adress every slave
// 3. DS18B20 Function Command

/* ROM */
#define ROM_CMD         (0xF0)
#define READ_ROM_CMD    (0x33)
#define SEARCH_CMD      (0xEC)
#define SKIP_ROM_CMD    (0xCC)
#define ALARM_SEARCH_CMD (0xEC)

/* Function */

#define CONVERT_T       (0x44)
#define READ_SCRATCHPAD (0xBE)
#define WRITE_SCRATCHPAD (0x4E)





void write_scratchpad(ONEWIRE_PINOUT* oneWirePinout, uint8_t byte2, uint8_t byte3, uint8_t byte4){

    //  | byte 2 : TH | Byte 3: TL | Byte 4: configuration| // 
    ONEWIRE_RESET(oneWirePinout);
    ONEWIRE_WriteByte(oneWirePinout,SKIP_ROM_CMD);
    ONEWIRE_WriteByte(oneWirePinout,WRITE_SCRATCHPAD);

    ONEWIRE_WriteByte(oneWirePinout,byte2);
    ONEWIRE_WriteByte(oneWirePinout,byte3);
    ONEWIRE_WriteByte(oneWirePinout,byte4);
    ONEWIRE_RESET(oneWirePinout);

}


float Temp_Convert(ONEWIRE_PINOUT* oneWirePinout)
{
    uint8_t LSB, MSB;
    uint16_t raw;

    ONEWIRE_RESET(oneWirePinout);
    ONEWIRE_WriteByte(oneWirePinout, SKIP_ROM_CMD);
    ONEWIRE_WriteByte(oneWirePinout, CONVERT_T);

    DWT_Delay(750000); // max conversion time

    ONEWIRE_RESET(oneWirePinout);
    ONEWIRE_WriteByte(oneWirePinout, SKIP_ROM_CMD);
    ONEWIRE_WriteByte(oneWirePinout, READ_SCRATCHPAD);

    LSB = ONEWIRE_ReadByte(oneWirePinout);
    MSB = ONEWIRE_ReadByte(oneWirePinout);
    raw = (MSB << 8) | LSB;
    printf("LSB=0x%02X MSB=0x%02X RAW=0x%04X\n\r", LSB, MSB, raw);


    return raw / 16.0f;
}





//config alarm

void DS18B20_SetAlarm(ONEWIRE_PINOUT *pin, int8_t TH, int8_t TL)
{
    ONEWIRE_RESET(pin);
    ONEWIRE_WriteByte(pin, SKIP_ROM_CMD);
    ONEWIRE_WriteByte(pin, WRITE_SCRATCHPAD);

    ONEWIRE_WriteByte(pin, TH);    // Alarm High
    ONEWIRE_WriteByte(pin, TL);    // Alarm Low
    ONEWIRE_WriteByte(pin, 0x7F);  // Configuration = 12 bits

    // Copy scratchpad (sauvegarde dans EEPROM interne)
    ONEWIRE_RESET(pin);
    ONEWIRE_WriteByte(pin, SKIP_ROM_CMD);
    ONEWIRE_WriteByte(pin, 0x48); // COPY SCRATCHPAD
}


uint8_t DS18B20_CheckAlarm(ONEWIRE_PINOUT *pin)
{
    uint8_t presence;
    uint8_t rom[8];

    ONEWIRE_RESET(pin);
    ONEWIRE_WriteByte(pin, ALARM_SEARCH_CMD); // 0xEC

    // Dans ton cas: un seul capteur
    for (int i = 0; i < 8; i++)
        rom[i] = ONEWIRE_ReadByte(pin);

    // Si rom = FF FF FF FF FF FF FF FF → aucune alarme
    uint8_t allFF = 1;
    for (int i = 0; i < 8; i++)
        if (rom[i] != 0xFF)
            allFF = 0;

    if (allFF)
        return 0; // aucune alarme

    // Sinon = alarme détectée
    return 1;
}

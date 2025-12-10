#include <stdio.h>
#include <stdint.h>
#include "ds18b20.h"
#include "timer.h"


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


uint16_t Temp_Convert(ONEWIRE_PINOUT* oneWirePinout)
{
	uint16_t Temp = 0;
	uint8_t Temp_byte1 = 0;
	uint8_t Temp_byte2 = 0;

	ONEWIRE_RESET(oneWirePinout);
    ONEWIRE_WriteByte(oneWirePinout,SKIP_ROM_CMD);
    ONEWIRE_WriteByte(oneWirePinout,CONVERT_T);

    SYSTICK_Delay(750);

    ONEWIRE_RESET(oneWirePinout);
    ONEWIRE_WriteByte(oneWirePinout,SKIP_ROM_CMD);
    ONEWIRE_WriteByte(oneWirePinout,READ_SCRATCHPAD);
	Temp_byte1 = ONEWIRE_ReadByte(oneWirePinout);
	Temp_byte2 = ONEWIRE_ReadByte(oneWirePinout);
    ONEWIRE_RESET(oneWirePinout);
	
    Temp = Temp_byte1 |((Temp_byte2<<8));

	return Temp;
}



//config alarm


uint32_t Search_Alarm (ONEWIRE_PINOUT* oneWirePinout){
    
    uint32_t read = 0;
    ONEWIRE_RESET(oneWirePinout);
    ONEWIRE_WriteByte(oneWirePinout,ALARM_SEARCH_CMD);
	read = ONEWIRE_ReadByte(oneWirePinout);
	ONEWIRE_RESET(oneWirePinout);
	printf ("%01X\r\n",&read);
    return read;
}

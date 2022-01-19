#ifndef ds18b20_h
#define ds18b20_h

#include "head_files.h"

void ProcessDS18B20();

// Defines used only in code example.
#define OWI_STATE_IDLE                  0
#define OWI_STATE_DETECT_PRESENCE1      1
#define OWI_STATE_WAIT_FOR_CONVERSION1  2
#define OWI_STATE_WAIT_FOR_CONVERSION2  3
#define OWI_STATE_DETECT_PRESENCE2      4
#define OWI_STATE_READ_SCRATCHPAD       5
#define OWI_STATE_CHECK_CRC             6


#define DS1820_START_CONVERSION         0x44    //!< DS1820 start conversion command//68
#define DS1820_READ_SCRATCHPAD          0xbe    //!< DS1820 Read scratchpad command//190

#endif

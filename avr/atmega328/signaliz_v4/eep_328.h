#ifndef eeprom__h
#define eeprom__h
//---------------
#include "_def.h"
#include "head_files.h"

#define BYTE_X8   0
#define BYTE_X16  1
#define BYTE_X32  2
#define ARRAY_X8  3
#define ARRAY_X16 4
#define ARRAY_X32 5

void ReadEeprom_x8 (u08 adress,uint8_t *pdatafromeep);
void ReadEeprom_x16 (u08 adress,uint16_t *pdatafromeep);
void ReadEeprom_x32 (u08 adress,int32_t *pdatafromeep);

void ReadArrayEeprom_x8 (uint8_t kol_vo_elements,u08 adress,int8_t *parrayfromeep);
void ReadArrayEeprom_x16 (uint8_t kol_vo_elements,u08 adress,int16_t *parrayfromeep);
void ReadArrayEeprom_x32 (uint8_t kol_vo_elements,u08 adress,int32_t *parrayfromeep);

void WriteEeprom_x8 (u08 adress,uint8_t *pdata2write);
void WriteEeprom_x16 (u08 adress,uint16_t *pdata2write);
void WriteEeprom_x32 (u08 adress,int32_t *pdata2write);

void WriteArrayEeprom_x8 (uint8_t kol_vo_bytes,u08 adress,int8_t *parray2write);
void WriteArrayEeprom_x16 (uint8_t kol_vo_bytes,u08 adress,int16_t *parray2write);
void WriteArrayEeprom_x32 (uint8_t kol_vo_bytes,u08 adress,int32_t *parray2write);


#endif

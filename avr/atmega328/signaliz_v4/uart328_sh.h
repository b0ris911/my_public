#ifndef uart328_sh_h
#define uart328_sh_h

#include "head_files.h"

//defs
#define baudrate 9600L
#define bauddivider ((F_CPU+baudrate*8)/(16*baudrate)-1)
#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)

//prots
void InitUart();
void StartTxUart();
void StopTxUart();
void SendDigitUart(u32 data,u08 digits,u08 new_line);
void ProcessShedulerUart();
void SendTextUart(char text[],u08 new_line);

#define NUMBER_OF_STRINGS		10
#define STRING_LENGTH			40
#define TIME_INC_COUNTER_SYSTEM_RESET			6000	//ms

#endif

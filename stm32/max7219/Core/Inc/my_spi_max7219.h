#ifndef MY_SPI_MAX7219_H_
#define MY_SPI_MAX7219_H_

#include "my_head_files.h"

#define NUMBER_OF_SEGMENTS	4
#define SIZE_VIRTUAL_ARRAY	160

#define SPI_MODULE_MAX7219	SPI2

void Test_MAX7219(void);
void SendWord(u08 reg,u08 byte);
void  SendDataSPI_X(u16 data);
void Clean_All(void);
u08 RunningDots(void);
void Init_4_MAX7219(void);
void TestLine(void);
void SwapArrays(void);
void ShowMax7219(void);
void SetSymbol(char symbol,u08 place); //place 31...0
void SetString(char *string,u08 place); //place
void CleanArray(void);
void SetVirtualArray(char *string);
u08 RunVA(void);
u08 DinVA(void);
u08 StaticVA(void);
void Change_Regime_Test_Max7219(void);
void Test_Modes_Max7219(void);

#endif

#ifndef my_UART_SH_STM32_H_
#define my_UART_SH_STM32_H_


#include "my_head_files.h"
#include <string.h>

#define FREE_UART		0
#define BUSY_UART		1
#define END_UART		2

#define NUMBER_OF_STRINGS		30
#define STRING_LENGTH			30

void SendDigitUart(u32 data,u08 digits,u08 new_line);
void SendTrimDigitUart(u32 data,u08 digits,u08 new_line);
void SendTextUart(char *text_in,u08 new_line);
void ProcessShedulerUart(UART_HandleTypeDef *huart);


#endif /* UART_SH_STM32_H_ */

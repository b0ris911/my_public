#ifndef my_uart_queue_h
#define my_uart_queue_h

#include "my_head_files.h"

#define STRING_LENGTH			50
#define STRING_NUMBER			20
#define UART_MODULE 			&huart4

void SendIntDigitUartX(int mas_in,u08 new_line);
void SendTextUartX(char *string_in,u08 new_line);
void vTaskProcessUart(void *param);
void vTaskSendDataToUART (void *param);
void InitQueueUART(void);

#endif 

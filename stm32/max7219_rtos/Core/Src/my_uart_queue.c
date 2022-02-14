#include "my_uart_queue.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

extern TaskHandle_t Handle_vTaskProcessUart;

xQueueHandle xQueue_uart;
portBASE_TYPE xStatus;
static char str[STRING_LENGTH];

//------------------------------------------------------
void vTaskSendDataToUART (void *param) {
volatile static u32 w=0;
	while(1){
		SendTextUartX("Hello, friend ",0);
		SendTextUartX("Boris! ",0);
		SendIntDigitUartX(w++,1);
		vTaskDelay(100);
}}
//------------------------------------------------------
//------------------------------------------------------
void SendIntDigitUartX(int data_in,u08 new_line){
char mas_out[15];
	if(data_in<0) data_in=-data_in;
	if(new_line==0){
		sprintf(mas_out,"%d",data_in);
	}
	else{
		sprintf(mas_out,"%d\r\n",data_in);
	}
	xQueueSendToBack(xQueue_uart,(void*)mas_out,0);
}
//------------------------------------------------------
void SendTextUartX(char *string_in,u08 new_line) {
	if(new_line==0){
		sprintf(str,"%s",string_in);
	}
	else{
		sprintf(str,"%s\r\n",string_in);
	}
	xQueueSendToBack(xQueue_uart,(void*)str,0);
}
//------------------------------------------------------
void vTaskProcessUart(void *param){
static char string_out[STRING_LENGTH]={0};
while(1){
	xStatus = xQueueReceive(xQueue_uart,(void*)string_out,portMAX_DELAY);
	if (xStatus == pdPASS) {
		HAL_UART_Transmit_IT(UART_MODULE,(unsigned char*)string_out,strlen(string_out));
	}
	vTaskSuspend(NULL);
}}
//---------------------------------------------------------
void HAL_UART_TxCpltCallback (UART_HandleTypeDef * huart) {
	xTaskResumeFromISR(Handle_vTaskProcessUart);
}
//------------------------------------------------------
void InitQueueUART(void){
	xQueue_uart = xQueueCreate(STRING_NUMBER, STRING_LENGTH);
}

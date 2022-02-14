#include "my_tasks.h"
#include "gpio.h"
#include "i2c.h"

extern TaskHandle_t Handle_vTaskTestTimer;
extern TaskHandle_t Handle_vTaskTestLed;
extern TaskHandle_t Handle_vTaskStartAdcConversion;
extern TaskHandle_t Handle_vTaskShowAdcResultOnUART;
extern TaskHandle_t Handle_vTaskSi7021_BMP180;
extern TaskHandle_t Handle_vTaskProcessShedulerI2C;
extern TaskHandle_t Handle_vTaskMemory;
extern TaskHandle_t Handle_vTaskStartTrig;
extern TaskHandle_t Handle_vTaskRunLedLine;
extern TaskHandle_t Handle_vTaskGSCC;
extern TaskHandle_t Handle_vTaskProcessUart;
extern TaskHandle_t Handle_vTaskAlg_HCSR;
extern TaskHandle_t Handle_vTaskStartTrig;
extern TaskHandle_t Handle_vTaskLightEffects;
extern TaskHandle_t Handle_vTaskRunLedLine;
extern TaskHandle_t Handle_vTaskChangeLightEffects;
extern TaskHandle_t Handle_vTaskTest_Modes_Max7219;

volatile static u16 systick=0;
//------------------------------------------------------------------
void vTaskGSCC(void *param){
	volatile static u08 dist=5;
	while(1){
		//GSCC();*****
	//	dist=Distance_get_data()/3;*****
		if(dist>100) dist=100;
		//dist=7;
		//vTaskDelay(dist);
		vTaskDelay(4);
	}
}
//------------------------------------------------------------------
//------------------------------------------------------------------
void vTaskMemory(void *param) {
	while(1){
		vTaskDelay(1000);
		uxTaskGetStackHighWaterMark(NULL);
		SendTextUartX("all heap= ",0);
		SendIntDigitUartX(xPortGetFreeHeapSize(),0);
		SendTextUartX("  minimum= ",0);
		SendIntDigitUartX(xPortGetMinimumEverFreeHeapSize(),1);

		SendTextUartX("led= ",0);
		SendIntDigitUartX(uxTaskGetStackHighWaterMark(Handle_vTaskTestLed),1);
		SendTextUartX("sh_uart= ",0);
		SendIntDigitUartX(uxTaskGetStackHighWaterMark(Handle_vTaskProcessUart),1);
		SendTextUartX("start_adc= ",0);
		SendIntDigitUartX(uxTaskGetStackHighWaterMark(Handle_vTaskStartAdcConversion),1);
		SendTextUartX("show_adc= ",0);
		SendIntDigitUartX(uxTaskGetStackHighWaterMark(Handle_vTaskShowAdcResultOnUART),1);
		SendTextUartX("si7021_&_bmp180= ",0);
		SendIntDigitUartX(uxTaskGetStackHighWaterMark(Handle_vTaskSi7021_BMP180),1);
		SendTextUartX("sh_i2c= ",0);
		SendIntDigitUartX(uxTaskGetStackHighWaterMark(Handle_vTaskProcessShedulerI2C),1);
		SendTextUartX("mem= ",0);
		SendIntDigitUartX(uxTaskGetStackHighWaterMark(NULL/*Handle_vTaskMemory*/),1);
		SendTextUartX("max7219= ",0);
		SendIntDigitUartX(uxTaskGetStackHighWaterMark(Handle_vTaskTest_Modes_Max7219),1);

	//	SendTextUartX("run_ll= ",0);
	//	SendIntDigitUartX(uxTaskGetStackHighWaterMark(Handle_vTaskRunLedLine),1);
	//	SendTextUartX("light_effects= ",0);
	//	SendIntDigitUartX(uxTaskGetStackHighWaterMark(Handle_vTaskLightEffects),1);
	}
}
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
void vTaskTestLed(void *param) {
	while(1) {
		HAL_GPIO_WritePin(GPIOF, LED_PF9_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOF, LED_PF10_Pin, GPIO_PIN_SET);
		vTaskDelay(1000);
		HAL_GPIO_WritePin(GPIOF, LED_PF9_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOF, LED_PF10_Pin, GPIO_PIN_RESET);
		vTaskDelay(1000);
	}
}
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
void vApplicationTickHook(void) {
	systick++;
}
u32 Get_systick(void){
	return systick;
}

#include "my_adc_rtos.h"
#include "adc.h"

volatile static u32 adc_result; // переменная для результата
volatile u16 volts;
volatile u16 m_volts;
volatile u32 adc_data;
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
void vTaskShowADC(void *param) {
char array_tft[MAX_SIZE];
	while(1){
		SendTextUartX(" ",1);
		SendTextUartX("adc1  ",0);
		SendIntDigitUartX(AdcResult_get_data_mv(),1);
		SendTextUartX(" ",1);
		TFTDrawUT32_X(32,18,GREEN, FONE,AdcResult_get_data_mv(),4,2,array_tft);
		vTaskDelay(500);
	}//w
}//v
//-----------------------------------------------------------------------
void vTaskStartAdcConversion(void *param) {
	while(1) {
		vTaskDelay(5);
		HAL_ADC_Start_IT(&hadc1);
	}
}
//-----------------------------------------------------------------------
u16 AdcResult_get_data_mv() {
	adc_result = (VREF * adc_data) / 4096;
/*	if(adc_result%100!=0) {
		adc_result=(adc_result/100)*100;
	}*/
	return adc_result;
}
//-----------------------------------------------------------------------
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
volatile static u08 counter=0;
volatile static u32 tmp=0;
	if(hadc->Instance == ADC1) {
		tmp=tmp+ HAL_ADC_GetValue(&hadc1);
		counter++;
		if(counter==8) {
			counter=0;
			adc_data=tmp/8;
			tmp=0;
		}
	}
}
//-----------------------------------------------------------------------
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc) {
	if(hadc->Instance == ADC1) {
		//SendMessage(MSG_ADCEx_InjectedConvCpltCallback);
	}
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------


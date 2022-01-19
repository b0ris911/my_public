#include "my_adc.h"
#include "adc.h"

volatile static u32 adc_result; // переменная для результата
volatile u16 volts;
volatile u16 m_volts;

volatile u32 adc_data;
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
u16 AdcResult_get_data_mv() {
	adc_result = (VREF * adc_data) / 4096;
	return adc_result;
}
//-----------------------------------------------------------------------
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
volatile static u08 counter=0;
volatile static u32 tmp=0;
	if(hadc->Instance == ADC1) {
		tmp=tmp+ HAL_ADC_GetValue(&hadc1);
		counter++;
		if(counter==COUNTER_ADC) {
			counter=0;
			adc_data=tmp/COUNTER_ADC;
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

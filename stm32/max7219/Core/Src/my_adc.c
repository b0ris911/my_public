#include "my_adc.h"
#include "adc.h"

volatile static u32 adc_result; // переменная для результата
volatile u16 volts;
volatile u16 m_volts;

volatile u32 adc_data;
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
void FirstScreen(void){
    TFTDrawString(0,2, GREEN,FONE, "U=",3);
    TFTDrawString(144,2, GREEN,FONE, "mV",3);

    TFTDrawString(20,28,ORANGE,FONE,"Si7021",3);
    TFTDrawString(0,54,GREEN,FONE,"H:",3);
    TFTDrawString(0,80,GREEN,FONE,"T:",3);

    TFTDrawString(20,106,ORANGE,FONE,"BMP180",3);
    TFTDrawString(0,132,GREEN,FONE,"P:",3);
    TFTDrawString(120,132,GREEN,FONE,"mm",3);
    TFTDrawString(0,158,GREEN,FONE,"T:",3);
}
//-----------------------------------------------------------------------
u16 AdcResult_get_data_mv() {
	adc_result = (VREF * adc_data) / 4096;
	//adc_result=100;
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
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
void ProcessDataADC() {
    //adc_result=(tmp_0*vrefint_calc+2048)/4096;//перевели единицы в милливольты
 //   Start_ADC_DMA();
}

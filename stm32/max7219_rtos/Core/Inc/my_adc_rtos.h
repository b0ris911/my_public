#ifndef my_adc_rtos_h
#define my_adc_rtos_h

#include "my_head_files.h"

#define VREF 3300 // напряжение ИОН

u16 AdcResult_get_data_mv();
void vTaskShowAdcResultOnUART(void *param);
void vTaskStartAdcConversion(void *param);
void vTaskShowADC(void *param);

#endif

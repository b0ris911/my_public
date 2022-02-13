#ifndef my_adc_h
#define my_adc_h

#include "my_head_files.h"

#define VREF 3300 // напряжение ИОН
#define COUNTER_ADC		32
u16 AdcResult_get_data_mv();
void FirstScreen(void);
void ShowResultsOnLCD(void);


#endif

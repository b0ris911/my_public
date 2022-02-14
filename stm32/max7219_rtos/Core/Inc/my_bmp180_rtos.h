#ifndef my_bmp180_h
#define my_bmp180_h

#include "my_def.h"
#include "my_head_files.h"

#define OSS 3
#define BMP180_ADDR	0b11101110


void BMP180_rtos();
void ProcessErrorBMP180(void);
void vTask_BMP180_Delay_1(void *param);
void vTask_BMP180_Delay_2(void *param);
u16 Pres_BMP180_get_data(void);
u16 Temp_BMP180_get_data(void);


#endif

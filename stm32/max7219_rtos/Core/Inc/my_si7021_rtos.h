#ifndef my_si7021_rtos_h
#define my_si7021_rtos_h

#include "my_def.h"
#include "my_head_files.h"
#include "i2c.h"


void vTaskSi7021_BMP180();
void Si7021_rtos();
void vTask_Si7021_Delay(void *param);
void ProcessErrorSi7021(void);
u16 Hum_Si7021_get_data(void);
u16 Temp_Si7021_get_data(void);


#define Si7021_ADDR			0b10000000
#define I2C_ID_ADDRESS		0xD0
#define I2C_TIMEOUT			10
#define SI7021_RESET		0xFE


void readID();
void readIDinterrupt();

#endif

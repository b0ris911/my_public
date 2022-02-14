#ifndef my_i2c_sh2_h
#define my_i2c_sh2_h

#include "my_head_files.h"


void ShedulerI2C(void (*pfunc)());
void ShedulerI2C_Init(void (*pfunc)()); //before start rtos sheduler
void vTaskProcessShedulerI2C(void * param);
void vTask_Error_Callback(void *param);

#define I2C_MODULE		hi2c1

#define FREE_I2C		0	//свободен для любого
#define BUSY_I2C		1	//занят
#define END_I2C			2	//конец очередной функции

#define MAXQUEUE	10	//макс. размер очереди

#define i2c_MasterAddress 	0xA0	// Адрес на который будем отзываться
#define i2c_i_am_slave		0	// Если мы еще и слейвом работаем то 1. А то не услышит!

#define i2c_MasterBytesRX	1	// Величина принимающего буфера режима Slave, т.е. сколько байт жрем.
#define i2c_MasterBytesTX	1	// Величина Передающего буфера режима Slave , т.е. сколько байт отдаем за сессию.

#define i2c_MAXBUFFER		50	// Величина буфера Master режима RX-TX. Зависит от того какой длины строки мы будем гонять
#define i2c_MaxPageAddrLgth	1	// Максимальная величина адреса страницы. Обычно адрес страницы это один или два байта.


	#endif


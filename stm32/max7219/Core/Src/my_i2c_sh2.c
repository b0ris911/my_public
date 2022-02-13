#include "my_i2c_sh2.h"
#include "i2c.h"
//volatile u08 state_uart;						// Переменная состояния передатчика I2C
volatile u08 i2c_error=0;
volatile u08 i2c_alg=0;
volatile u08 counter_errors_i2c=0;

//sheduler
void (*maspfuncs[MAXQUEUE])()={0};
volatile s08 queue_i2c=0;
volatile u08 status_i2c=FREE_I2C;
volatile u08 foa_start_i2c=ON;
//volatile u08 was_error_i2c_time_reset=NO;

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c){
	status_i2c=FREE_I2C;
}
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
	status_i2c=FREE_I2C;
}
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
	status_i2c=FREE_I2C;
}
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	status_i2c=FREE_I2C;
}
void HAL_I2C_ErrorCallback (I2C_HandleTypeDef * hi2c)
{// Функция обратного вызова исключения ошибки
	//I2C1->ISR=0;
//	LedRedOn();
	_delay_ms(20);
//	LedRedOff();
	i2c_error=1;
	status_i2c=FREE_I2C;
}
//------------------------------------------------
//--------------------------------
void ShedulerI2C(void (*pfunc)()) {
	maspfuncs[queue_i2c]=pfunc;	
	queue_i2c++;
	if (queue_i2c>MAXQUEUE)
		queue_i2c=MAXQUEUE;
}
//--------------------------------
void ProcessShedulerI2c() {
volatile static u08 step=0;
u08 i=0;

	if(status_i2c!=FREE_I2C) {
//		CLI
		if (ExpGTimer(timer_reset_i2c)) {
		//	was_error_i2c_time_reset=YES;
		//	status_i2c=END;
		}
	//	SEI
	}

switch (status_i2c) {

	case BUSY_I2C:
	break;

	case END_I2C:
	...
	break;

	case FREE_I2C:
	...
	break;				
}}

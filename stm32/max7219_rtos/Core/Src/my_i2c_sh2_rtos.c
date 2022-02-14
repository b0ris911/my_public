#include "my_i2c_sh2_rtos.h"
#include "i2c.h"

extern TaskHandle_t Handle_vTaskProcessShedulerI2C;

volatile u08 i2c_error=0;
volatile u08 i2c_alg=0;
volatile u08 counter_errors_i2c=0;

//sheduler
void (*maspfuncs[MAXQUEUE])()={0};
volatile s08 queue_i2c=0;
volatile u08 status_i2c=FREE_I2C;
volatile u08 foa_start_i2c=ON;
//volatile u08 was_error_i2c_time_reset=NO;
volatile static u08 flag_ec=0;
//----------------------------------------------------------------------
void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c){
	status_i2c=FREE_I2C;
	xTaskResumeFromISR(Handle_vTaskProcessShedulerI2C);
}
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
	status_i2c=FREE_I2C;
	xTaskResumeFromISR(Handle_vTaskProcessShedulerI2C);
}
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
	status_i2c=FREE_I2C;
	xTaskResumeFromISR(Handle_vTaskProcessShedulerI2C);
}
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	status_i2c=FREE_I2C;
	xTaskResumeFromISR(Handle_vTaskProcessShedulerI2C);
}
void HAL_I2C_ErrorCallback (I2C_HandleTypeDef * hi2c){// Функция обратного вызова исключения ошибки
//	HAL_GPIO_WritePin(Test3_GPIO_Port, Test3_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(Test3_GPIO_Port, Test3_Pin, GPIO_PIN_RESET);
	flag_ec=1;
	xTaskResumeFromISR(Handle_vTaskProcessShedulerI2C);
}
//--------------------------------
void ShedulerI2C_Init(void (*pfunc)()) { //before start rtos sheduler
	maspfuncs[queue_i2c]=pfunc;
	queue_i2c++;
	if (queue_i2c>MAXQUEUE)
		queue_i2c=MAXQUEUE;
}
//--------------------------------
void ShedulerI2C(void (*pfunc)()) {
	maspfuncs[queue_i2c]=pfunc;	
	queue_i2c++;
	if (queue_i2c>MAXQUEUE)
		queue_i2c=MAXQUEUE;
	if(queue_i2c==1) {
		vTaskResume(Handle_vTaskProcessShedulerI2C);
	}
}
//--------------------------------
void vTaskProcessShedulerI2C(void * param) {
volatile u08 i=0;
while(1) {
	//HAL_GPIO_WritePin(Test1_GPIO_Port, Test1_Pin, GPIO_PIN_SET);
	//HAL_GPIO_WritePin(Test1_GPIO_Port, Test1_Pin, GPIO_PIN_RESET);
	switch (status_i2c) {
		case BUSY_I2C:
			status_i2c=END_I2C;

		case END_I2C:
		...
//		break;

		case FREE_I2C:
		...
		break;
}}
//HAL_GPIO_WritePin(Test1_GPIO_Port, Test1_Pin, GPIO_PIN_RESET);
}
//---------------------------------------------------------------
//------------------------------------------------------------------
void vTask_Error_Callback(void *param) {
while(1){
	//SendTextUartX("was Error_callback",1);
	vTaskDelete(NULL);
}}
//------------------------------------------------------------------


//---------------------------------------------------------------
//---------------------------------------------------------------
//---------------------------------------------------------------

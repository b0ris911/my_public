#include "my_si7021_rtos.h"

extern u08 i2c_alg;
extern u08 status_i2c;
extern u08 i2c_error;
extern TaskHandle_t Handle_vTaskProcessShedulerI2c;

volatile static u08 i2c_slave_addr;						// адрес слэйва
static u08 i2c_buf[i2c_MAXBUFFER];
volatile static u08 i2c_byte_count;

volatile static u16 RH_Code_u16;
volatile static u16 T_Code;

volatile static u32 RH_Si_u32=0;
volatile static s32 T_Si_s16=0;

volatile static u16 RH_Si=1;
volatile static s16 T_Si=10;
volatile static u32 tmp_u32;

volatile u08 was_error_i2c_si7021=NO;
//-----------------------------------------------------------------
//------------------------------------------------
void vTaskSi7021_BMP180(void *param) {
while(1) {
volatile static u08 step=0;
	switch(step) {
	case 0:
		ShedulerI2C(Si7021_rtos);
		step=1;
		vTaskDelay(1000);
		break;
	case 1:
		ShedulerI2C(BMP180_rtos);
		step=0;
		vTaskDelay(1000);
		break;
	}
}}
	//------------------------------------------------
void Si7021_rtos(void) {
status_i2c=BUSY_I2C;

switch (i2c_alg) {
	case 0:
		i2c_byte_count=1;		//сколько байт
		i2c_buf[1]=0;
		i2c_buf[0]=0xF5;
		i2c_slave_addr=Si7021_ADDR;
		i2c_alg=1;
		if(HAL_I2C_Master_Transmit_IT(&hi2c1, i2c_slave_addr, i2c_buf, i2c_byte_count) != HAL_OK){
			ProcessErrorSi7021();
		}
	break;

	case 1://make pause
		vTaskDelay(30);

		i2c_alg=2;
		i2c_slave_addr=Si7021_ADDR;
	  	i2c_byte_count=2;		//сколько байт
	  	if(HAL_I2C_Master_Receive_IT(&hi2c1,  i2c_slave_addr, i2c_buf, i2c_byte_count) != HAL_OK){
	  		ProcessErrorSi7021();
	  	}
	break;

	case 2:
		RH_Code_u16=((i2c_buf[0] << 8) | i2c_buf[1]);
		tmp_u32=RH_Code_u16;
		//вычисляем влажность
		RH_Si_u32=((125*tmp_u32+32768)/65536)-6;

		//считываем температуру
		i2c_alg=3;
		i2c_slave_addr=Si7021_ADDR;
		i2c_byte_count=1;		//сколько байт
		i2c_buf[0]=0xF3;
		if(HAL_I2C_Master_Transmit_IT(&hi2c1, i2c_slave_addr, i2c_buf, i2c_byte_count) != HAL_OK) {
			ProcessErrorSi7021();
		}
	break;

	case 3://make pause
		vTaskDelay(30);

		i2c_alg=4;
		i2c_slave_addr=Si7021_ADDR;
		i2c_byte_count=2;		//сколько байт
		if(HAL_I2C_Master_Receive_IT(&hi2c1,  i2c_slave_addr, i2c_buf, i2c_byte_count) != HAL_OK) {
			ProcessErrorSi7021();
		}
	break;

	case 4:
		T_Code=((i2c_buf[0] << 8) | i2c_buf[1]);
		T_Si_s16=(((175.72*T_Code+32768)/65536)-46.85)*10;

		RH_Si=RH_Si_u32;
		T_Si=T_Si_s16;

		SendTextUartX(" ",1);
		SendTextUartX("H=",0);
		SendIntDigitUartX(RH_Si,0);
		SendTextUartX("%   ",0);
		SendTextUartX("T=",0);
		SendIntDigitUartX(T_Si/10,0);
		SendTextUartX(".",0);
		SendIntDigitUartX(T_Si%10,0);
		SendTextUartX(" C",1);

static char array_tft[10];
		TFTDrawUT32_X(32,51,GREEN,FONE,RH_Si,2,2,array_tft);
		TFTDrawChar(64,51,GREEN,FONE,'%',2);
		TFTDrawUT32_X(32,69,GREEN,FONE,T_Si/10,2,2,array_tft);
		TFTDrawChar(64,69,GREEN,FONE,'.',2);
		TFTDrawUT32_X(80,69,GREEN,FONE,T_Si%10,1,2,array_tft);
		TFTDrawChar(100,69,GREEN,FONE,'C',2);

		status_i2c=END_I2C;
	//	was_error_i2c_si7021=NO;
	break;
}//sw
}//v
//-------------------------------------------------------
u16 Hum_Si7021_get_data(void) {
	return RH_Si;
}
u16 Temp_Si7021_get_data(void) {
	return T_Si;
}
//-------------------------------------------------------
void ProcessErrorSi7021(void){
	i2c_error=1;
	status_i2c=END_I2C;
//	SendTextUartX("was_error_i2c_si7021",1);//optional
}
//------------------------------------------------------------------
//------------------------------------------------------------------

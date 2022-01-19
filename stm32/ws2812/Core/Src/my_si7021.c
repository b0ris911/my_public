#include "my_si7021.h"
#include "i2c.h"

extern u08 i2c_alg;
extern u08 status_i2c;
extern u08 i2c_error;

volatile u08 i2c_SlaveAddress;						// адрес слэйва
u08 i2c_Buffer[i2c_MAXBUFFER];
volatile u08 i2c_ByteCount;

volatile u16 RH_Code_u16;
volatile u16 T_Code;

volatile u32 RH_Si_u32=0;
volatile s32 T_Si_s16=0;

volatile u08 RH_Si=1;	//для использования в других модулях
volatile s16 T_Si=10;	//для использования в других модулях
volatile static u32 tmp_u32;

volatile u08 was_error_i2c_si7021=NO;
//------------------------------------------------
//------------------------------------------------
void Si7021 () {
status_i2c=BUSY_I2C;

if (i2c_error!=0) {
	status_i2c=END_I2C;
	//was_error_i2c_si7021=YES;
	return;
}

switch (i2c_alg) {

	case 0:
		i2c_ByteCount=1;		//сколько байт
		i2c_Buffer[1]=0;
		i2c_Buffer[0]=0xF5;
		i2c_SlaveAddress=0b10000000;
		i2c_alg=1;
		HAL_I2C_Master_Transmit_IT(&hi2c1, i2c_SlaveAddress, i2c_Buffer, i2c_ByteCount);
	break;

	case 1:
		StartGTimer(timer_delay_si7021,30);
		if (ExpGTimer(timer_delay_si7021)) {		//ждем  мс для получения данных
			i2c_alg=2;
			i2c_ByteCount=3;		//сколько байт
			HAL_I2C_Master_Receive_IT(&hi2c1,  i2c_SlaveAddress, i2c_Buffer, 2);
		}
		else status_i2c=FREE_I2C;
	break;

	case 2:
		RH_Code_u16=((i2c_Buffer[0] << 8) + i2c_Buffer[1]);
		tmp_u32=RH_Code_u16;
		//вычисляем влажность
		RH_Si_u32=((125*tmp_u32+32768)/65536)-6;

		//считываем температуру
		i2c_ByteCount=1;		//сколько байт
		i2c_Buffer[0]=0xF3;
		i2c_SlaveAddress=0b10000000;
		i2c_alg=3;
		HAL_I2C_Master_Transmit_IT(&hi2c1, i2c_SlaveAddress, i2c_Buffer, i2c_ByteCount);
	break;

	case 3:
		StartGTimer(timer_delay_si7021,30);
		if (ExpGTimer(timer_delay_si7021)) {		//ждем  мс для получения данных

			i2c_alg=4;
			i2c_ByteCount=2;		//сколько байт
			HAL_I2C_Master_Receive_IT(&hi2c1,  i2c_SlaveAddress, i2c_Buffer, 2);
		}
		else
			status_i2c=FREE_I2C;
	break;

	case 4:
		T_Code=((i2c_Buffer[0] << 8) + i2c_Buffer[1]);
		T_Si_s16=(((175.72*T_Code+32768)/65536)-46.85)*10;

		RH_Si=RH_Si_u32;
		T_Si=T_Si_s16;

		status_i2c=END_I2C;

		TFTDrawUT32(32,50,GREEN,FONE,RH_Si,2,2);
		TFTDrawChar(64,50,GREEN,FONE,'%',2);
		TFTDrawUT32(32,66,GREEN,FONE,T_Si/10,2,2);
		TFTDrawChar(64,66,GREEN,FONE,'.',2);
		TFTDrawUT32(80,66,GREEN,FONE,T_Si%10,1,2);
		TFTDrawChar(100,66,GREEN,FONE,'C',2);

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


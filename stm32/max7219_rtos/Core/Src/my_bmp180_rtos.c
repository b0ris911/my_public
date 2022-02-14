#include "my_bmp180_rtos.h"

extern u08 i2c_alg;
extern u08 status_i2c;
extern u08 i2c_error;
extern TaskHandle_t Handle_vTaskProcessShedulerI2c;


volatile static u08 i2c_slave_addr;						// адрес слэйва
static u08 i2c_buf[i2c_MAXBUFFER];
volatile static u08 i2c_byte_count;

volatile static u08 i2c_mem_addr_size=1;			//размер регистра (в байтах)
volatile static u08 i2c_reg_addr=0;		//адрес регистра


volatile static u16 ac4,ac5,ac6;
//-***************
volatile static s16 ac1,ac2,ac3,b1,b2,mb,mc,md;
volatile static s16 tmp_buff[2];
//-***************
volatile static u32 b4, b7;
volatile static u32 p_msb,p_lsb,p_xlsb;
//-***************
volatile static s32 ut,up,T_BMP_s32=0,P_BMP_s32=0;
volatile static s32 x1, x2, b5, b6, x3, b3, p;
//-***************

volatile static s32 T_BMP;		//для использования в других модулях
volatile static s32 P_BMP;

volatile u08 was_error_i2c_bmp180=NO;
//---------------------------------------
//---------------------------------------
void BMP180_rtos() {
static char array2[10];
status_i2c=BUSY_I2C;

switch (i2c_alg) {
	case 0:	
		i2c_slave_addr=BMP180_ADDR;
		i2c_reg_addr=0xAA;
		i2c_byte_count=22;		//сколько байт
		i2c_alg=10;
		if(HAL_I2C_Mem_Read_IT(&hi2c1, i2c_slave_addr, i2c_reg_addr,i2c_mem_addr_size, i2c_buf,i2c_byte_count) != HAL_OK) {
			ProcessErrorBMP180();
		}
	break;	

	case 10://считали 22 байта коэффициентов
		ac1=i2c_buf[0]<<8 | i2c_buf[1];
		ac2=i2c_buf[2]<<8 | i2c_buf[3];
		ac3=i2c_buf[4]<<8 | i2c_buf[5];
		ac4=i2c_buf[6]<<8 | i2c_buf[7];
		ac5=i2c_buf[8]<<8 | i2c_buf[9];
		ac6=i2c_buf[10]<<8 | i2c_buf[11];
		b1=i2c_buf[12]<<8 | i2c_buf[13];
		b2=i2c_buf[14]<<8 | i2c_buf[15];
		mb=i2c_buf[16]<<8 | i2c_buf[17];
		mc=i2c_buf[18]<<8 | i2c_buf[19];
		md=i2c_buf[20]<<8 | i2c_buf[21];

		//write 0x2e to reg 0xF4
		i2c_slave_addr=BMP180_ADDR;
		i2c_reg_addr=0xF4;		//куда
		i2c_buf[0]=0x2E;		//что
		i2c_byte_count=1;		//сколько байт
		if(HAL_I2C_Mem_Write_IT(&hi2c1, i2c_slave_addr, i2c_reg_addr,i2c_mem_addr_size,i2c_buf,i2c_byte_count) != HAL_OK){
			ProcessErrorBMP180();
		}
		i2c_alg=20;
		break;
//------------
	case 20://pause
		vTaskDelay(5);
		i2c_alg=40;
		i2c_slave_addr=BMP180_ADDR;		//будем читать нескомпенсиров. темп-ру (НКТ)
		i2c_reg_addr=0xF6;		//откуда (2 байта)
		i2c_byte_count=2;		//сколько байт
		if(HAL_I2C_Mem_Read_IT(&hi2c1, i2c_slave_addr, i2c_reg_addr,i2c_mem_addr_size,i2c_buf,i2c_byte_count) != HAL_OK){
			ProcessErrorBMP180();
		}
	break;	

	case 40: //read reg 0xF6 and 0xF7
		ut=i2c_buf[0]<<8 | i2c_buf[1];//вычислили НКТ
//запускаем считывание давления
		i2c_alg=60;
		i2c_slave_addr=BMP180_ADDR;
		i2c_reg_addr=0xF4;
		i2c_buf[0]=0x34 | (OSS<<6);
		i2c_byte_count=1;
		if(HAL_I2C_Mem_Write_IT(&hi2c1, i2c_slave_addr, i2c_reg_addr,i2c_mem_addr_size,i2c_buf,i2c_byte_count) != HAL_OK){
			ProcessErrorBMP180();
		}
	break;
//------------------
	case 60://pause
		vTaskDelay(30);

		i2c_alg=80;//read uncomp pressure
		i2c_slave_addr=BMP180_ADDR;
		i2c_reg_addr=0xF6;//откуда
		i2c_byte_count=3;		//сколько байт
		if(HAL_I2C_Mem_Read_IT(&hi2c1, i2c_slave_addr, i2c_reg_addr,i2c_mem_addr_size,i2c_buf,i2c_byte_count) != HAL_OK){
			ProcessErrorBMP180();
		}
	break;	
//------------------ //сняли давление
	case 80:
		p_msb=i2c_buf[0];
		p_lsb=i2c_buf[1];
		p_xlsb=i2c_buf[2];
	//	CLI
		up=((p_msb << 16) + (p_lsb << 8) + p_xlsb) >> (8-OSS);
	//	SEI
//------------------ //вычисляем температуру
//CLI
	x1 = ((int32_t)ut - (int32_t)ac6) * (int32_t)ac5 >> 15;
	x2 = ((int32_t)mc << 11) / (x1 + md);
	b5 = x1 + x2;
	T_BMP_s32 = (b5 + 8) >> 4;
	T_BMP = T_BMP_s32;	
//SEI

//------------------ //вычисляем давление
//CLI

	b6 = b5 - 4000;
	x1 = (b2 * ((b6 * b6) >> 12)) >> 11;
	x2 = (ac2 * b6) >> 11;
	x3 = x1 + x2;
	b3 = (((((int32_t) ac1) * 4 + x3)<<OSS) + 2)>> 2;
	x1 = (ac3 * b6) >> 13;
	x2 = (b1 * ((b6 * b6) >> 12)) >> 16;
	x3 = ((x1 + x2) + 2) >> 2;
	b4 = (ac4 * (uint32_t) (x3 + 32768)) >> 15;
	b7 = ((uint32_t) (up - b3) * (50000 >> OSS));
	if (b7 < 0x80000000)
		{p = (b7 << 1) / b4;}
	else {p = (b7 / b4) << 1;}
	
	x1 = (p >> 8) * (p >> 8);
	x1 = (x1 * 3038) >> 16;
	x2 = (-7357 * p) >> 16;
	P_BMP_s32 = p + ((x1 + x2 + 3791) >> 4);	
	P_BMP_s32=(P_BMP_s32*1000)/133322;
	P_BMP = P_BMP_s32;		
//SEI
	status_i2c=END_I2C;

	TFTDrawUT32_X(32,107,GREEN,FONE,P_BMP,3,2,array2);
	TFTDrawChar(64,50,GREEN,FONE,'%',2);
	TFTDrawUT32_X(32,125,GREEN,FONE,T_BMP/10,2,2,array2);
	TFTDrawChar(64,125,GREEN,FONE,'.',2);
	TFTDrawUT32_X(80,125,GREEN,FONE,T_BMP%10,1,2,array2);
	TFTDrawChar(100,125,GREEN,FONE,'C',2);
	//		TFTDrawU32(80,92,GREEN,FONE,temp_hum_right,3,2,array2);

	SendTextUartX("   ",1);
	SendTextUartX("P=",0);
	SendIntDigitUartX(P_BMP,0);
	SendTextUartX("mm   ",0);
	SendTextUartX("T=",0);
	SendIntDigitUartX(T_BMP/10,0);
	SendTextUartX(".",0);
	SendIntDigitUartX(T_BMP%10,0);
	SendTextUartX(" C",1);

	//was_error_i2c_bmp180=NO;
	break;

}//switch
}//void
//-------------------------------------------------------
u16 Pres_BMP180_get_data(void) {
	return P_BMP;
}
u16 Temp_BMP180_get_data(void) {
	return T_BMP;
}
//-------------------------------------------------------
//--------------------------------------------------
void ProcessErrorBMP180(void){
	i2c_error=1;
	status_i2c=END_I2C;
//	SendTextUart("was_error_i2c_bmp180",1);//optional
}



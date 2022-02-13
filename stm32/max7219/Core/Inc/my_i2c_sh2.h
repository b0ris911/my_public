#ifndef my_i2c_sh2_h
#define my_i2c_sh2_h

#include "my_head_files.h"


void ShedulerI2C(void (*pfunc)());
void ProcessShedulerI2c();

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
											// Зависит от типа ЕЕПРОМ или другой микросхемы.
	 
	//#define i2c_type_msk	0b00001100	// Маска режима
	//#define i2c_sarp		0b00000000	// Start-Addr_R-Read-Stop  							Это режим простого чтения. Например из слейва или из епрома с текущего адреса
	//#define i2c_sawp		0b00000100	// Start-Addr_W-Write-Stop 							Это режим простой записи. В том числе и запись с адресом страницы.
	//#define i2c_sawsarp		0b00001000	// Start-Addr_W-WrPageAdr-rStart-Addr_R-Read-Stop 	Это режим с предварительной записью текущего адреса страницы
//	#define i2c_sawwp		0b00010000  // Start_Addr_W-Write_Reg-Write-Stop	

	//#define i2c_r			0b00000000	// Start-Addr_R-Read-Stop  							Это режим простого чтения. Например из слейва или из епрома с текущего адреса
	//#define i2c_w			0b00000100	// Start-Addr_W-Write-Stop 							Это режим простой записи. В том числе и запись с адресом страницы.
	//#define i2c_wr			0b00001000	// Start-Addr_W-WrPageAdr-rStart-Addr_R-Read-Stop 	Это режим с предварительной записью текущего адреса страницы
	 
	//#define i2c_ERR_MSK	0b00110011	// Маска кода ошибок
	//#define i2c_ERR_NO	0b00000000	// All Right! 						-- Все окей, передача успешна.
	#define i2c_ERR_20_NA	1//0b00010000	// Device No Answer 				-- Слейв не отвечает. Т.к. либо занят, либо его нет на линии.
	//#define i2c_ERR_LP	0b00100000	// Low Priority 					-- нас перехватили собственным адресом, либо мы проиграли арбитраж
	#define i2c_ERR_30_NK	2//0b00000010	// Received NACK. End Transmittion. -- Был получен NACK. Бывает и так.
	//#define i2c_ERR_BF	0b00000001	// BUS FAIL 						-- Автобус сломался. И этим все сказано. Можно попробовать сделать переинициализацию шины
	 #define i2c_ERR_48_NA	3



	//#define i2c_Interrupted		0b10000000		// Transmiting Interrupted		Битмаска установки флага занятости
	//#define i2c_NoInterrupted 	0b01111111  	// Transmiting No Interrupted	Битмаска снятия флага занятости
	 
	//#define i2c_Busy		0b01000000  	// Trans is Busy				Битмаска флага "Передатчик занят, руками не трогать".
	//#define i2c_Free		0b10111111  	// Trans is Free				Битмаска снятия флага занятости.
	 
	 
//	#define MACRO_i2c_WhatDo_MasterOut 		(MasterOutFunc)();		// Макросы для режима выхода. Пока тут функция, но может быть что угодно
//	#define MACRO_i2c_WhatDo_SlaveOut   	(SlaveOutFunc)();
//	#define MACRO_i2c_WhatDo_ErrorOut   	(ErrorOutFunc)();
	 
	 
	 
//	typedef void (*IIC_F)(void);		// Тип указателя на функцию
	 
//	extern IIC_F MasterOutFunc;		// Подробности в сишнике.
//	extern IIC_F SlaveOutFunc;
//	extern IIC_F ErrorOutFunc;
	 
	 
//	extern unsigned char i2c_InBuff[i2c_MasterBytesRX];
//	extern unsigned char i2c_OutBuff[i2c_MasterBytesTX];
	 
//	extern unsigned char i2c_SlaveIndex;
	 
	 
//	extern unsigned char i2c_ByteCount;
	 
//	extern unsigned char i2c_SlaveAddress;
	//extern unsigned char i2c_PageAddress[i2c_MaxPageAddrLgth];
	 
	//extern unsigned char i2c_PageAddrIndex;
	//extern unsigned char i2c_PageAddrCount;
	 
	 
//	extern void Init_i2c(void);
//	extern void Init_Slave_i2c(IIC_F Addr);
	 
	 
//	extern unsigned char 	WorkLog[100];
//	extern unsigned char	WorkIndex;
	 
	#endif


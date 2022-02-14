#include "my_spi.h"

static volatile u32 tmp=0;

//---------------------------------
//---------------------------------

inline void  TFTData(u16 data) {
	CLI
	while(!(SPI_MODULE->SR & SPI_SR_TXE));
	*(u08*)&(SPI_MODULE->DR) = data>>8;
	tmp++;tmp++;
    while(!(SPI_MODULE->SR & SPI_SR_TXE));
    *(u08*)&(SPI_MODULE->DR) = data;
    tmp++;tmp++;
	while((SPI_MODULE->SR & SPI_SR_BSY));
	SEI
}
//------------------------------------------
inline void TFTCmd(u08 cmd) {
	while((SPI_MODULE->SR & SPI_SR_BSY));
	CB(DC_GPIO_Port,DC_Pin);
	*(u08*)&(SPI_MODULE->DR) = cmd;
	tmp++;tmp++;tmp++;
    while((SPI_MODULE->SR & SPI_SR_BSY));
    SB(DC_GPIO_Port,DC_Pin);
}
//---------------------------------
inline void TFTPar(u08 parameter) {
	while(!(SPI_MODULE->SR & SPI_SR_TXE));
	*(u08*)&(SPI_MODULE->DR) = parameter;
	tmp++;
}

//-----------------------------------
/*
При необходимости смены вида передаваемых данных (по линии DC),
или отмены выбора дисплея (линией CS) предварительно нужно проверять
флаг BSY для того чтобы убедиться
что физическая передача данных/команды завершилась.
В остальных случаях нужно использовать проверку
флага TXE ПЕРЕД загрузкой значения в SPI_DR:
*/

/*!
@brief  Send Command handles complete sending of commands and data
@param   commandByte       The Command Byte
@param   dataBytes         A pointer to the Data bytes to send
@param   numDataBytes      The number of bytes we should send
*/
void TFTSendCommand(u08 commandByte, u08 *dataBytes, u08 numDataBytes) {
	TFTCmd(commandByte); // Send the command byte
	for (int i = 0; i < numDataBytes; i++) {
		TFTPar(*dataBytes); // Send the data bytes
		dataBytes++;
    }
}


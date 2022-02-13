#ifndef MY_SPI_TFT_H_
#define MY_SPI_TFT_H_

#include "my_head_files.h"
//#include "my_ST7735_rtos.h"
//#include "my_func.h"

#define SPI_MODULE	SPI3

void TFTCmd(u08 cmd);
void TFTPar(u08 parameter);
void TFTData(u16 data);


#endif /* MY_SPI_H_ */

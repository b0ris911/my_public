#ifndef MY_SPI_TOUCH_H_
#define MY_SPI_TOUCH_H_

#include "my_head_files.h"

#define SPI_MODULE_TOUCH		SPI1
#define	chy 	0x90         //координатные оси дисплея и тачскрина поменяны местами(там где у дисплея Х у тачсрина Y)
#define	chx 	0xD0        //за основу возьмём оси дисплея

void ProcessXPT2046(void);
void InitXPT2046(void);
void Get_Touch_xy( volatile u16 *x_touch,volatile u16 *y_touch);
u08 Touch_Spi_Master_Transmit(u08 out_data);
void Process2D(void);


#endif

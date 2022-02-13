#include "my_spi_touch.h"

static volatile u32 tmp=0;
static volatile u16 touch_x_data=0,touch_y_data=0;
static volatile u16 brush_color=YELLOW;

void Process2D(void){
	TFTFillRectangle(200,0,40,40,ORANGE);
	TFTFillRectangle(0,270,50,50,RED);
	TFTFillRectangle(51,270,50,50,GREEN);
	TFTFillRectangle(101,270,50,50,BLUE);
	TFTFillRectangle(151,270,50,50,BLACK);
	TFTFillRectangle(201,270,50,50,WHITE);
	FirstScreen();
}
//-------------------------------------------------------
void ProcessXPT2046(void){
	  StartGTimer(timer_get_data_xpt2046,5);
	  if(ExpGTimer(timer_get_data_xpt2046)){
		  if(BIS(TOUCH_TRIG_GPIO_Port,TOUCH_TRIG_Pin))
			  return;

		  Get_Touch_xy(&touch_x_data,&touch_y_data);
		  touch_x_data=(touch_x_data-200)/16;
		  touch_y_data=(touch_y_data-200)/12;
		  if(touch_x_data>239) touch_x_data=239;
		  if(touch_y_data>319) touch_y_data=319;
//		  SendTextUart("x= ",0);
//		  SendTrimDigitUart(touch_x_data,5,0);
//		  SendTextUart("    y= ",0);
//		  SendTrimDigitUart(touch_y_data,5,1);
/*		  if((touch_x_data>0)&&(touch_x_data<51)&&(touch_y_data<51))
			  brush_color=RED;
		  if((touch_x_data>50)&&(touch_x_data<101)&&(touch_y_data<51))
			  brush_color=GREEN;
		  if((touch_x_data>100)&&(touch_x_data<151)&&(touch_y_data<51))
			  brush_color=BLUE;
		  if((touch_x_data>150)&&(touch_x_data<201)&&(touch_y_data<51))
			  brush_color=YELLOW;
		  if((touch_x_data>200)&&(touch_y_data<51))
			  brush_color=WHITE;
*/
		  if((touch_x_data>200)&&(touch_y_data<40)){
			  TFTFillScreen(FONE);
			  Process2D();
		  }

		  if((touch_x_data>0)&&(touch_x_data<51)&&(touch_y_data>270)){
			  TFTFillRectangle(0,185,240,320,RED);
			  Process2D();
		  }
		  if((touch_x_data>50)&&(touch_x_data<101)&&(touch_y_data>270)){
			  TFTFillRectangle(0,185,240,320,GREEN);
			  Process2D();
		  }
		  if((touch_x_data>100)&&(touch_x_data<151)&&(touch_y_data>270)){
			  TFTFillRectangle(0,185,240,320,BLUE);
			  Process2D();
		  }
		  if((touch_x_data>150)&&(touch_x_data<201)&&(touch_y_data>270)){
			  TFTFillRectangle(0,185,240,320,BLACK);
			  Process2D();
		  }
		  if((touch_x_data>200)&&(touch_y_data>270)){
			  TFTFillRectangle(0,185,240,320,WHITE);
			  Process2D();
		  }

		  TFTFillCircle(touch_x_data,touch_y_data,2,brush_color);
	  }
}
//-------------------------------------------------------
void InitXPT2046(void) {
	Touch_Spi_Master_Transmit(0X80);
	Touch_Spi_Master_Transmit(0X00);
	Touch_Spi_Master_Transmit(0X00);
}
//-------------------------------------------------------
void Get_Touch_xy( volatile u16 *x_touch,volatile u16 *y_touch) {
		volatile u16 touch_x = 0;
		volatile u16 touch_y = 0;
CLI
		Touch_Spi_Master_Transmit(chx);  //отправляем запрос координаты X

		Touch_Spi_Master_Transmit(0X00); //получаем старшие 8 бит
		touch_x = SPI_MODULE_TOUCH->DR;
		touch_x <<= 8;

		Touch_Spi_Master_Transmit(0X00); //получаем младшие 4 бита
		touch_x |= SPI_MODULE_TOUCH->DR;
		touch_x >>= 3;

		_delay_us(100);
		Touch_Spi_Master_Transmit(chy);  //отправляем запрос координаты Y

		Touch_Spi_Master_Transmit(0X00);  //получаем старшие 8 бит
		touch_y = SPI_MODULE_TOUCH->DR;
		touch_y <<= 8;

		Touch_Spi_Master_Transmit(0X00);  ////получаем младшие 4 бита
		touch_y |= SPI_MODULE_TOUCH->DR;
		touch_y >>= 3;
SEI

		*x_touch = touch_x;
		*y_touch = touch_y;
}
//-------------------------------------------------------
u08 Touch_Spi_Master_Transmit(u08 out_data){
	while((SPI_MODULE_TOUCH->SR & SPI_SR_BSY));
	//CB(CS_TOUCH_GPIO_Port,CS_TOUCH_Pin);
	*(u08*)&(SPI_MODULE_TOUCH->DR) = out_data;
	tmp++;tmp++;tmp++;
    while((SPI_MODULE_TOUCH->SR & SPI_SR_BSY));
    //SB(CS_TOUCH_GPIO_Port,CS_TOUCH_Pin);
    return SPI_MODULE_TOUCH->DR; //возвращаем принятый байт
}

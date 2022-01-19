#include "my_ST7735.h"

extern u08 fontx[][8];
extern char out[MAX_SIZE];

volatile u08 flag_orient=VERT;
volatile u16 Max_X=0;
volatile u16 Max_Y=0;

volatile static u08 var_MV=1;
volatile static u08 var_MX=1;
volatile static u08 var_MY=1;
volatile u16 TFT_Width=0;
volatile u16 TFT_Height=0;

volatile u16 TFT_Center_X=0;
volatile u16 TFT_Center_Y=0;
//----------------------------------------------------------
/*
void SetupSt7735ForDMA() {
	TFTCmd(CASET);
    //границы прямоугольника совпадают с границами дисплея
    TFTData(0x00);	TFTData(TFT_Width - 1);
  	TFTCmd(RASET);
    TFTData(0x00);	TFTData(TFT_Height - 1);
  	TFTCmd(RAMWR);
}
*/
//----------------------------------------------------------
//----------------------------------------------------------
//----------------------------------------------------------
//----------------------------------------------------------
void  TFTDrawHorizontalLine( u16 x, u16 y, u16 length,u16 color) {
	CB(CS_ST7735_PORT,CS_ST7735_PIN);

	TFTSetColumn(x,x + length);
	TFTSetPage(y,y);
	TFTCmd(0x2c);
	for(int i=0; i<length; i++)
		TFTData(color);

	SB(CS_ST7735_PORT,CS_ST7735_PIN);
}
//--------------------------------------------------
void TFTDrawVerticalLine( u16 x, u16 y, u16 length,u16 color) {
	CB(CS_ST7735_PORT,CS_ST7735_PIN);

	TFTSetColumn(x,x);
	TFTSetPage(y,y+length);
	TFTCmd(0x2c);
	for(int i=0; i<length; i++)
		TFTData(color);

	SB(CS_ST7735_PORT,CS_ST7735_PIN);
}
//--------------------------------------------------
void TFTDrawTriangle( u16 x1, u16 y1, u16 x2, u16 y2, u16 x3, u16 y3, u16 color) {
	CB(CS_ST7735_PORT,CS_ST7735_PIN);

	TFTDrawLine( x1, y1, x2, y2, color);
	TFTDrawLine( x2, y2, x3, y3, color);
	TFTDrawLine( x3, y3, x1, y1, color);

	SB(CS_ST7735_PORT,CS_ST7735_PIN);
}
//--------------------------------------------------
void TFTDrawRectangle(u16 x, u16 y, u16 length, u16 width,u16 color) {
	CB(CS_ST7735_PORT,CS_ST7735_PIN);

	TFTDrawHorizontalLine(x, y, length, color);
	TFTDrawHorizontalLine(x, y + width-1, length, color);
	TFTDrawVerticalLine(x, y, width,color);
	TFTDrawVerticalLine(x + length -1, y, width,color);

	SB(CS_ST7735_PORT,CS_ST7735_PIN);
}
//--------------------------------------------------
void TFTDrawUT32(u16 x, u16 y, u16 color, u16 fone, u32 numeric, u08 digits,u08 size) {
	CB(CS_ST7735_PORT,CS_ST7735_PIN);

	TrimConvert(numeric,digits);
	TFTDrawString(x,y,color,fone,out,size);

	SB(CS_ST7735_PORT,CS_ST7735_PIN);
}
//--------------------------------------------------
void TFTDrawST32(u16 x, u16 y, u16 color, u16 fone, s32 numeric, u08 digits,u08 size) {
	CB(CS_ST7735_PORT,CS_ST7735_PIN);

	STrimConvert(numeric,digits);
	TFTDrawString(x,y,color,fone,out,size);

	SB(CS_ST7735_PORT,CS_ST7735_PIN);
}
//--------------------------------------------------
void TFTDrawU32(u16 x, u16 y, u16 color, u16 fone, u32 numeric, u08 digits,u08 size) {
	CB(CS_ST7735_PORT,CS_ST7735_PIN);

	Convert(numeric,digits);
	TFTDrawString(x,y,color,fone,out,size);

	SB(CS_ST7735_PORT,CS_ST7735_PIN);
}
//--------------------------------------------------
void TFTDrawCircle(u16 pos_x, u16 pos_y, u08 r,u16 color) {
	CB(CS_ST7735_PORT,CS_ST7735_PIN);

	int x = -r, y = 0, err = 2-2*r, e2;
	do {
		TFTDrawPixel(pos_x-x, pos_y+y,color);
		TFTDrawPixel(pos_x+x, pos_y+y,color);
		TFTDrawPixel(pos_x+x, pos_y-y,color);
		TFTDrawPixel(pos_x-x, pos_y-y,color);
		e2 = err;
		if (e2 <= y) {
			err += ++y*2+1;
			if (-x == y && e2 <= x) e2 = 0;
		}
		if (e2 > x) err += ++x*2+1;
	} while (x <= 0);

	SB(CS_ST7735_PORT,CS_ST7735_PIN);
}
//--------------------------------------------------
void TFTDrawString(u16 x, u16 y, u16 color,u16 fone, const char *string, u08 size) {
	CB(CS_ST7735_PORT,CS_ST7735_PIN);

	while(*string) {
		if((x + FONT_X) > Max_X) {
			x = 1;
			y = y + FONT_X*size;
		}
		TFTDrawChar(x, y, color, fone,*string, size);
		x += FONT_X*size;
		string++;
	}

	SB(CS_ST7735_PORT,CS_ST7735_PIN);
}
//----------------------------------------------------------
//u08 fontx[][8]={{0x04,0x04,0x04,0x04,0x00,0x04,0x00,0x00}};
void TFTDrawChar(u16 x, u16 y, u16 color, u16 fone, u08 ascii, u08 size) {
	CB(CS_ST7735_PORT,CS_ST7735_PIN);

	for (int i = 0; i < FONT_Y; i++ ) {
		for(u08 f = 0; f < FONT_X; f++) {
			if(((fontx[ascii-0x20][i])>>(7-f))&0x01) {
				 TFTFillRectangle(x+f*size, y+i*size, size, size, color);
			}
			else {	
				 TFTFillRectangle(x+f*size, y+i*size, size, size, fone);
			}
		}
	}

	SB(CS_ST7735_PORT,CS_ST7735_PIN);
}
//----------------------------------------------------------
u16 constrain(u16 a, u16 b, u16 c) {
	if (a < b)	{
		return b;
	}
	if (c < a)	{
		return c;
	}
	else return a;
}
//-----------------------------------------------------
//x & y - это координаты левого верхнего угла прямоугольника
void TFTFillRectangle(u16 x, u16 y, u16 length, u16 width, u16 color) {
	CB(CS_ST7735_PORT,CS_ST7735_PIN);

	if(length  && width) {
		TFTFillScreen(x, x+length - 1, y, y+width - 1, color);
	}

	SB(CS_ST7735_PORT,CS_ST7735_PIN);
}
//------------------------------------------------------
void TFTFillScreen(u16 x_left, u16 x_right, u16 y_up, u16 y_down, u16 color) {
	CB(CS_ST7735_PORT,CS_ST7735_PIN);

	unsigned long  xy=0;
	unsigned long i=0;
	if(x_left > x_right) {	
		x_left = x_left^x_right;       //если координата левого края больше
		x_right = x_left^x_right;      //координаты правого края они поменяются
		x_left = x_left^x_right;       //местами, было x_left = 5 x_right = 3
					       //стало x_left = 3 x_right = 5
	}
	if(y_up > y_down) {
		y_up = y_up^y_down;		//то же самое для оси y
		y_down = y_up^y_down;		//название этой операции
		y_up = y_up^y_down;		//"swap без временной переменной"
	}
	//контролируем, что бы передаваемые в функцию координаты
	//входили в область допустимых значений
	x_left = constrain(x_left, MIN_X,Max_X);
	x_right = constrain(x_right, MIN_X,Max_X);
	y_up = constrain(y_up, MIN_Y,Max_Y);
	y_down = constrain(y_down, MIN_Y,Max_Y);

	xy = (x_right - x_left+1);		//рассчитываем количество точек
	xy = xy*(y_down - y_up+1);		//которое надо закрасить

	TFTSetColumn(x_left,x_right);	        //задаём рабочую область по x
	TFTSetPage(y_up, y_down);		//задаём рабочую область по y
	TFTCmd(0x2c);			//будем писать в видео ОЗУ
	
	for(i=0; i < xy; i++) {
		TFTData(color);	//передаём кодировку цвета
	}

	SB(CS_ST7735_PORT,CS_ST7735_PIN);
}
//--------------------------------------------------
void TFTDrawLine( u16 x0,u16 y0,u16 x1, u16 y1,u16 color) {
	CB(CS_ST7735_PORT,CS_ST7735_PIN);

	int x = x1-x0;
	int y = y1-y0;
	int dx = abs(x), sx = x0<x1 ? 1 : -1;
	int dy = -abs(y), sy = y0<y1 ? 1 : -1;
	int err = dx+dy, e2;
	for (;;) {
		TFTDrawPixel(x0,y0,color);
		e2 = 2*err;
		if (e2 >= dy) {
			if (x0 == x1) break;
			err += dy; x0 += sx;
		}
		if (e2 <= dx) {
			if (y0 == y1) break;
			err += dx; y0 += sy;
		}
	}

	SB(CS_ST7735_PORT,CS_ST7735_PIN);
}
//----------------------------------------------------------
/*
void TFTFill(u16 color) {
	TFTSetColumn(0,3);
	TFTSetPage(0,5);
  	TFTCmd(RAMWR);
	for (u32 i=0;i<20;i++) {		
		TFTData(color);
	}
}
*/
//----------------------------------------------------------
void St7735FillScreen(u16 color) {
	CB(CS_ST7735_PORT,CS_ST7735_PIN);

	TFTCmd(CASET); 
    //границы прямоугольника совпадают с границами дисплея
    TFTData(0x00);	TFTData(TFT_Width - 1);
  	TFTCmd(RASET); 
    TFTData(0x00);	TFTData(TFT_Height - 1);
  	TFTCmd(RAMWR);
    //количество пикселей, т.е. площади прямоугольника и дисплея, также совпадают
	for(u16 counter = 0; counter < (TFT_Width*TFT_Height); counter++) {      
    	TFTData(color);   	
	}
	SB(CS_ST7735_PORT,CS_ST7735_PIN);
}    
//----------------------------------------------------------
/*ф-ция ограничивает координаты  рабочей области по оси Х*/
void TFTSetColumn(u16 start_column,u16 end_colunm) {
	TFTCmd(CASET);                                           
	TFTData(start_column);
	TFTData(end_colunm);
}
//----------------------------------------------------------
/*ф-ция ограничивает координаты  рабочей области по оси Y*/
void TFTSetPage(u16 start_page,u16 end_page) {
	TFTCmd(RASET);                                                      
	TFTData(start_page);
	TFTData(end_page);
}
//----------------------------------------------------------
/*ф-ция ограничивает координаты  рабочей области*/
void TFTSetXY(u16 x, u16 y) {
	TFTSetColumn(x, x);
	TFTSetPage(y, y);
}
//----------------------------------------------------------
/*ф-ция отрисовывает пиксель по заданным координатам*/
void TFTDrawPixel(u16 x, u16 y,u16 color) {
	CB(CS_ST7735_PORT,CS_ST7735_PIN);
	TFTSetXY(x, y);
	TFTCmd(RAMWR);
	TFTData(color);
	while((SPI3->SR & SPI_SR_BSY));
	SB(CS_ST7735_PORT,CS_ST7735_PIN);
}
//----------------------------------------------------------
void ST7735Init() {
	CB(CS_ST7735_PORT,CS_ST7735_PIN);

	//PORT_CS &= ~(1<<CS);
	CB(RST_GPIO_Port,RST_Pin);
//	GPIOB->BSRR |= (u32)RST_Pin<<16u;
	_delay_ms(150);
	SB(RST_GPIO_Port,RST_Pin);
	_delay_ms(150);
	//GPIOB->BSRR |= RST_Pin;

	if(flag_orient) {
		TFT_Width=ST7735_WIDTH;
		TFT_Height=ST7735_HEIGHT;
	}
	else {
		TFT_Width=ST7735_HEIGHT;
		TFT_Height=ST7735_WIDTH;
	}		
	TFT_Center_X=TFT_Width/2;
	TFT_Center_Y=TFT_Height/2;
	Max_X=TFT_Width-1;
	Max_Y=TFT_Height-1;

	TFTCmd(SWRESET);
	_delay_ms(150);
	TFTCmd(SLPOUT);

	_delay_ms(150);

	TFTCmd(COLMOD);  // режим цвета:
	TFTPar(0x05); //16 бит
	
	TFTCmd(MADCTL);  // направление вывода изображения:
	
	if(flag_orient) {
		TFTPar((0<<7)|(0<<6)|(0<<5)|(ML<<4)|(RGB<<3)|(MH<<2)); //MY,MX,MV
	}
	else {
		TFTPar((1<<7)|(0<<6)|(1<<5)|(ML<<4)|(RGB<<3)|(MH<<2)); //MY,MX,MV
	}		
	 
	TFTCmd(DISPON);  // включаем изображение
	_delay_ms(10);

	SB(CS_ST7735_PORT,CS_ST7735_PIN);
}
//----------------------------------------------------------
void ST7735ReInit() {
	CB(CS_ST7735_PORT,CS_ST7735_PIN);

	if(flag_orient==VERT) {
		TFT_Width=ST7735_WIDTH;
		TFT_Height=ST7735_HEIGHT;
	}
	else {
		TFT_Width=ST7735_HEIGHT;
		TFT_Height=ST7735_WIDTH;
	}		

	TFT_Center_X=TFT_Width/2;
	TFT_Center_Y=TFT_Height/2;
	Max_X=TFT_Width-1;
	Max_Y=TFT_Height-1;

//	TFTCmd(SWRESET);
//	_delay_ms(150);
//	TFTCmd(SLPOUT);

//	_delay_ms(150);

	TFTCmd(COLMOD);  // режим цвета:
	TFTPar(0x05); //16 бит
	
	TFTCmd(MADCTL);  // направление вывода изображения:
	if(flag_orient==VERT) {
		TFTPar((0<<7)|(0<<6)|(0<<5)|(ML<<4)|(RGB<<3)|(MH<<2)); //MY,MX,MV
	}
	else {
		TFTPar((1<<7)|(0<<6)|(1<<5)|(ML<<4)|(RGB<<3)|(MH<<2)); //MY,MX,MV
	}		
	 
//	TFTCmd(DISPON);  // включаем изображение

	SB(CS_ST7735_PORT,CS_ST7735_PIN);
}

#include "my_ili9341.h"
//#include "spi.h" //???

extern u08 fontx[][8];
extern char out[MAX_SIZE];

//volatile u08 flag_orient=VERT;
volatile u16 Max_X=0;
volatile u16 Max_Y=0;

volatile static u08 var_MV=1;
volatile static u08 var_MX=1;
volatile static u08 var_MY=1;
volatile u16 TFT_Width=240;
volatile u16 TFT_Height=320;

volatile u16 TFT_Center_X=0;
volatile u16 TFT_Center_Y=0;
static volatile u08 tft_orientation=2;
//-------------------FOR DMA--------------------------------
extern s08 tablesin2[];
extern s08 tablecos2[];

//------- CHANGE ORIENTATION !!! -------------------
//u08 buff2[ST7735_HEIGHT][ST7735_WIDTH*2]={0};//vert
//u08 buff2[ST7735_WIDTH][ST7735_HEIGHT*2]={0};//horis
//--------------------------------------------------
//----------------------------------------
/*
void DrawFatLineX(u16 x,u16 y,u16 length,u08 thickness,u16 color) {
u32 n=0;
	TFTSetColumn(x,x+length);
	TFTSetPage(y,y+thickness);
	TFTCmd(0x2c);
	n=length*thickness;
	for(u32 i=0;i<n;i++) {
		TFTData(color);
	}
}
*/
//--------------------------------------------------
void TFTFillCircle(u16 pos_x, u16 pos_y, u08 r,u16 color) {
	int x = -r, y = 0, err = 2-2*r, e2;
	do {
		TFTDrawVerticalLine(pos_x-x, pos_y-y, 2*y, color);
		TFTDrawVerticalLine(pos_x+x, pos_y-y, 2*y, color);
		e2 = err;
		if (e2 <= y) {
			err += ++y*2+1;
			if (-x == y && e2 <= x) e2 = 0;
		}
		if (e2 > x) err += ++x*2+1;
	} while (x <= 0);
}

//--------------------------------------------------
void  TFTDrawHorizontalLine( u16 x, u16 y, u16 length,u16 color) {
	CB(CS_TFT_PORT,CS_TFT_PIN);

	TFTSetColumn(x,x + length);
	TFTSetPage(y,y);
	TFTCmd(0x2c);
	for(int i=0; i<length; i++)
		TFTData(color);

	SB(CS_TFT_PORT,CS_TFT_PIN);
}
//--------------------------------------------------
void TFTDrawVerticalLine( u16 x, u16 y, u16 length,u16 color) {
	CB(CS_TFT_PORT,CS_TFT_PIN);

	TFTSetColumn(x,x);
	TFTSetPage(y,y+length);
	TFTCmd(0x2c);
	for(int i=0; i<length; i++)
		TFTData(color);

	SB(CS_TFT_PORT,CS_TFT_PIN);
}
//--------------------------------------------------
void TFTDrawTriangle( u16 x1, u16 y1, u16 x2, u16 y2, u16 x3, u16 y3, u16 color) {
	CB(CS_TFT_PORT,CS_TFT_PIN);

	TFTDrawLine( x1, y1, x2, y2, color);
	TFTDrawLine( x2, y2, x3, y3, color);
	TFTDrawLine( x3, y3, x1, y1, color);

	SB(CS_TFT_PORT,CS_TFT_PIN);
}
//--------------------------------------------------
void TFTDrawRectangle(u16 x, u16 y, u16 length, u16 width,u16 color) {
	CB(CS_TFT_PORT,CS_TFT_PIN);

	TFTDrawHorizontalLine(x, y, length, color);
	TFTDrawHorizontalLine(x, y + width-1, length, color);
	TFTDrawVerticalLine(x, y, width,color);
	TFTDrawVerticalLine(x + length -1, y, width,color);

	SB(CS_TFT_PORT,CS_TFT_PIN);
}
//--------------------------------------------------
void TFTDrawUT32(u16 x, u16 y, u16 color, u16 fone, u32 numeric, u08 digits,u08 size) {
	CB(CS_TFT_PORT,CS_TFT_PIN);

	TrimConvert(numeric,digits);
	TFTDrawString(x,y,color,fone,out,size);

	SB(CS_TFT_PORT,CS_TFT_PIN);
}
//--------------------------------------------------
void TFTDrawST32(u16 x, u16 y, u16 color, u16 fone, u32 numeric, u08 digits,u08 size) {
	CB(CS_TFT_PORT,CS_TFT_PIN);

	STrimConvert(numeric,digits);
	TFTDrawString(x,y,color,fone,out,size);

	SB(CS_TFT_PORT,CS_TFT_PIN);
}
//--------------------------------------------------
void TFTDrawU32(u16 x, u16 y, u16 color, u16 fone, u32 numeric, u08 digits,u08 size) {
	CB(CS_TFT_PORT,CS_TFT_PIN);

	Convert(numeric,digits);
	TFTDrawString(x,y,color,fone,out,size);

	SB(CS_TFT_PORT,CS_TFT_PIN);
}
//--------------------------------------------------
void TFTDrawCircle(u16 pos_x, u16 pos_y, u08 r,u16 color) {
	CB(CS_TFT_PORT,CS_TFT_PIN);

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

	SB(CS_TFT_PORT,CS_TFT_PIN);
}
//--------------------------------------------------
void TFTDrawString(u16 x, u16 y, u16 color,u16 fone, const char *string, u08 size) {
	CB(CS_TFT_PORT,CS_TFT_PIN);

	while(*string) {
		if((x + FONT_X) > Max_X) {
			x = 1;
			y = y + FONT_X*size;
		}
		TFTDrawChar(x, y, color, fone,*string, size);
		x += FONT_X*size;
		string++;
	}

	SB(CS_TFT_PORT,CS_TFT_PIN);
}
//----------------------------------------------------------
void TFTDrawChar(u16 x, u16 y, u16 color, u16 fone, u08 ascii, u08 size) {
	CB(CS_TFT_PORT,CS_TFT_PIN);

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

	SB(CS_TFT_PORT,CS_TFT_PIN);
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
	CB(CS_TFT_PORT,CS_TFT_PIN);

	if(length  && width) {
		TFTFillScreen2(x, x+length - 1, y, y+width - 1, color);
	}

	SB(CS_TFT_PORT,CS_TFT_PIN);
}
//------------------------------------------------------
void TFTFillScreen2(u16 x_left, u16 x_right, u16 y_up, u16 y_down, u16 color) {
	CB(CS_TFT_PORT,CS_TFT_PIN);

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

	SB(CS_TFT_PORT,CS_TFT_PIN);
}
//--------------------------------------------------
void TFTDrawLine( u16 x0,u16 y0,u16 x1, u16 y1,u16 color) {
	CB(CS_TFT_PORT,CS_TFT_PIN);

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

	SB(CS_TFT_PORT,CS_TFT_PIN);
}
//----------------------------------------------------------
/*void TFTFill(u16 color) {
	TFTSetColumn(0,3);
	TFTSetPage(0,5);
  	TFTCmd(RAMWR);
	for (u32 i=0;i<20;i++) {
		TFTData(color);
	}
}*/
//----------------------------------------
void DrawTFT(void) {
	TFTSetColumn(0,240);
	TFTSetPage(0,320);
	TFTCmd(0x2c);
	for (u32 i=0;i<76000;i++) {
		TFTData(0);
	}
}
//----------------------------------------------------------
void TFTFillScreen(u16 color) {
	CB(CS_TFT_PORT,CS_TFT_PIN);

	TFTCmd(0x2A);
    //границы прямоугольника совпадают с границами дисплея
    //TFTData(0x00);	TFTData(TFT_Width - 1);
    TFTData(0x00);	TFTData(Max_X - 1);
  	TFTCmd(0x2B);
    //TFTData(0x00);	TFTData(TFT_Height - 1);
    TFTData(0x00);	TFTData(Max_Y - 1);
  	TFTCmd(0x2C);
    //количество пикселей, т.е. площади прямоугольника и дисплея, также совпадают
	for(u32 counter = 0; counter < (TFT_Width*TFT_Height); counter++) {
    	TFTData(color);
	}
	SB(CS_TFT_PORT,CS_TFT_PIN);
}
//----------------------------------------------------------
/*ф-ция ограничивает координаты  рабочей области по оси Х*/
void TFTSetColumn(u16 start_column,u16 end_colunm) {
	TFTCmd(0x2A);
	TFTData(start_column);
	TFTData(end_colunm);
}
//----------------------------------------------------------
/*ф-ция ограничивает координаты  рабочей области по оси Y*/
void TFTSetPage(u16 start_page,u16 end_page) {
	TFTCmd(0x2B);
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
	CB(CS_TFT_PORT,CS_TFT_PIN);
	TFTSetXY(x, y);
	TFTCmd(0x2c);
	TFTData(color);
	SB(CS_TFT_PORT,CS_TFT_PIN);
}
//-------------------------------------------------------------
void TFTSetOrientation(u08 orient) {
	TFTCmd(0x36);
	switch (orient)
	{
		case 0: TFTPar(0x48);
				break;
		case 1: TFTPar(0x28);
				break;
		case 2: TFTPar(0x88);
				break;
		case 3: TFTPar(0xE8);
				break;
	}
	if (orient == 0 || orient == 2)
	{
		Max_X = 239;
		Max_Y = 319;
	}
	else
	{
		Max_X = 319;
		Max_Y = 239;
	}
}
//------------------------------------------

void InitILI9341(void){
	CB(CS_TFT_PORT,CS_TFT_PIN);
	CB(RST_GPIO_Port,RST_Pin);
	_delay_ms(20);
	SB(RST_GPIO_Port,RST_Pin);
	_delay_ms(150);
	TFTCmd(0x01);
	_delay_ms(150);
	TFTCmd(0xEF);
	TFTPar(0x03);
	TFTPar(0x0);
	TFTPar(0x02);

	TFTCmd(0xCF);
	TFTPar(0x0);
	TFTPar(0xC1);
	TFTPar(0x30);

	TFTCmd(0xED);
	TFTPar(0x64);
	TFTPar(0x03);
	TFTPar(0x12);
	TFTPar(0x81);

	TFTCmd(0xE8);
	TFTPar(0x85);
	TFTPar(0x0);
	TFTPar(0x78);

	TFTCmd(0xCB);
	TFTPar(0x39);
	TFTPar(0x2C);
	TFTPar(0x0);
	TFTPar(0x34);
	TFTPar(0x02);

	TFTCmd(0xF7);
	TFTPar(0x20);

	TFTCmd(0xEA);
	TFTPar(0x0);
	TFTPar(0x0);

	TFTCmd(0xC0);
	TFTPar(0x23);

	TFTCmd(0xC1);
	TFTPar(0x10);

	TFTCmd(0xC5);
	TFTPar(0x3E);
	TFTPar(0x28);

	TFTCmd(0xC7);
	TFTPar(0x86);

	TFTSetOrientation(tft_orientation);
//	TFTCmd(0x36);
//	TFTPar(0x48);

	TFTCmd(0x37);
	TFTPar(0x0);

	TFTCmd(0x3A);
	TFTPar(0x55);

	TFTCmd(0xB1);
	TFTPar(0x0);
	TFTPar(0x18);

	TFTCmd(0xB6);
	TFTPar(0x08);
	TFTPar(0x82);
	TFTPar(0x27);

	TFTCmd(0xF2);
	TFTPar(0x0);

	TFTCmd(0x26);
	TFTPar(0x01);

	TFTCmd(0xE0);
	TFTPar(0x0F);
	TFTPar(0x31);
	TFTPar(0x2B);
	TFTPar(0x0C);
	TFTPar(0x0E);
	TFTPar(0x08);
	TFTPar(0x4E);
	TFTPar(0xF1);
	TFTPar(0x37);
	TFTPar(0x07);
	TFTPar(0x10);
	TFTPar(0x03);
	TFTPar(0x0E);
	TFTPar(0x09);
	TFTPar(0x0);

	TFTCmd(0xE1);
	TFTPar(0x0);
	TFTPar(0x0E);
	TFTPar(0x14);
	TFTPar(0x03);
	TFTPar(0x11);
	TFTPar(0x7);
	TFTPar(0x31);
	TFTPar(0xC1);
	TFTPar(0x48);
	TFTPar(0x08);
	TFTPar(0x0F);
	TFTPar(0x0C);
	TFTPar(0x31);
	TFTPar(0x36);
	TFTPar(0x0F);

	TFTCmd(0x11);
	_delay_ms(150);
	TFTCmd(0x29);
	_delay_ms(150);
	SB(CS_TFT_PORT,CS_TFT_PIN);
}

//------------------------------------------
//-------------------------------------------------------------
/*
void InitTFT2(void) {
	CB(CS_TFT_PORT,CS_TFT_PIN);
	TFTHardReset();
	//COLMOD: Pixel Format Set
	TFTCmd(0x3A);		//один пиксель будет кодироваться 16 битами
	TFTPar(0x05);
	TFTSetOrientation(0); //выбираем ориентацию дисплея
	TFTCmd(0x11);
	_delay_ms(120);
	TFTCmd(0x29);
	_delay_ms(120);
	CB(CS_TFT_PORT,CS_TFT_PIN);
}
*/
//-------------------------------------------------------------

//-------------------------------------------------------------
void InitTFT() {
	CB(CS_TFT_PORT,CS_TFT_PIN);
	TFTHardReset();
	TFTCmd(0x01);        //Software Reset
	_delay_ms(200);

	//Power Control 1
	TFTCmd(0xC0);		//задаём градацию серого цвета
	TFTPar(0x25);

	//Power Control 2
	TFTCmd(0xC1);		//настройка step up преобразователя
	TFTPar(0x11);

	//VCOM Control 1
	TFTCmd(0xC5);		//контрастность определяется разностью VCOMH - VCOML = 5.2V
	TFTPar(0x2B);	        //VCOMH = 3.825
	TFTPar(0x2B);  	//VCOML = -1.375

	//VCOM Control 2
	TFTCmd(0xC7);		//на Vcom по сути ШИМ, а тут мы задаем offset для него
	TFTPar(0x86);        //VML=58 VMH=58

	//Memory Access Control
	TFTSetOrientation(0); //выбираем ориентацию дисплея

	//COLMOD: Pixel Format Set
	TFTCmd(0x3A);		//один пиксель будет кодироваться 16 битами
	TFTPar(0x05);
	//Frame Rate Control
	TFTCmd(0xB1);
	TFTPar(0x00);
	TFTPar(0x18);	 //Frame Rate 79Hz

	//Display Function Control
	TFTCmd(0xB6);
	TFTPar(0x0A);
	TFTPar(0x82);//восьмой бит определяет нормальный цвет кристала белый - 1, черный - 0,
	TFTPar(0x27);

	// Sleep Out
	TFTCmd(0x11);
	_delay_ms(120);

	//Display On
	TFTCmd(0x29);
	_delay_ms(200);

	TFTSetColumn(0,240);
	TFTSetPage(0,320);
	TFTCmd(0x2c);
	for (u32 i=0;i<76800;i++) {
		TFTData(WHITE);
	}
/*
	TFTSetColumn(20,40);
	TFTSetPage(2,40);
	TFTCmd(0x2c);
	for (u32 i=0;i<(400-1);i++) {
		TFTData(BLACK);
	}
*/
//	BLine(0,0,240,320,0);
//	BCircle(120,160,117,BLUE);
	SB(CS_TFT_PORT,CS_TFT_PIN);
}
//--------------------------------------------------
void TFTHardReset() {
	CB(RST_GPIO_Port,RST_Pin);
	_delay_ms(20);
	SB(RST_GPIO_Port,RST_Pin);
	_delay_ms(150);
}
//--------------------------------------------------
/*
void TFTSendData(u16 data) {
	uint8_t data1 = data>>8;
	uint8_t data2 = data&0xff;
	TFTPar(data1);
	TFTPar(data2);
}*/
//--------------------------------------------

void TFT_Init() {
//u08 rotation;
//  TFT_Pins_Init();
//  CB(CONTROL_PORT, CS_pin);
/*
  #ifndef RESET_HW
    TFT_Reset_SW();
  #else
    TFT_Reset_HW();
  #endif
*/
  TFTCmd(0x3A);
    TFTPar(0x55);
  TFTCmd(0x36);
    TFTPar(0x55);
  TFTCmd(0x3A);
  _delay_ms(120);
  TFTCmd(0x3A);
  _delay_ms(120);
	//rotation=ROTATION;
//	TFT_Set_Orientation(rotation);

//  SB(CONTROL_PORT, CS_pin);
}
//--------------------------------------------
//-------------------------------------------------------------
//--------------------FUNCTIONS FOR DMA------------------------
//-------------------------------------------------------------
/*
void TFTDrawUT32_X_DMA(u16 x, u16 y, u16 color, u16 fone, u32 numeric, u08 digits,u08 size,char * mas) {
	TrimConvertX(mas,numeric,digits);
	TFTDrawString_DMA(x,y,color,fone,mas,size);
}
//--------------------------------------------------
void TFTDrawST32_X_DMA(u16 x, u16 y, u16 color, u16 fone, u32 numeric, u08 digits,u08 size,char * mas) {
	STrimConvertX(mas,numeric,digits);
	TFTDrawString_DMA(x,y,color,fone,mas,size);
}
//--------------------------------------------------
void TFTDrawU32_X_DMA(u16 x, u16 y, u16 color, u16 fone, u32 numeric, u08 digits,u08 size,char * mas) {
	ConvertX(mas,numeric,digits);
	TFTDrawString_DMA(x,y,color,fone,mas,size);
}
//--------------------------------------------------
void TFTDrawString_DMA(u16 x, u16 y, u16 color,u16 fone, const char *string, u08 size) {
	while(*string) {
		if((x + FONT_X) > Max_X) {
			x = 1;
			y = y + FONT_X*size;
		}
		TFTDrawChar_DMA(x, y, color, fone,*string, size);
		x += FONT_X*size;
		string++;
	}
}
//----------------------------------------------------------
void TFTDrawChar_DMA(u16 x, u16 y, u16 color, u16 fone, u08 ascii, u08 size) {
	for (int i = 0; i < FONT_Y; i++ ) {
		for(u08 f = 0; f < FONT_X; f++) {
			if(((fontx[ascii-0x20][i])>>(7-f))&0x01) {
				 TFTFillRectangle_DMA(x+f*size,y+i*size,size,size,color);
			}
			else {
				 TFTFillRectangle_DMA(x+f*size,y+i*size,size,size,fone);
			}
		}
	}
}
//-----------------------------------------------------
//x & y - это координаты левого верхнего угла прямоугольника
void TFTFillRectangle_DMA(u16 x, u16 y, u16 length, u16 width, u16 color) {
	for(u16 iy=y;iy<y+width;iy++) {
		TFTDrawHorizontalLine_DMA(x, iy, length, color);
	}
}
//--------------------------------------------------
void TFTDrawCircle_DMA(u16 pos_x, u16 pos_y, u08 r,u16 color) {
	pos_x = constrain(pos_x, MIN_X,Max_X);
	pos_y = constrain(pos_y, MIN_Y,Max_Y);

	int x = -r, y = 0, err = 2-2*r, e2;
	do {
		DrawPixel_DMA(pos_x-x, pos_y+y,color);
		DrawPixel_DMA(pos_x+x, pos_y+y,color);
		DrawPixel_DMA(pos_x+x, pos_y-y,color);
		DrawPixel_DMA(pos_x-x, pos_y-y,color);
		e2 = err;
		if (e2 <= y) {
			err += ++y*2+1;
			if (-x == y && e2 <= x) e2 = 0;
		}
		if (e2 > x) err += ++x*2+1;
	} while (x <= 0);
}
//--------------------------------------------------
void TFTDrawTriangle_DMA( u16 x1, u16 y1, u16 x2, u16 y2, u16 x3, u16 y3, u16 color) {
	TFTDrawLine_DMA( x1, y1, x2, y2, color);
	TFTDrawLine_DMA( x2, y2, x3, y3, color);
	TFTDrawLine_DMA( x3, y3, x1, y1, color);
}
//--------------------------------------------------
void TFTDrawRectangle_DMA(u16 x, u16 y, u16 length, u16 width,u16 color) {
	TFTDrawHorizontalLine_DMA(x, y, length, color);
	TFTDrawHorizontalLine_DMA(x, y + width-1, length, color);
	TFTDrawVerticalLine_DMA(x, y, width,color);
	TFTDrawVerticalLine_DMA(x + length -1, y, width,color);
}
//--------------------------------------------------
void TFTDrawVerticalLine_DMA( u16 x, u16 y, u16 length,u16 color) {
	x = constrain(x, MIN_X,Max_X);
	y = constrain(y, MIN_Y,Max_Y);

	for(int i=0; i<length; i++)
		DrawPixel_DMA(x,y+i,color);
}
//--------------------------------------------------
void  TFTDrawHorizontalLine_DMA( u16 x, u16 y, u16 length,u16 color) {
	x = constrain(x, MIN_X,Max_X);
	y = constrain(y, MIN_Y,Max_Y);

	for(u16 i=0; i<length; i++){
		DrawPixel_DMA(x+i,y,color);
	}
}
//--------------------------------------------------
void TFTDrawLine_DMA( u16 x0,u16 y0,u16 x1, u16 y1,u16 color) {
int x = x1-x0;
x0 = constrain(x0, MIN_X,Max_X);
y0 = constrain(y0, MIN_Y,Max_Y);
x1 = constrain(x1, MIN_X,Max_X);
y1 = constrain(y1, MIN_Y,Max_Y);

	int y = y1-y0;
	int dx = abs(x), sx = x0<x1 ? 1 : -1;
	int dy = -abs(y), sy = y0<y1 ? 1 : -1;
	int err = dx+dy, e2;
	for (;;) {
		DrawPixel_DMA(x0,y0,color);
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
}

//-----------------------------------------------------
void DrawPixel_DMA(u16 x,u16 y,u16 color) {
	x = constrain(x, MIN_X,Max_X);
	y = constrain(y, MIN_Y,Max_Y);
	buff2[y][2*x]=color>>8;
	buff2[y][2*x+1]=color;
}
//-----------------------------------------------------
void TFTFillScreen_DMA(u16 color) {
	for (u16 i=0;i<TFT_Height;i++){
		for(u16 j=0;j<TFT_Width*2-1;j+=2){
			buff2[i][j]=color>>8;
			buff2[i][j+1]=color;
		}
	}
}
//-----------------------------------------------------
//-----------------------------------------------------
void InitTX_DMA() {
	CB(CS_TFT_PORT,CS_TFT_PIN);

	TFTCmd(CASET);
    //границы прямоугольника совпадают с границами дисплея
    TFTData(0x00);	TFTData(TFT_Width - 1);
  	TFTCmd(RASET);
    TFTData(0x00);	TFTData(TFT_Height - 1);
  	TFTCmd(RAMWR);
  	HAL_SPI_Transmit_DMA(&hspi3, &buff2[0][0], WXH);

}
*/
/*
static const s16 initcmd[] = {
  0xEF, 3, 0x03, 0x80, 0x02,
  0xCF, 3, 0x00, 0xC1, 0x30,
  0xED, 4, 0x64, 0x03, 0x12, 0x81,
  0xE8, 3, 0x85, 0x00, 0x78,
  0xCB, 5, 0x39, 0x2C, 0x00, 0x34, 0x02,
  0xF7, 1, 0x20,
  0xEA, 2, 0x00, 0x00,
  ILI9341_PWCTR1  , 1, 0x23,             // Power control VRH[5:0]
  ILI9341_PWCTR2  , 1, 0x10,             // Power control SAP[2:0];BT[3:0]
  ILI9341_VMCTR1  , 2, 0x3e, 0x28,       // VCM control
  ILI9341_VMCTR2  , 1, 0x86,             // VCM control2
  ILI9341_MADCTL  , 1, 0x48,             // Memory Access Control
  ILI9341_VSCRSADD, 1, 0x00,             // Vertical scroll zero
  ILI9341_PIXFMT  , 1, 0x55,
  ILI9341_FRMCTR1 , 2, 0x00, 0x18,
  ILI9341_DFUNCTR , 3, 0x08, 0x82, 0x27, // Display Function Control
  0xF2, 1, 0x00,                         // 3Gamma Function Disable
  ILI9341_GAMMASET , 1, 0x01,             // Gamma curve selected
  ILI9341_GMCTRP1 , 15, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, // Set Gamma
    0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00,
  ILI9341_GMCTRN1 , 15, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, // Set Gamma
    0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F,
  ILI9341_SLPOUT  , 0x80,                // Exit Sleep
  ILI9341_DISPON  , 0x80,                // Display on
  0x100                                   // End of list
};
*/
/*
void InitTFT5(void) {
	CB(CS_TFT_PORT,CS_TFT_PIN);
  // TFTCmd(ILI9341_SWRESET); // Engage software reset
   _delay_ms(150);

  u08 cmd=0, x=0, numArgs=0;
  const u08 *addr = initcmd;
  while (*addr != 0x100) {
    x = addr+2;
    //numArgs = x & 0x7F;
    TFTSendCommand(*addr, &x, *(addr+1));
    //addr += numArgs;
    addr++;
    if (x == 0x80)
      _delay_ms(150);
  }
//  _width = ILI9341_TFTWIDTH;
//  _height = ILI9341_TFTHEIGHT;
  SB(CS_TFT_PORT,CS_TFT_PIN);
}
*/


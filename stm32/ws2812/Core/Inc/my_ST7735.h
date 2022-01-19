#ifndef my_ST7735_h
#define my_ST7735_h
//---------------
#include "my_head_files.h"


#define CS_ST7735_PIN GPIO_PIN_0
#define CS_ST7735_PORT GPIOD

#define DC_Pin GPIO_PIN_1
#define DC_GPIO_Port GPIOD

#define RST_Pin GPIO_PIN_2
#define RST_GPIO_Port GPIOD


#define SWRESET		0x01
#define SLPOUT 		0x11 
#define DISPON		0x29
#define DISPOFF		0x28
 
#define CASET		0x2A
#define RASET		0x2B
#define	RAMWR		0x2C 

#define SWRESET		0x01
#define INVOFF		0x20
#define INVON		0x21
#define MADCTL		0x36
#define COLMOD		0x3A
#define NORON		0x13
//bits of MADCTL

//#define MY	0
//#define MX	0
//#define MV	0
#define ML	0
#define RGB	0
#define MH	0

#define VERT	ON

/*
#if	MV==0
	#define ST7735_WIDTH 	128
	#define ST7735_HEIGHT  	160
#else
	#define ST7735_WIDTH 	160
	#define ST7735_HEIGHT  	128
#endif
*/
#define ST7735_WIDTH 	128
#define ST7735_HEIGHT  	160


#define BLACK		0x0000
#define BLUE		0x001F
#define CYAN		0x07FF
#define DARKCYAN	0x03EF
#define DARKGREEN	0x03E0
#define GREEN		0x07E0
#define GREENYELLOW 0xAFE5
#define MAGENTA		0xF81F
#define MAROON		0x7800
#define NAVY		0x000F
#define OLIVE		0x7BE0
#define ORANGE		0xFD20
#define PINK		0xF81F
#define PURPLE		0x780F
#define RED			0xF800
#define WHITE		0xFFFF
#define YELLOW		0xFFE0

#define FONE	BLUE

#define MIN_X	0
#define MIN_Y	0

#define FONT_X	8
#define FONT_Y	8


void  TFTDrawHorizontalLine( u16 x, u16 y, u16 length,u16 color);
//--------------------------------------------------
void TFTDrawVerticalLine( u16 x, u16 y, u16 length,u16 color);
//--------------------------------------------------
void TFTDrawRectangle(u16 x, u16 y, u16 length, u16 width,u16 color);
//--------------------------------------------------
void TFTDrawTriangle( u16 x1, u16 y1, u16 x2, u16 y2, u16 x3, u16 y3, u16 color);
//--------------------------------------------------
void TFTDrawUT32(u16 x, u16 y, u16 color, u16 fone, u32 numeric, u08 digits,u08 size);
void TFTDrawST32(u16 x, u16 y, u16 color, u16 fone, s32 numeric, u08 digits,u08 size);
void TFTDrawU32(u16 x, u16 y, u16 color, u16 fone, u32 numeric, u08 digits,u08 size);
//----------------------------------------
void TFTDrawCircle(u16 pos_x, u16 pos_y, u08 r,u16 color);
//----------------------------------------
void TFTDrawString(u16 x, u16 y, u16 color,u16 fone, const char *string, u08 size);
void TFTDrawChar(u16 x, u16 y, u16 color, u16 fone, u08 ascii, u08 size);
//void TFTFill(u16 color);
void TFTFillScreen(u16 x_left, u16 x_right, u16 y_up, u16 y_down, u16 color);
void TFTFillRectangle(u16 x, u16 y, u16 length, u16 width, u16 color);
u16 constrain(u16 a, u16 b, u16 c);

void TFTDrawLine(u16 x0,u16 y0,u16 x1, u16 y1,u16 color);
void St7735FillScreen(u16 color);

/*ф-ция ограничивает координаты  рабочей области по оси Х*/
void TFTSetColumn(u16 start_column,u16 end_colunm);

/*ф-ция ограничивает координаты  рабочей области по оси Y*/
void TFTSetPage(u16 start_page,u16 end_page);

/*ф-ция ограничивает координаты  рабочей области*/
void TFTSetXY(u16 x, u16 y);

/*ф-ция отрисовывает пиксель по заданным координатам*/
void TFTDrawPixel(u16 x, u16 y,u16 color);
void ST7735Init();
void ST7735ReInit();
void SetupSt7735ForDMA();
#endif

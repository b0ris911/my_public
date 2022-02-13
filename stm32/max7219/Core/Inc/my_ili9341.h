#ifndef my_st7735_rtos_h
#define my_st7735_rtos_h
//---------------
#include "my_head_files.h"

#define CS_TFT_PIN GPIO_PIN_0
#define CS_TFT_PORT GPIOD

#define DC_Pin GPIO_PIN_1
#define DC_GPIO_Port GPIOD

#define RST_Pin GPIO_PIN_2
#define RST_GPIO_Port GPIOD
//Commands
#define ILI9341_TFTWIDTH 240  ///< ILI9341 max TFT width
#define ILI9341_TFTHEIGHT 320 ///< ILI9341 max TFT height

#define ILI9341_NOP 0x00     ///< No-op register
#define ILI9341_SWRESET 0x01 ///< Software reset register
#define ILI9341_RDDID 0x04   ///< Read display identification information
#define ILI9341_RDDST 0x09   ///< Read Display Status

#define ILI9341_SLPIN 0x10  ///< Enter Sleep Mode
#define ILI9341_SLPOUT 0x11 ///< Sleep Out
#define ILI9341_PTLON 0x12  ///< Partial Mode ON
#define ILI9341_NORON 0x13  ///< Normal Display Mode ON

#define ILI9341_RDMODE 0x0A     ///< Read Display Power Mode
#define ILI9341_RDMADCTL 0x0B   ///< Read Display MADCTL
#define ILI9341_RDPIXFMT 0x0C   ///< Read Display Pixel Format
#define ILI9341_RDIMGFMT 0x0D   ///< Read Display Image Format
#define ILI9341_RDSELFDIAG 0x0F ///< Read Display Self-Diagnostic Result

#define ILI9341_INVOFF 0x20   ///< Display Inversion OFF
#define ILI9341_INVON 0x21    ///< Display Inversion ON
#define ILI9341_GAMMASET 0x26 ///< Gamma Set
#define ILI9341_DISPOFF 0x28  ///< Display OFF
#define ILI9341_DISPON 0x29   ///< Display ON

#define ILI9341_CASET 0x2A ///< Column Address Set
#define ILI9341_PASET 0x2B ///< Page Address Set
#define ILI9341_RAMWR 0x2C ///< Memory Write
#define ILI9341_RAMRD 0x2E ///< Memory Read

#define ILI9341_PTLAR 0x30    ///< Partial Area
#define ILI9341_VSCRDEF 0x33  ///< Vertical Scrolling Definition
#define ILI9341_MADCTL 0x36   ///< Memory Access Control
#define ILI9341_VSCRSADD 0x37 ///< Vertical Scrolling Start Address
#define ILI9341_PIXFMT 0x3A   ///< COLMOD: Pixel Format Set

#define ILI9341_FRMCTR1                                                        \
  0xB1 ///< Frame Rate Control (In Normal Mode/Full Colors)
#define ILI9341_FRMCTR2 0xB2 ///< Frame Rate Control (In Idle Mode/8 colors)
#define ILI9341_FRMCTR3                                                        \
  0xB3 ///< Frame Rate control (In Partial Mode/Full Colors)
#define ILI9341_INVCTR 0xB4  ///< Display Inversion Control
#define ILI9341_DFUNCTR 0xB6 ///< Display Function Control

#define ILI9341_PWCTR1 0xC0 ///< Power Control 1
#define ILI9341_PWCTR2 0xC1 ///< Power Control 2
#define ILI9341_PWCTR3 0xC2 ///< Power Control 3
#define ILI9341_PWCTR4 0xC3 ///< Power Control 4
#define ILI9341_PWCTR5 0xC4 ///< Power Control 5
#define ILI9341_VMCTR1 0xC5 ///< VCOM Control 1
#define ILI9341_VMCTR2 0xC7 ///< VCOM Control 2

#define ILI9341_RDID1 0xDA ///< Read ID 1
#define ILI9341_RDID2 0xDB ///< Read ID 2
#define ILI9341_RDID3 0xDC ///< Read ID 3
#define ILI9341_RDID4 0xDD ///< Read ID 4

#define ILI9341_GMCTRP1 0xE0 ///< Positive Gamma Correction
#define ILI9341_GMCTRN1 0xE1 ///< Negative Gamma Correction
//#define ILI9341_PWCTR6     0xFC
/*
#define ILI9341_RESET				0x01
#define ILI9341_SLEEP_OUT			0x11
#define ILI9341_GAMMA				0x26
#define ILI9341_DISPLAY_OFF			0x28
#define ILI9341_DISPLAY_ON			0x29
#define ILI9341_COLUMN_ADDR			0x2A
#define ILI9341_PAGE_ADDR			0x2B
#define ILI9341_GRAM				0x2C
#define ILI9341_MAC			        0x36
#define ILI9341_PIXEL_FORMAT        0x3A
#define ILI9341_WDB			    	0x51
#define ILI9341_WCD				    0x53
#define ILI9341_RGB_INTERFACE       0xB0
#define ILI9341_FRC				    0xB1
#define ILI9341_BPC				    0xB5
#define ILI9341_DFC				    0xB6
#define ILI9341_POWER1				0xC0
#define ILI9341_POWER2				0xC1
#define ILI9341_VCOM1				0xC5
#define ILI9341_VCOM2				0xC7
#define ILI9341_POWERA				0xCB
#define ILI9341_POWERB				0xCF
#define ILI9341_PGAMMA				0xE0
#define ILI9341_NGAMMA				0xE1
#define ILI9341_DTCA				0xE8
#define ILI9341_DTCB				0xEA
#define ILI9341_POWER_SEQ			0xED
#define ILI9341_3GAMMA_EN			0xF2
#define ILI9341_INTERFACE			0xF6
#define ILI9341_PRC				    0xF7
*/

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


//#define VERT	ON //!!! check buff2[][] in .c file
/*
#define ST7735_WIDTH 	128
#define ST7735_HEIGHT  	160
*/

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

//void DrawFatLineX(u16 x,u16 y,u16 length,u08 thickness,u16 color);
void TFTFillCircle(u16 pos_x, u16 pos_y, u08 r,u16 color);
void TFTDrawHorizontalLine( u16 x, u16 y, u16 length,u16 color);
void TFTDrawVerticalLine( u16 x, u16 y, u16 length,u16 color);
void TFTDrawTriangle( u16 x1, u16 y1, u16 x2, u16 y2, u16 x3, u16 y3, u16 color);
void TFTDrawRectangle(u16 x, u16 y, u16 length, u16 width,u16 color);
void TFTDrawUT32(u16 x, u16 y, u16 color, u16 fone, u32 numeric, u08 digits,u08 size);
void TFTDrawST32(u16 x, u16 y, u16 color, u16 fone, u32 numeric, u08 digits,u08 size);
void TFTDrawU32(u16 x, u16 y, u16 color, u16 fone, u32 numeric, u08 digits,u08 size);
void TFTDrawCircle(u16 pos_x, u16 pos_y, u08 r,u16 color);
void TFTDrawString(u16 x, u16 y, u16 color,u16 fone, const char *string, u08 size);
void TFTDrawChar(u16 x, u16 y, u16 color, u16 fone, u08 ascii, u08 size);

u16 constrain(u16 a, u16 b, u16 c);
void TFTFillRectangle(u16 x, u16 y, u16 length, u16 width, u16 color);
void TFTFillScreen2(u16 x_left, u16 x_right, u16 y_up, u16 y_down, u16 color);
void TFTDrawLine(u16 x0,u16 y0,u16 x1, u16 y1,u16 color);
//void TFTFill(u16 color);
void TFTFillScreen(u16 color);
void DrawTFT(void);
/*ф-ция ограничивает координаты  рабочей области по оси Х*/
void TFTSetColumn(u16 start_column,u16 end_colunm);
/*ф-ция ограничивает координаты  рабочей области по оси Y*/
void TFTSetPage(u16 start_page,u16 end_page);
/*ф-ция ограничивает координаты  рабочей области*/
void TFTSetXY(u16 x, u16 y);
/*ф-ция отрисовывает пиксель по заданным координатам*/
void TFTDrawPixel(u16 x, u16 y,u16 color);
void InitTFT(void);
void InitILI9341(void);
void TFTSetOrientation(u08 orient);
//void TFTSendData(u16 data);
void TFTHardReset();
void TFT_Init(void);
//-------------------------FOR DMA---------------------
/*
#define WXH	40960

void TFTDrawUT32_X_DMA(u16 x, u16 y, u16 color, u16 fone, u32 numeric, u08 digits,u08 size,char * mas);
void TFTDrawST32_X_DMA(u16 x, u16 y, u16 color, u16 fone, u32 numeric, u08 digits,u08 size,char * mas);
void TFTDrawU32_X_DMA(u16 x, u16 y, u16 color, u16 fone, u32 numeric, u08 digits,u08 size,char * mas);
void TFTDrawString_DMA(u16 x, u16 y, u16 color,u16 fone, const char *string, u08 size);
void TFTDrawChar_DMA(u16 x, u16 y, u16 color, u16 fone, u08 ascii, u08 size);
void TFTFillRectangle_DMA(u16 x, u16 y, u16 length, u16 width, u16 color);
void TFTDrawCircle_DMA(u16 pos_x, u16 pos_y, u08 r,u16 color);
void TFTDrawTriangle_DMA( u16 x1, u16 y1, u16 x2, u16 y2, u16 x3, u16 y3, u16 color);
void TFTDrawRectangle_DMA(u16 x, u16 y, u16 length, u16 width,u16 color);
void TFTDrawVerticalLine_DMA( u16 x, u16 y, u16 length,u16 color);
void TFTDrawHorizontalLine_DMA( u16 x, u16 y, u16 length,u16 color);
void TFTDrawLine_DMA( u16 x0,u16 y0,u16 x1, u16 y1,u16 color);
void DrawPixel_DMA(u16 x,u16 y,u16 color);
void TFTFillScreen_DMA(u16 color);
void InitTX_DMA();
*/
#endif

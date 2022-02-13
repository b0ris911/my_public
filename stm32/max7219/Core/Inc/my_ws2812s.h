#ifndef my_ws2812s_h
#define my_ws2812s_h

#include "my_head_files.h"

#define LED_COUNT 				120	//число групп светодиодов
#define ARRAY_LENGTH			24

#define HIGH_TIME		136//205//102//205		//0.5 us
#define LOW_TIME		68//86//43//86		//1.2 us
//#define 224	1.3 us
#define TIME_ONE_COLOR		30	//ms
#define TIME_LEDLINE		5	//ms

//void ConvertRGB565to24(u16 RGB565);
void ConvertRGB565to24_X(u16 RGB565[],u16 adc_data);
void RUN_LedLine(void);

void BlackLine(void);
void RUN_TestRotateColors(void);
void TestRotateColors(u08 number_of_colors);
void RotateColors(u16 array[],u08 number_of_colors);
void SetFlag(void);
void Long_Line(void);
void SmoothColorChange(void);
void RunningColor(void);
void RunningColor2(void);
void ColorSnake(void);





#endif

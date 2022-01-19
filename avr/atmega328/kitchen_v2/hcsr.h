#ifndef hcsr_h
#define hcsr_h
//---------------
#include "head_files.h"

#define TIME_ON			150
#define TIME_OFF		150
#define TIME_PAUSE		1500
#define DIST_MAX		15
#define DIST_MIN		3

#define DDR_TRIG	DDRC
#define PORT_TRIG	PORTC
#define TRIG		5

//#define DDR_ECHO	DDRC
//#define PORT_ECHO	PORTC
//#define PIN_ECHO	PINC
//#define ECHO		0

#define DDR_NASOS_HOT_WATER			DDRD
#define PORT_NASOS_HOT_WATER		PORTD
#define NASOS_HOT_WATER				7

void InitPortsTrig();
void StartTrig();
void NasosHotWaterOn();
void NasosHotWaterOff();
void InitPortsNasosHotWater();
void HotWater();

#endif

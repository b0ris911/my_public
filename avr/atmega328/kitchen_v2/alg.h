#ifndef alg_h
#define alg_h
//---------------
#include "head_files.h"

#define T_MIN				25
#define T_MAX				30
#define TIME_DI_WORK		5
#define TIME_DI_SET_MIN		20
#define TIME_DI_SET_MAX		10
#define TIME_DI_ALARM		10

#define TIME_BUZZER_ON		100	//ms
#define TIME_BUZZER_OFF		200

#define DDR_BUZZER 		DDRB
#define PORT_BUZZER 	PORTB
#define BUZZER			1

#define DDR_NASOS_VANNA			DDRB
#define PORT_NASOS_VANNA		PORTB
#define NASOS_VANNA				0

//#define 4
void InitPortsBuzzer();
void BuzzerOn();
void BuzzerOff();
void BuzzerSound();
void BuzzerOk();

void ProcessNasos();
void InitPortsNasos();
void NasosOn();
void NasosOff();

void Setup();
void RedLedFlash();
void Algorithm();
void ReadingDataFromEeprom();

#define ADR_T_MIN	100
#define ADR_T_MAX	200

#endif

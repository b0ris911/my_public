#ifndef led_h
#define led_h
//---------------
#include "head_files.h"

void InitPortsLedRed();
void InitPortsLedBlue();
void InitPortsLedGreen();
void InitPortsLedWhite();


void TestLedRed();
void TestLedBlue();
void TestLedGreen();
void TestLedWhite();

void LedRedOn();
void LedRedOff();

void LedBlueOn();
void LedBlueOff();

void LedGreenOn();
void LedGreenOff();

void LedWhiteOn();
void LedWhiteOff();

#define PORT_LED_RED PORTC
#define PIN_LED_RED PINC
#define DDR_LED_RED DDRC
#define LED_RED 0
//--
#define PORT_LED_BLUE PORTC
#define PIN_LED_BLUE PINC
#define DDR_LED_BLUE DDRC
#define LED_BLUE 0
//---
#define PORT_LED_GREEN PORTB
#define PIN_LED_GREEN PINB
#define DDR_LED_GREEN DDRB
#define LED_GREEN 0
//---
#define PORT_LED_WHITE PORTC
#define PIN_LED_WHITE PINC
#define DDR_LED_WHITE DDRC
#define LED_WHITE 0

#endif

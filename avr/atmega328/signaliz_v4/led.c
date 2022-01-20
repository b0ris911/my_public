#include "led.h"

void InitPortsLedRed() {
	DDR_LED_RED |= (1<<LED_RED);
	PORT_LED_RED &= ~(1<<LED_RED);
}
/*
void InitPortsLedBlue() {
	DDR_LED_BLUE |= (1<<LED_BLUE);
	PORT_LED_BLUE &= ~(1<<LED_BLUE);
}
void InitPortsLedGreen() {
	DDR_LED_GREEN |= (1<<LED_GREEN);
	PORT_LED_GREEN &= ~(1<<LED_GREEN);
}
void InitPortsLedWhite() {
	DDR_LED_WHITE |= (1<<LED_WHITE);
	PORT_LED_WHITE &= ~(1<<LED_WHITE);
}
*/
//-------------------------------
void TestLedRed() {
			PORT_LED_RED ^= 1<<LED_RED;			
}
/*
void TestLedBlue() {
			PORT_LED_BLUE ^= 1<<LED_BLUE;			
}
void TestLedGreen() {
			PORT_LED_GREEN ^= 1<<LED_GREEN;			
}
void TestLedWhite() {
			PORT_LED_WHITE ^= 1<<LED_WHITE;			
}
*/

void LedRedOn() {
	SB(PORT_LED_RED,LED_RED);
}
void LedRedOff() {
	CB(PORT_LED_RED,LED_RED);
}

/*
void LedBlueOn() {
	SB(PORT_LED_BLUE,LED_BLUE);
}
void LedBlueOff() {
	CB(PORT_LED_BLUE,LED_BLUE);
}
void LedGreenOn() {
	SB(PORT_LED_GREEN,LED_GREEN);
}
void LedGreenOff() {
	CB(PORT_LED_GREEN,LED_GREEN);
}
void LedWhiteOn() {
	SB(PORT_LED_WHITE,LED_WHITE);
}
void LedWhiteOff() {
	CB(PORT_LED_WHITE,LED_WHITE);
}
*/

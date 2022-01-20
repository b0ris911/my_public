#ifndef algoritm_h
#define algoritm_h

#include "head_files.h"

#define DDR_SIRENA				DDRD
#define PORT_SIRENA				PORTD
#define SIRENA					2

#define DDR_ALARM_TONE			DDRD
#define PORT_ALARM_TONE			PORTD
#define ALARM_TONE				3

#define DDR_RESET_SIM800L		DDRD
#define PORT_RESET_SIM800L		PORTD
#define RESET_SIM800L			4

#define DDR_INCOMING_SIM800L	DDRC
#define PIN_INCOMING_SIM800L	PINC
#define PORT_INCOMING_SIM800L	PORTC
#define INCOMING_SIM800L		5

#define DDR_LINE_1				DDRD
#define PORT_LINE_1				PORTD
#define PIN_LINE_1				PIND
#define LINE_1					7

#define DDR_LINE_2				DDRD
#define PORT_LINE_2				PORTD
#define PIN_LINE_2				PIND
#define LINE_2					6

#define DDR_LINE_3				DDRD
#define PORT_LINE_3				PORTD
#define PIN_LINE_3				PIND
#define LINE_3					5

#define TIME_DELAYED_START						120 //sec	задержка старта
#define KOLVO_POPYTOK_DOZVONA					3
#define TIME_DELAY_REPEAT_ALARM_CALLING			10000 //ms
#define TIME_SIRENA_OFF							60000 //ms 60000=1 min

//work modes
#define TEST_SIM800L			0		
#define TEST_LINES				1
#define SETUP					2
#define BROKEN_LINES			3
#define DELAYED_START			4
#define ALL_OK					5
#define INCOMING_CALL			6
#define RELEASE_GUARD			7
#define SYSTEM_RESET			8
#define POWER_OFF				9

void MainAlgorithm();
void TestAlg();
void ResetSim800L();
void InitPortsSim800L();
void InitTestLines();
void ResetSim800l();
void SetupData();
void ReadingFromEeprom();

#endif

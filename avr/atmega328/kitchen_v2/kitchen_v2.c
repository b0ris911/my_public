#include "_def.h"
//Глобальные переменные
#include "_var.h"
///*******************
#include "head_files.h"
//----------------------
//-----------------------------------------------------------------------------MAIN FUNCTION---
extern u08 work_mode;
extern OWIflags OWIStatus;

volatile s16 data_di=0;
volatile u08 time_di=TIME_DI_WORK;

int main() {
//--------------------------------***---INITIALISATION---***
_delay_ms(20);
InitPortsKn1();
InitPortsKn2();

InitPortsDI();

InitPortsTrig();
InitPortsNasosHotWater();
InitPortsNasos();
NasosOff();

InitPortsBuzzer();
BuzzerOn();
_delay_ms(5);
BuzzerOff();

InitGTimers();
InitMessages();
OWI_Init();    

_delay_ms(5);

if ( (BIC(PIN_KN1,KN1))||(BIC(PIN_KN2,KN2)) ) {
	work_mode=DIST;
}
else
	work_mode=WORK;
//-------------------------------Timer 0 ----------------------------
TCCR0A = (0<<COM0A1)|(0<<COM0A0)|(1<<WGM01)|(0<<WGM00);
TCCR0B = (0<<CS02)|(1<<CS01)|(1<<CS00);
OCR0A=125;
TIMSK0 = (1<<OCIE0A);
//-------------------------------------------------------------------
//OCR1A=2000;
//TCCR1A = (0<<COM1A1)|(1<<COM1A0)|(0<<COM1B1)|(0<<COM1B0)|(0<<WGM11)|(0<<WGM10);
//TCCR1B = (0<<ICNC1)|(0<<ICES1)|(0<<WGM13)|(1<<WGM12)|(0<<CS12)|(1<<CS11)|(0<<CS10); //8
//TIMSK1 = (1<<OCIE1A);
//----------------------------------------------------**--MAIN--**
SEI
EEARH=0;
ReadingDataFromEeprom();
//---------------------------------------------------
  while(1)  {  
//---------------------Обработка кнопок---------
	StartGTimer(timer_kn,5);
	if (ExpGTimer(timer_kn)) {		//10ms
		ProcessKn1(&f1_hold);		
		ProcessKn2(&f2_hold);		
	}
//----------------------------------------------
	StartGTimer(timer_di,time_di);
	if (ExpGTimer(timer_di)) {		//10ms
		di(data_di);		
	}
//----------------------------------------------
if((work_mode==WORK)||(work_mode==ALARM)) {
	if (!OWIStatus.busy) {
		ProcessDS18B20();
	}		
}
//-------------------------------
Algorithm();
//-------------------------------
BuzzerSound();
//-------------------------------
Setup();
//-------------------------------
StartTrig();
//-------------------------------
HotWater();
//-------------------------------
//+++++++++++++++++++++++++++++++
//-------------------------------
ProcessMessages();
//-------------------------------
  }//while
  return 0;
}//main
//--------------------------------------------------------------END of MAIN---



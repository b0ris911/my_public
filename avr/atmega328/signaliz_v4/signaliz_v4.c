#include "_def.h"
//Глобальные переменные
#include "_var.h"
///*******************
#include "head_files.h"
//--------------------------------------------------MAIN FUNCTION---
int main() {
WDT_off();
CLI
//-------------------------------------------***---INITIALISATION---***
_delay_ms(20);
InitPortsKn1();
InitPortsKn2();
InitPortsLedRed();
InitTestLines();
InitGTimers();
InitMessages();
InitUart();

InitPortsSim800L();
//----выводы сирены и тревоги на выход, инверсия
DDR_ALARM_TONE |= 1<<ALARM_TONE;
PORT_ALARM_TONE |= (1<<ALARM_TONE);

DDR_SIRENA |= 1<<SIRENA;
PORT_SIRENA |= (1<<SIRENA);

_delay_ms(20);

for(u08 i=0;i<2;i++) {
	LedRedOn();
	_delay_ms(10);
	LedRedOff();
	_delay_ms(100); 
}
//-------------------------------Timer 0 ----------------------------
TCCR0A = (0<<COM0A1)|(0<<COM0A0)|(0<<COM0B1)|(0<<COM0B0)|(1<<WGM01)|(0<<WGM00);
TCCR0B = (0<<FOC0A)|(0<<FOC0B)|(0<<WGM02)|(0<<CS02)|(1<<CS01)|(1<<CS00);
OCR0A=62;
TIMSK0 = (0<<OCIE0B)|(1<<OCIE0A)|(0<<TOIE0);
//--------------------------------AC off-----------------------------
ACSR = 1<<ACD;
//----------------------------------------------------**--MAIN--**
SEI
EEARH=0;
ReadingFromEeprom();
//------------------------------------------------
extern u08 work_mode;
extern u08 system_reset_counter;
	if((BIC(PIN_KN1,KN1))&&(BIS(PIN_KN2,KN2))) { //если нажата К1
		work_mode=DELAYED_START;
	}		
	if((BIS(PIN_KN1,KN1))&&(BIC(PIN_KN2,KN2))) {//если нажата К2
		work_mode=SETUP;
	}				
	if((BIS(PIN_KN1,KN1))&&(BIS(PIN_KN2,KN2))) {//если не нажаты обе
		work_mode=TEST_SIM800L;
	}
	if(BIC(PIN_INCOMING_SIM800L,INCOMING_SIM800L)) {//если идет входящий звонок
		work_mode=INCOMING_CALL;
	}


//---------------------------------------------------
  while(1)  {  
//---------------------Обработка кнопок--------------
	StartGTimer(timer_kn,10);
	if (ExpGTimer(timer_kn)) {		//10ms
		ProcessKn1(&f1_hold);		
		ProcessKn2(&f2_hold);		
	}
//------------------------------------------
	if(ExpGTimer(timer_total_reset)) {//обнуляется после каждого нажатия кнопок
		work_mode=SYSTEM_RESET;
	}
//------------------------------------------
	if(system_reset_counter==30) {
		ResetSim800L();
		work_mode=SYSTEM_RESET;
	}		
//------------------------------------------
MainAlgorithm();
//-------------------------------
ProcessMessages();
//-------------------------------
ProcessShedulerUart();
//-------------------------------
  }//while
  return 0;
}//main
//------------------------------------------------------------------------------END of MAIN---


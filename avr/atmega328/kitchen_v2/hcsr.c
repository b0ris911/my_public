#include "hcsr.h"

extern u16 data_di;
extern u08 work_mode;
volatile u08 step_int0=0;
volatile u16 counter_echo=135;
volatile u08 show_distance_on_lcd=OFF;
//---------------------------------------------
void HotWater() {
volatile static u08 step_hw=5;
	switch (step_hw) {	
		case 5:
			StartGTimer(timer_delay_start_hcsr,1000);
			if(ExpGTimer(timer_delay_start_hcsr)) {
				step_hw=10;
			}
		break;		
		case 10:		
			if((counter_echo<DIST_MAX)&&(counter_echo>DIST_MIN)) {
				StartGTimer(timer_hot_water,TIME_ON);
				step_hw=20;
			}		
		break;
		case 20:
			if(ExpGTimer(timer_hot_water)){
				if((counter_echo>=DIST_MAX)||(counter_echo<=DIST_MIN)){
					counter_echo=100;
					step_hw=10;
					return;
				}
				NasosHotWaterOn();	
				counter_echo=100;				
				step_hw=30;
			}		
		break;
		case 30:
			StartGTimer(timer_hot_water,TIME_PAUSE);
			if(ExpGTimer(timer_hot_water)){
				step_hw=40;
			}
		break;					
		case 40:			
			if((counter_echo<DIST_MAX)&&(counter_echo>DIST_MIN)) {
				StartGTimer(timer_hot_water,TIME_OFF);
				step_hw=50;
			}		
		break;		
		case 50:
			if(ExpGTimer(timer_hot_water)){
				if((counter_echo>=DIST_MAX)||(counter_echo<=DIST_MIN)){
					step_hw=40;
					return;
				}
				NasosHotWaterOff();
				counter_echo=100;
				step_hw=60;					
			}
		break;
		case 60:
			StartGTimer(timer_hot_water,TIME_PAUSE);
			if(ExpGTimer(timer_hot_water)){
				step_hw=10;
			}
		break;					
	}
}
//---------------------------------------------
void NasosHotWaterOn() {
	CB(PORT_NASOS_HOT_WATER,NASOS_HOT_WATER);
//	LedRedOn();
}
//---------------------------------------------
void NasosHotWaterOff() {
	SB(PORT_NASOS_HOT_WATER,NASOS_HOT_WATER);
//	LedRedOff();
}
//---------------------------------------------
void InitPortsNasosHotWater() {
	SB(DDR_NASOS_HOT_WATER,NASOS_HOT_WATER);
	NasosHotWaterOff();
}
//---------------------------------------------
ISR (INT0_vect) {
	switch (step_int0) {
		case 0:
			TCNT1=0;
			TCCR1A = (0<<COM1A1)|(0<<COM1A0)|(0<<COM1B1)|(0<<COM1B0)|(0<<WGM11)|(0<<WGM10);
			TCCR1B = (0<<ICNC1)|(0<<ICES1)|(0<<WGM13)|(0<<WGM12)|(0<<CS12)|(1<<CS11)|(0<<CS10); //8
			EICRA=(1<<ISC01)|(0<<ISC00);
			step_int0=1;

		break;
		case 1:
			TCCR1A = (0<<COM1A1)|(0<<COM1A0)|(0<<COM1B1)|(0<<COM1B0)|(0<<WGM11)|(0<<WGM10);
			TCCR1B = (0<<ICNC1)|(0<<ICES1)|(0<<WGM13)|(0<<WGM12)|(0<<CS12)|(0<<CS11)|(0<<CS10); //0			
			EIMSK=0;
			counter_echo=TCNT1/58;
			if(work_mode==DIST) {
				data_di=counter_echo;
			}		
		break;
	}
}
//-----------------------------------------
void InitPortsTrig() {
	SB(DDR_TRIG,TRIG);
	CB(PORT_TRIG,TRIG);
}
//---------------------------------------------
void StartTrig() {
	StartGTimer(timer_trig,250);
	if(ExpGTimer(timer_trig)) {
		step_int0=0;
		CLI
		SB(PORT_TRIG,TRIG);
		_delay_us(15);
		CB(PORT_TRIG,TRIG);		
		EIMSK=(1<<INT0);
		EICRA = (1<<ISC01)|(1<<ISC00);
		SEI
	}		
}

#include "alg.h"

extern u08 f1_hold,f2_hold;
extern u08 time_di;
extern s16 data_di;
extern s16 temp_data;

volatile u08 work_mode=WORK;
volatile u08 allow_red_led_flashing=0;
volatile u08 allow_buzzer=OFF;
volatile u16 t_min=T_MIN;
volatile u16 t_max=T_MAX;
u16 tmp=0;
//------------------------------------------
void Algorithm() {
	switch(work_mode){
		case WORK:
			if(temp_data>=t_max*10) {
				allow_buzzer=ON;
				work_mode=ALARM;
				time_di=TIME_DI_ALARM;	
			}
		break;
		case ALARM:
			if(temp_data<=t_min*10) {
				allow_buzzer=OFF;
				work_mode=WORK;
				time_di=TIME_DI_WORK;
			}
			if(temp_data>=((t_max+5)*10)) {
				allow_buzzer=ON;		
			}
			if(temp_data>=((t_max+10)*10)) {
				allow_buzzer=ON;		
			}

//			if( (GetMessage(MSG_KN1_FAST_PRESSED))||(GetMessage(MSG_KN2_FAST_PRESSED)) ) {
//				allow_buzzer=OFF;
//				BuzzerOff();			
//			}		
		break;
	}
}
//------------------------------------------
void Setup() {
	if( (GetMessage(MSG_KN1_RELEASED))||(GetMessage(MSG_KN2_RELEASED)) )  {
		switch(work_mode) {
			case WORK:
			case ALARM:
				work_mode=SET_MIN;
				time_di=TIME_DI_SET_MIN;
				data_di=t_min;	
			break;
			case SET_MIN:
				work_mode=SET_MAX;
				time_di=TIME_DI_SET_MAX;
				data_di=t_max;
			break;
			case SET_MAX:
				work_mode=WORK;
				time_di=TIME_DI_WORK;
			break;
			case DIST:
			break;
		}									
		return;
	}
	
	if(GetMessage(MSG_KN1_PRESSED)) {
		switch(work_mode) {
			case WORK:
			case ALARM:
			case DIST:
				if(allow_buzzer==ON) {
					allow_buzzer=OFF;
				}		
				else
					IB(PORT_NASOS_VANNA,NASOS_VANNA);
			break;
			case SET_MIN:
				t_min--;//decrement t min				
				if(t_min==0) {
					t_min=1;
				}		
				data_di=t_min;
				tmp=t_min;
				WriteEeprom_x16(ADR_T_MIN,&tmp);
			break;
			case SET_MAX:
				t_max--;//decrement t max
				if(t_max==t_min) {
					t_max=t_min+1;
				}		
				data_di=t_max;
				tmp=t_max;
				WriteEeprom_x16(ADR_T_MAX,&tmp);
			break;		
		}
		return;		
	}

	if(GetMessage(MSG_KN2_PRESSED)) {
		switch(work_mode) {
			case WORK:
			case ALARM:
			case DIST:
				if(allow_buzzer==ON) {
					allow_buzzer=OFF;
				}		
				else
					IB(PORT_NASOS_VANNA,NASOS_VANNA);
			break;
			case SET_MIN:
				t_min++;//increment t min
				if(t_min==t_max) {
					t_min=t_max-1;
				}		
				data_di=t_min;
				tmp=t_min;
				WriteEeprom_x16(ADR_T_MIN,&tmp);
			break;
			case SET_MAX:
				t_max++;//increment t max				
				if(t_max>50) {
					t_max=50;
				}		
				data_di=t_max;
				tmp=t_max;
				WriteEeprom_x16(ADR_T_MAX,&tmp);
			break;		
		}
	}
}
//------------------------------------------------
/*
void RedLedFlash() {
	if(allow_red_led_flashing==ON) {
		StartGTimer(timer_flash_red,200);
		if(ExpGTimer(timer_flash_red)) {
//			TestLedRed();
		}
	}	
}
*/
//------------------------------------------------
void ProcessNasos() {
volatile static u08 tmp_nasos_dush=0;

	if(GetMessage(MSG_KN1_FAST_PRESSED)) {
		if(tmp_nasos_dush==0) {
			tmp_nasos_dush=1;
			NasosOn();
			allow_red_led_flashing=ON;
			return;
		}
		else {
			tmp_nasos_dush=0;
			NasosOff();
			allow_red_led_flashing=OFF;
//			LedRedOff();
			return;
		}		
	}
}
//-----------------------------------------------------------
void NasosOn() {
	CB(PORT_NASOS_VANNA,NASOS_VANNA);
	allow_red_led_flashing=ON;
}
void NasosOff() {
	SB(PORT_NASOS_VANNA,NASOS_VANNA);
	allow_red_led_flashing=OFF;
	StopGTimer(timer_flash_red);
}
void InitPortsNasos() {
	SB(DDR_NASOS_VANNA,NASOS_VANNA);
	SB(PORT_NASOS_VANNA,NASOS_VANNA);
}
//-------------------------BUZZER-----------------
void BuzzerOn() {
	SB(PORT_BUZZER,BUZZER);
}
void BuzzerOff() {
	CB(PORT_BUZZER,BUZZER);
}
void BuzzerOnOff() {
	PORT_BUZZER ^= 1<<BUZZER;
}		
void InitPortsBuzzer() {
	SB(DDR_BUZZER,BUZZER);
	CB(PORT_BUZZER,BUZZER);
}
//--
void BuzzerSound() {
volatile static u08 step=10;
	if(allow_buzzer==ON) {
		switch(step) {
			case 10:
				StartGTimer(timer_buzzer,800);
				step=20;
			break;
			case 20:		
				if(ExpGTimer(timer_buzzer)) {
					BuzzerOn();
					StartGTimer(timer_buzzer,150);
					step=30;
				}
			break;
			case 30:
				if(ExpGTimer(timer_buzzer)) {
					BuzzerOff();
					step=10;
				}				
			break;				
		}		
	}
	else {
		BuzzerOff();
		StopGTimer(timer_buzzer);
		step=10;
	}		
}

//------------------------------------------------
//--------------------------------------------------
void ReadingDataFromEeprom(){
	ReadEeprom_x16 (ADR_T_MIN,&tmp);
		t_min=tmp;	
	ReadEeprom_x16 (ADR_T_MAX,&tmp);
		t_max=tmp;	
}
//--------------------------------------------------


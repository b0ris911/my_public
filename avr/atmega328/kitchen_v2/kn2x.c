#include "kn2x.h"		//change

//-------------------------------------------
void ProcessKn2(volatile u08 *flag_hold) {	//change
volatile static u08 kn_status=NOT_PRESSED;
volatile static u08 flag_press=OFF;
volatile static u08 flag_long_press=OFF;
volatile static u08 counter=0;
volatile static u16 counter_delay=0;

switch(kn_status) {
	case NOT_PRESSED:

		if(BIS(PIN_KN2,KN2)) {	//change		��������� �������
			counter=0;	//����� � �����
			return;
		}
		else {
			counter++;						
		}		
				
		if(counter<NUMBER_CHECKS_IN) 
			return;
		else {
			SendMessage(MSG_KN2_FAST_PRESSED);	//change	
			counter=0;
			counter_delay=0;
			kn_status=PRESSED;
			return;
		}
	break;
	case PRESSED:		
		if(BIC(PIN_KN2,KN2)) { //change			��������� ����������
			counter=0;

			counter_delay++;
			if(counter_delay>DELAY_PRESS) {		
				flag_press=ON;
			}

			if(counter_delay>DELAY_LONG_PRESS) {		
				flag_press=OFF;
				flag_long_press=ON;
			}		

			if(counter_delay>DELAY_HOLD) {		 
				flag_long_press=OFF;
				*flag_hold=ON;
			}		
			return;			
		}	
		else {
			counter++;
			if(counter<NUMBER_CHECKS_OUT) {
				return;
			}		
			else {
				if(flag_press==ON) {
					flag_press=OFF;
					SendMessage(MSG_KN2_PRESSED);	//change
				}		

				if(flag_long_press==ON) {
					flag_long_press=OFF;
					SendMessage(MSG_KN2_LONGPRESSED);	//change
				}		
				if(*flag_hold==ON)
					SendMessage(MSG_KN2_RELEASED);		//change			

				*flag_hold=OFF;
				counter_delay=0;
				counter=0;
				kn_status=NOT_PRESSED;
				return;
			}
		}
	break;
}//sw	
}//v
//-----------------------------------------------------------
void InitPortsKn2() {	//change
	DDR_KN2 &= ~(1<<KN2);	//change
	PORT_KN2 |= (1<<KN2);	//change
}

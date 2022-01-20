#include "releaseguard.h"

extern u08 work_mode;
extern char data_dtmf;
extern char text_ATH[];
extern char text_ATA[];
extern char text_AT_DDET[];

char code[]={"258#"}; //код снятия с охраны;l
char text_AT_VTD[]={"AT+VTD=1"};
char text_AT_VTS[]={"AT+VTS="};
char text_321[]={"\"3,2,1\""};
//----------------------------------------
void ReleaseGuard() {
volatile static u08 step=10;

	if(ExpGTimer(timer_delay_reset_release_guard)) //прождали но код не угадали
		step=197;

	switch(step) {
		case 10:
			SendTextUart(text_AT_DDET,1);	//включаем тоновый набор
			step=15;
		break;		
		case 15:
			if(GetMessage(MSG_SIM800L_OK))
				step=20;
		break;
		case 20:
			SendTextUart(text_ATA,1);		//снимаем трубку
			StartGTimer(timer_delay_reset_release_guard,TIME_DELAY_RESET_RELEASE_GUARD);
			step=25;				
		break;
		case 25:
			if(GetMessage(MSG_SIM800L_OK)) 
				step=30;				
		break;
		case 30:
			if(GetMessage(MSG_SIM800L_DTMF)) 
				step=35;
			if(GetMessage(MSG_SIM800L_NO_CARRIER)) {//если вешают трубку - переходим в рабочий режим.
				work_mode=SYSTEM_RESET;				
				return;
			}			
		break;		
		case 35:
			if(data_dtmf==code[0])		//код снятия с охраны - 258#
				step=40;						
			else
				step=30;			
		break;			
		case 40:
			if(GetMessage(MSG_SIM800L_DTMF)) 
				step=45;
			if(GetMessage(MSG_SIM800L_NO_CARRIER)) {//если вешают трубку - переходим в рабочий режим.
				work_mode=SYSTEM_RESET;				
				return;
			}			
		break;		
		case 45:
			if(data_dtmf==code[1])
				step=50;
			else
				step=30;			
		break;			
		case 50:
			if(GetMessage(MSG_SIM800L_DTMF)) 
				step=55;
			if(GetMessage(MSG_SIM800L_NO_CARRIER)) {//если вешают трубку - переходим в рабочий режим.
				work_mode=SYSTEM_RESET;				
				return;
			}			
		break;		
		case 55:
			if(data_dtmf==code[2])
				step=60;						
			else
				step=30;			
		break;		
		case 60:
			if(GetMessage(MSG_SIM800L_DTMF)) 
				step=65;
			if(GetMessage(MSG_SIM800L_NO_CARRIER)) {//если вешают трубку - переходим в рабочий режим.
				work_mode=SYSTEM_RESET;				
				return;
			}			
		break;		
		case 65:
			if(data_dtmf==code[3])
				step=70;						
			else
				step=30;			
		break;			
		case 70:
			StopGTimer(timer_delay_reset_release_guard);
//			SendTextUart(text_ATH,1);		//вешаем трубку
//			work_mode=DELAYED_START;
			step=80;
		break;		
		case 80:
			SendTextUart(text_AT_VTD,1);
			step=85;
		break;
		case 85:
			if(GetMessage(MSG_SIM800L_OK))
				step=90;
		break;
		case 90:
			SendTextUart(text_AT_VTS,0);
			SendTextUart(text_321,1);
			step=93;
		break;
		case 93:
			if(GetMessage(MSG_SIM800L_OK))
				step=95;
		break;
		case 95:
			StartGTimer(timer_delay,1000); 
			step=96;
		break;
		case 96:
			if(ExpGTimer(timer_delay)) {
				SendTextUart(text_ATH,1);		
				StartGTimer(timer_delay,1000); 
				step=97;
			}		
		break;
		case 97:
			if(GetMessage(MSG_SIM800L_OK))
				step=98;
		break;
		case 98:
			if(ExpGTimer(timer_delay)) 
				work_mode=DELAYED_START;
		break;


		case 197:							 //вешаем трубку
			SendTextUart(text_ATH,1);		
			StartGTimer(timer_delay,1000); 	//и через секунду выходим
			step=198;
		break;
		case 198:
			if(ExpGTimer(timer_delay)) 
				work_mode=SYSTEM_RESET;
		break;
}}



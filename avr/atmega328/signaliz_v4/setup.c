#include "setup.h"

extern char signal_power[];
extern char text_AT_CSQ[];
extern u08 Messages[];
extern u08 f2_hold;

char text_new_out_phone_1[]={"new_out_phone_1"};
char text_new_out_phone_2[]={"new_out_phone_2"};
char text_active[]={"act"};
char text_disable[]={"dis"};
char text_enter_setup[]={"Enter setup..."};
char text_line1[]={"L1"};
char text_line2[]={"L2"};
char text_line3[]={"L3"};
char text_ok[]={"- "};
char text_fault[]={"* "};
char text_mobile_net[]={"net: "};
char text_db[]={" dB"};
char out_phone_1[]={0,9,3,5,9,9,5,8,8,9};
char out_phone_2[]={0,9,5,2,4,0,7,1,0,7};
char in_phone_1[]={0,9,3,5,9,9,5,8,8,9};
char in_phone_2[]={0,9,3,5,9,9,5,8,8,9};
char text_out_phone_1[]={"out_phone_1:"};
char text_out_phone_2[]={"out_phone_2:"};
char text_in_phone_1[]={"in_phone_1:"};
char text_in_phone_2[]={"in_phone_2:"};
char text_set_out_phone_1[]={"set_out_phone_1:"};
char text_set_out_phone_2[]={"set_out_phone_2:"};
char text_set_status_out_phone_1[]={"status_out_ph_1"};
char text_set_status_out_phone_2[]={"status_out_ph_2"};
char text_set_status_in_phone_1[]={"status_in_ph_1"};
char text_set_status_in_phone_2[]={"status_in_ph_2"};
char text_saved[]={"Saved          "};
volatile u08 flag_activity_out_phone_1=OFF;
volatile u08 flag_activity_out_phone_2=OFF;
volatile u08 setup_mode=MAIN;
//---SetupData()-----------------------------------------------
void SetupData() {
volatile static u08 step_setup_data=5;
u08 p0=0,p1=0,p=0;
	
	StartGTimer(timer_total_reset,DELAY_TOTAL_RESET);

	switch(step_setup_data) {
		case 5:
			DDR_POWER_LCD |= 1<<POWER_LCD;	
			PORT_POWER_LCD |= 1<<POWER_LCD;	//подаем питание на дисплей, контрастность.
			_delay_ms(100);
			InitLcd();
			LcdCursorOff();
			LcdString(text_enter_setup);
			step_setup_data=6;
		break;
		case 6:
			if(GetMessage(MSG_KN2_RELEASED)) {
				step_setup_data=10;
			}
		break;
		case 10:	
			SendTextUart(text_AT_CSQ,1);//запрос на уровень сигнала сотовой сети				
			LcdClear();
			LcdGoto(100);
				//проверяем линии
			LcdString(text_line1);
			if(BIC(PIN_LINE_1,LINE_1)) {
				LcdString(text_ok);
			}		
			else{
				LcdString(text_fault);
			}	

			LcdString(text_line2);
			if(BIC(PIN_LINE_2,LINE_2)) {
				LcdString(text_ok);
			}		
			else{
				LcdString(text_fault);
			}	

			LcdString(text_line3);
			if(BIC(PIN_LINE_3,LINE_3)) {
				LcdString(text_ok);
			}		
			else{
				LcdString(text_fault);				
			}

			LcdGoto(200);
			LcdString(text_mobile_net);				
			p0=CAD(signal_power[0]);	
			p1=CAD(signal_power[1]);	
			p=p0*10+p1;												
			STrimConvert(-113+p*2,4);	
			LCD(4);		//выводим уровень сигнала
			LcdString(text_db);

			StartGTimer(timer_setup,1000);	//выводим его раз в секунду
			step_setup_data=20;	
		break;
		case 20:
			if(ExpGTimer(timer_setup)) {
				step_setup_data=10;
			}
			if(GetMessage(MSG_KN2_FAST_PRESSED)) {
				StopGTimer(timer_setup);	
				step_setup_data=30;
			}			
		break;
		case 30:
			LcdClear();
			LcdGoto(100);
			LcdString(text_out_phone_1);
			LcdGoto(200);
			for (u08 i=0;i<10;i++){
				Convert(out_phone_1[i],1);					
				LCD(1);		//выводим номер телефона 1
			}
			LcdGoto(212);	//выводим статус активности номера 1
			if(flag_activity_out_phone_1==ON)
				LcdString(text_active);
			else		
				LcdString(text_disable);			
			step_setup_data=40;	
		break;

		case 40:
			if(GetMessage(MSG_KN1_FAST_PRESSED)) { //идем устанавливать исх. номер 1
				step_setup_data=45;
			}		
			if(GetMessage(MSG_KN2_FAST_PRESSED)) {//идем показывать исх. номер 2
				step_setup_data=50;
			}
		break;
		case 45:
			if(SetupOutPhone1()==1){
				step_setup_data=50;
			}
		break;
		case 50:
			LcdClear();
			LcdGoto(100);
			LcdString(text_out_phone_2);
			LcdGoto(200);
			for (u08 i=0;i<10;i++){
				Convert(out_phone_2[i],1);					
				LCD(1);
			}							
			LcdGoto(212);
			if(flag_activity_out_phone_2==ON)
				LcdString(text_active);
			else		
				LcdString(text_disable);			
			step_setup_data=60;	
		break;
		case 60:
			if(GetMessage(MSG_KN1_FAST_PRESSED)) { //идем устанавливать исх. номер 2
				step_setup_data=65;
			}		
			if(GetMessage(MSG_KN2_FAST_PRESSED)) {//идем показывать вх. номер 1
				step_setup_data=70;
			}
		break;
		case 65:
			if(SetupOutPhone2()==1){
				step_setup_data=70;
			}
		break;
		case 70:	//смотрим входящий номер 1 
			LcdClear();
			LcdGoto(100);
			LcdString(text_in_phone_1);
			LcdGoto(200);
			for (u08 i=0;i<10;i++){
				Convert(in_phone_1[i],1);					
				LCD(1);
			}							
			step_setup_data=80;	
		break;
		case 80:
			if(GetMessage(MSG_KN1_FAST_PRESSED)) { //идем устанавливать вх. номер 1
				step_setup_data=85;
			}		
			if(GetMessage(MSG_KN2_FAST_PRESSED)) {//идем показывать вх. номер 2
				step_setup_data=90;
			}
		break;
		case 85:
			if(SetupInPhone1()==1){ //устанавливаем входящий номер 1
				step_setup_data=90;
			}
		break;
//*-*-*
		case 90:	//смотрим входящий номер 2 
			LcdClear();
			LcdGoto(100);
			LcdString(text_in_phone_2);
			LcdGoto(200);
			for (u08 i=0;i<10;i++){
				Convert(in_phone_2[i],1);					
				LCD(1);
			}							
			step_setup_data=100;	
		break;
		case 100:
			if(GetMessage(MSG_KN1_FAST_PRESSED)) { //идем устанавливать вх. номер 1
				step_setup_data=105;
			}		
			if(GetMessage(MSG_KN2_FAST_PRESSED)) {
				step_setup_data=10;
			}
		break;
		case 105:
			if(SetupInPhone2()==1){
				step_setup_data=10;
			}
		break;
	}
}
//--------------------------------------------------
u08 SetupOutPhone1() {
volatile static u08 step_setup_out_phone_1=5,i=0;
u08 tmp=0;
switch (step_setup_out_phone_1) {
	case 5:
		LcdGoto(100);
		LcdString(text_set_out_phone_1);		
		LcdCursorCube();
		LcdGoto(200);	
		//читаем номер из памяти
		for(u08 i=0;i<10;i++) {
			ReadEeprom_x8 (adr_out_phone_1+i,&tmp);
			out_phone_1[i]=tmp;
		}
		 //читаем статус активности из памяти
		ReadEeprom_x8 (adr_flag_activity_out_phone_1,&tmp);
		flag_activity_out_phone_1=tmp;

		step_setup_out_phone_1=10;		
	break;
		
	case 10:// вводим новый номер
		if(GetMessage(MSG_KN1_FAST_PRESSED)){
			out_phone_1[i]++;
			if(out_phone_1[i]>9) {
				out_phone_1[i]=0;
			}	
			LcdGoto(200+i);	
			Convert(out_phone_1[i],1);
			LCD(1);
			LcdGoto(200+i);
		}
		if(GetMessage(MSG_KN2_FAST_PRESSED)){ //или меняем цифру
			i++;
			LcdGoto(200+i);
			if(i>9) {
				i=0;
				LcdGoto(213);				
				step_setup_out_phone_1=15;				
			}		
		}			
	break;
	case 15:	//устанавливаем статус активности номера 1
		if(GetMessage(MSG_KN1_FAST_PRESSED)){ 
			if(flag_activity_out_phone_1==ON) {
				flag_activity_out_phone_1=OFF;
				LcdGoto(212);
				LcdString(text_disable);
				LcdGoto(213);
			}		
			else {
				flag_activity_out_phone_1=ON;
				LcdGoto(212);
				LcdString(text_active);
				LcdGoto(213);
			}		
		}
		if(GetMessage(MSG_KN2_FAST_PRESSED)){ 
			for(u08 k=0;k<10;k++) {
				tmp=out_phone_1[k];
				WriteEeprom_x8 (adr_out_phone_1+k,&tmp);
			}		
			
			tmp=flag_activity_out_phone_1;
			WriteEeprom_x8 (adr_flag_activity_out_phone_1,&tmp);//сохраняем		
							
			LcdGoto(200);	
			LcdString(text_saved);	//показываем Saved и пауза 2 с
			_delay_ms(2000);
			LcdCursorOff();
			step_setup_out_phone_1=30;
		}		
	break;
	case 30://проверочное чтение 
		for(u08 i=0;i<10;i++) {
			ReadEeprom_x8 (adr_out_phone_1+i,&tmp);
			out_phone_1[i]=tmp;
		}
		ReadEeprom_x8 (adr_flag_activity_out_phone_1,&tmp);
		flag_activity_out_phone_1=tmp;

		step_setup_out_phone_1=35;
	
	case 35:	//показываем проверочные данные
		LcdClear(); 
		LcdGoto(100);
		LcdString(text_new_out_phone_1);		
		LcdGoto(200);	//показываем что записали
		for (u08 i=0;i<10;i++){
			Convert(out_phone_1[i],1);					
			LCD(1);
		}
		LcdGoto(212);	//выводим статус активности номера 1
		if(flag_activity_out_phone_1==ON)
			LcdString(text_active);
		else		
			LcdString(text_disable);
			LcdGoto(214);
		step_setup_out_phone_1=40;									
	break;
			
	case 40://выходим
		if(GetMessage(MSG_KN2_FAST_PRESSED)){ 
			step_setup_out_phone_1=5;
			i=0;
			return 1;
		}			
	break;

}
return 0;
}
//--------------------------------------------------
u08 SetupOutPhone2() {
volatile static u08 step_setup_out_phone_2=5,i=0;
u08 tmp=0;
switch (step_setup_out_phone_2) {
	case 5:
		LcdGoto(100);
		LcdString(text_set_out_phone_2);		
		LcdCursorCube();
		LcdGoto(200);	
		//читаем номер из памяти
		for(u08 i=0;i<10;i++) {
			ReadEeprom_x8 (adr_out_phone_2+i,&tmp);
			out_phone_2[i]=tmp;
		}
		 //читаем статус активности из памяти
		ReadEeprom_x8 (adr_flag_activity_out_phone_2,&tmp);
		flag_activity_out_phone_2=tmp;

		step_setup_out_phone_2=10;		
	break;
		
	case 10:// вводим новый номер
		if(GetMessage(MSG_KN1_FAST_PRESSED)){
			out_phone_2[i]++;
			if(out_phone_2[i]>9) {
				out_phone_2[i]=0;
			}	
			LcdGoto(200+i);	
			Convert(out_phone_2[i],1);
			LCD(1);
			LcdGoto(200+i);
		}
		if(GetMessage(MSG_KN2_FAST_PRESSED)){ //или меняем цифру
			i++;
			LcdGoto(200+i);
			if(i>9) {
				i=0;
				LcdGoto(213);				
				step_setup_out_phone_2=15;				
			}		
		}			
	break;
	case 15:	//устанавливаем статус активности номера 1
		if(GetMessage(MSG_KN1_FAST_PRESSED)){ 
			if(flag_activity_out_phone_2==ON) {
				flag_activity_out_phone_2=OFF;
				LcdGoto(212);
				LcdString(text_disable);
				LcdGoto(213);
			}		
			else {
				flag_activity_out_phone_2=ON;
				LcdGoto(212);
				LcdString(text_active);
				LcdGoto(213);
			}		
		}
		if(GetMessage(MSG_KN2_FAST_PRESSED)){ 
			for(u08 k=0;k<10;k++) {
				tmp=out_phone_2[k];
				WriteEeprom_x8 (adr_out_phone_2+k,&tmp);
			}		
			
			tmp=flag_activity_out_phone_2;
			WriteEeprom_x8 (adr_flag_activity_out_phone_2,&tmp);//сохраняем		
							
			LcdGoto(200);	
			LcdString(text_saved);	//показываем Saved и пауза 2 с
			_delay_ms(2000);
			LcdCursorOff();
			step_setup_out_phone_2=30;
		}		
	break;
	case 30://проверочное чтение 
		for(u08 i=0;i<10;i++) {
			ReadEeprom_x8 (adr_out_phone_2+i,&tmp);
			out_phone_2[i]=tmp;
		}
		ReadEeprom_x8 (adr_flag_activity_out_phone_2,&tmp);
		flag_activity_out_phone_2=tmp;

		step_setup_out_phone_2=35;
	
	case 35:	//показываем проверочные данные
		LcdClear(); 
		LcdGoto(100);
		LcdString(text_new_out_phone_2);		
		LcdGoto(200);	//показываем что записали
		for (u08 i=0;i<10;i++){
			Convert(out_phone_2[i],1);					
			LCD(1);
		}
		LcdGoto(212);	//выводим статус активности номера 1
		if(flag_activity_out_phone_2==ON)
			LcdString(text_active);
		else		
			LcdString(text_disable);
			LcdGoto(214);
		step_setup_out_phone_2=40;									
	break;
			
	case 40://выходим
		if(GetMessage(MSG_KN2_FAST_PRESSED)){ 
			step_setup_out_phone_2=5;
			i=0;
			return 1;
		}			
	break;

}
return 0;
}
//--------------------------------------------------

//--------------------------------------------------
u08 CAD(char data) {
if((data>47)&&(data<58))
	return	data-48;	
else
	return 0;
} 

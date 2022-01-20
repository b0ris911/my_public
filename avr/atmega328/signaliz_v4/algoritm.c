#include "algoritm.h"

extern char out_phone_1[];
extern char out_phone_2[];
extern char in_phone_1[];
extern char in_phone_2[];
extern u08 flag_activity_out_phone_1;
extern u08 flag_activity_out_phone_2;
extern char data_dtmf;
char text_incoming_phone[]={"incoming_phone"};
char text_incoming_unknown_phone[]={"incoming_unknown_phone"};
char text_ATH[]={"ATH"};
char text_AT_DDET[]={"AT+DDET=1"};	//�������� ������� �����
char text_ATE[]={"ATE0"};//��������� ���
char text_ATD[]={"ATD+38"};//������� �����
char text_AT[]={"AT"};
char text_ATA[]={"ATA"};//������� �����
char text_coldot[]={";"};
char text_AT_CCALR[]={"AT+CCALR?"};//������ ���������� � ��������� �������
char text_AT_CSQ[]={"AT+CSQ"};//������� ������� ������� ����
char text_AT_CLIP_ON[]={"AT+CLIP=1"};//�������� ���������������� ������

char text_sleep[]={"I go to sleep. Bye!"};
char text_lines_ok[]={"Lines are ok."};
char text_lines_are_broke[]={"Lines are broke. Alarm! "};
//char text_delayed_start[]={"Was delayed start..."};
char text_reset_sim800l[]={"RESET_SIM800L"};
char text_program_reset[]={"AT+CFUN=1,1"};
char text_all_attempts_have_ended[]={"All attempts have ended."};
volatile u08 work_mode=TEST_SIM800L;
volatile u08 system_reset_counter=0;
char tmp_buffer[10];
volatile u08 was_call_to_phone_1=NO;
volatile u08 was_call_to_phone_2=NO;
volatile u08 allow_power_off=NO;

//--------------------------------------------
void AlarmSirena() {
volatile static u08 step=10;
	switch(step) {
		case 10:
			PORT_ALARM_TONE &= ~(1<<ALARM_TONE);//�������� �����
			step=20;
			StartGTimer(timer_sirena_off,TIME_SIRENA_OFF);
		break;

		case 20:
			StartGTimer(timer_sirena,500);
			if(ExpGTimer(timer_sirena)) 
				PORT_SIRENA ^= 1<<SIRENA;//���� ������

			if(ExpGTimer(timer_sirena_off)) {
				PORT_SIRENA |= (1<<SIRENA);//����. ������
				PORT_ALARM_TONE |= (1<<ALARM_TONE);//����. �����
				step=30;
			}		
		break;
		case 30:
			allow_power_off=YES;//��������� ������� � ������ �����
			step=40;
		break;
		case 40:
		break;
	}
}
//--------------------------------------------
void MainAlgorithm() {
volatile static u08 step_test_sim800l=5;
	if((work_mode!=TEST_SIM800L) && (ExpGTimer(timer_inc_counter_system_reset))) {		
		system_reset_counter++;	//�� ������ ��������� ������ � ������ �������
	}		

switch(work_mode) {
//---INCOMING_CALL--------------------
	case INCOMING_CALL:
		if((GetMessage(MSG_SIM800L_INCOMING_PHONE_1))||(GetMessage(MSG_SIM800L_INCOMING_PHONE_2))){
			SendTextUart(text_incoming_phone,1);													
			work_mode=RELEASE_GUARD;
		}		
		if(GetMessage(MSG_SIM800L_INCOMING_UNKNOWN)) {
			SendTextUart(text_ATH,1);
			work_mode=TEST_SIM800L;
		}															
		if(BIS(PIN_INCOMING_SIM800L,INCOMING_SIM800L)) {//������ ��� ���������
			work_mode=TEST_SIM800L;
		}		
	break;
//---RELEASE_GUARD--------------------
	case RELEASE_GUARD:		//������� � ������
		ReleaseGuard();
	break;
//---TEST_SIM800L--------------------
	case TEST_SIM800L:
		switch(step_test_sim800l){
			case 5:
				SendTextUart(text_AT,1);//������������� ����� � UART	
				step_test_sim800l=10;
			break;

			case 10:
				if(GetMessage(MSG_SIM800L_OK)) {					
					step_test_sim800l=15;					
				}		
				if(ExpGTimer(timer_inc_counter_system_reset)) {//���� ��� ������, �������� AT ��� ���
					step_test_sim800l=5;
					system_reset_counter++;
				}		
			break;
			case 15:
//				SendTextUart(text_ATE,1);	//��������� ���
//				step_test_sim800l=16;
				step_test_sim800l=20;
			break;
			case 16:
				if(GetMessage(MSG_SIM800L_OK))
					step_test_sim800l=20;
				if(ExpGTimer(timer_inc_counter_system_reset)) {//���� ��� ������, �������� �������
					step_test_sim800l=5;
					system_reset_counter++;
				}		
			break;		
			case 20:
				SendTextUart(text_AT_CCALR,1);	//	��������� ���������� �������
				step_test_sim800l=30;
			break;

			case 30:
				if(GetMessage(MSG_SIM800L_CCALR1)) {
					step_test_sim800l=40;
					return;				
				}			
				if(GetMessage(MSG_SIM800L_CCALR0)) {	//���� ������ ��� �� ����� ������� - ��������
					StartGTimer(timer_delay_ccalr,3000);
					step_test_sim800l=31;
					return;
				}
				if(ExpGTimer(timer_inc_counter_system_reset)) {//���� ��� ������, �������� �������
					step_test_sim800l=5;
					system_reset_counter++;
					return;
				}		
			break;
			case 31:
				if(ExpGTimer(timer_delay_ccalr)) {	
					step_test_sim800l=20;					
					system_reset_counter++;					
				}		
			break;
			case 40:
				SendTextUart(text_AT_CLIP_ON,1);	//�������� ���������������� ������				
				step_test_sim800l=45;
			break;
			case 45:
				if(GetMessage(MSG_SIM800L_OK))
					step_test_sim800l=70;
				if(ExpGTimer(timer_inc_counter_system_reset)) {//���� ��� ������, �������� AT ��� ���
					step_test_sim800l=5;
					system_reset_counter++;
				}		
			break;
/*			case 50:
				SendTextUart(text_AT_CSQ,1);	
				step_test_sim800l=60;
			break;
			case 60:
				if(GetMessage(MSG_SIM800L_CSQ)) {					
					step_test_sim800l=70;					
				}
			break;
*/			case 70:
				work_mode=TEST_LINES;
			break;
		}
	break;
//---TEST_LINES--------------------
	case TEST_LINES:
		if((BIC(PIN_LINE_1,LINE_1))&&(BIC(PIN_LINE_2,LINE_2))&&(BIC(PIN_LINE_3,LINE_3))){
		//���� ��� ����� ��������� � �����
			SendTextUart(text_lines_ok,1);
			work_mode=ALL_OK;
		}
		else {
			SendTextUart(text_lines_are_broke,1);
			work_mode=BROKEN_LINES;
		}		
	break;
//---SETUP--------------------
	case SETUP:
//		WDT_off();
		SetupData();
	break;
//---BROKE_LINES--------------------
		volatile static u08 step_broke_lines=10;
		volatile static u08 counter1=0,counter2=0;
	case BROKEN_LINES:
		AlarmSirena();		//�������� ������
		switch(step_broke_lines) {			
			case 10://�������� � ������� 1
				if((flag_activity_out_phone_1==ON)&&(was_call_to_phone_1==NO)) {//���� ������� �� ���� ����� ���������
					for(u08 i=0;i<10;i++) //�������� ����� 
						tmp_buffer[i]=out_phone_1[i]+48;
						SendTextUart(text_ATD,0);
						SendTextUart(tmp_buffer,0);
						SendTextUart(text_coldot,1);
						step_broke_lines=20;
				}
				else {//���� ������� �� ���� ����� ���������
					step_broke_lines=30;		
					was_call_to_phone_1=YES;	//������� ��� ��� ���������
				}		
			break;
			case 20:
				if( (GetMessage(MSG_SIM800L_NO_ANSWER))||
					(GetMessage(MSG_SIM800L_BUSY))|| 
					(GetMessage(MSG_SIM800L_NO_DIALTONE))){
					step_broke_lines=10;
					counter1++;
					if(counter1<KOLVO_POPYTOK_DOZVONA) {//���� ��� ������ - ���������
						step_broke_lines=10;
					}								
					else {
						was_call_to_phone_1=NO;		
						step_broke_lines=30;//�� ��������� - ������ �� ������� ������
					}		
				}
				if (GetMessage(MSG_SIM800L_NO_CARRIER)) { //���� �������� ������ ���� �������
					was_call_to_phone_1=YES;
					step_broke_lines=30;//�� ������� ������
				}		
			break;
			case 30://�������� � ������� 2
				if((flag_activity_out_phone_2==ON)&&(was_call_to_phone_2==NO)){//���� ������� �� ���� ����� ���������
					for(u08 i=0;i<10;i++) //�������� ����� 
						tmp_buffer[i]=out_phone_2[i]+48;
						SendTextUart(text_ATD,0);
						SendTextUart(tmp_buffer,0);
						SendTextUart(text_coldot,1);
						step_broke_lines=40;
				}
				else {//���� ������� �� ���� ����� ���������
					step_broke_lines=50;
					was_call_to_phone_2=YES;	//������� ��� ��� ���������
				}								
			break;
			case 40:
				if( (GetMessage(MSG_SIM800L_NO_ANSWER))||
					(GetMessage(MSG_SIM800L_BUSY))|| 
					(GetMessage(MSG_SIM800L_NO_DIALTONE))){
					step_broke_lines=30;
					counter2++;
					if(counter2<KOLVO_POPYTOK_DOZVONA) {//���� ��� ������ - ���������
						step_broke_lines=30;
					}								
					else {
						was_call_to_phone_2=NO;		
						step_broke_lines=50;//�� ��������� - ������� � �������� ������� ����� �������
					}		
				}
				if (GetMessage(MSG_SIM800L_NO_CARRIER)) { //���� �������� ������ ���� ������
					was_call_to_phone_2=YES;
					step_broke_lines=50;
				}		
			break;
			case 50:
				if((was_call_to_phone_1==YES)&&(was_call_to_phone_2==YES)) {//���� ������ ����� ��� ������ - ������� ������ �� �����
					step_broke_lines=60;
				}
				else{
					StartGTimer(timer_delay_repeat_alarm_calling,TIME_DELAY_REPEAT_ALARM_CALLING);
					step_broke_lines=51;
				}			
			break;

				volatile static u08 counter_total_repeats=0;
			case 51:
				if(ExpGTimer(timer_delay_repeat_alarm_calling)) {
					counter1=0;
					counter2=0;
					step_broke_lines=10;
					counter_total_repeats++;
					if(counter_total_repeats>3) {
						step_broke_lines=60;
						SendTextUart(text_all_attempts_have_ended,1);
					}		
				}
			break;

//				volatile static u08 step_sleep_after_alarm=0;
			case 60:
				if(allow_power_off==YES){
					work_mode=POWER_OFF; //��������� � ������ �����
					step_broke_lines=70;
				}		
/*				switch(step_sleep_after_alarm) {
					case 0:
						SendTextUart(text_sleep,1);
						StartGTimer(timer_power_down,100);
						step_sleep_after_alarm=1;
					break;
					case 1:
						if(ExpGTimer(timer_power_down)){
							PORT_LINE_1 &= ~(1<<LINE_1);
							PORT_LINE_2 &= ~(1<<LINE_2);
							PORT_LINE_3 &= ~(1<<LINE_3);
							sleep_power_down_enable();
							SLEEP
						}		
					break;		
				}		
*/			break;
			case 70:
			break;
		}//sw	
	break;			
//---SYSTEM_RESET--------------------
	case SYSTEM_RESET:
		WDT_off();
		WDT_Prescaler_Change_2s();
		sleep_power_down_enable();
		SLEEP
		return;
	break;
//---POWER_OFF------------------------
	case POWER_OFF:
		WDT_off();
		sleep_power_down_enable();
		SLEEP
		return;
	break;
//---DELAYED_START--------------------
	case DELAYED_START:
		WDT_off();
		
		for(u08 i=0;i<TIME_DELAYED_START;i++) {
			LedRedOn();
			CLI
			_delay_ms(500);
			SEI
			LedRedOff();
			CLI
			_delay_ms(500);
			SEI
		}
//n		SendTextUart(text_delayed_start,1);
		work_mode=SYSTEM_RESET;
	break;
//---ALL_OK--------------------
	volatile static u08 step_all_ok=0;
	case ALL_OK:
		switch(step_all_ok) {
			case 0:
				SendTextUart(text_sleep,1);
				StartGTimer(timer_power_down,100);
				step_all_ok=1;
			break;
			case 1:
				if(ExpGTimer(timer_power_down)){
					PORT_LINE_1 &= ~(1<<LINE_1);
					PORT_LINE_2 &= ~(1<<LINE_2);
					PORT_LINE_3 &= ~(1<<LINE_3);
			/*		DDRB=1;
					PORTB=0;
					DDRC=1;
					PORTC=0b00111000;
					DDRD=1;
					PORTD=0b00000011;
			*/	
					work_mode=SYSTEM_RESET;
				}		
			break;		
		}		
	break;
}
}

//--------------------------------------------------
void ReadingFromEeprom(){
u08 i=0,tmp=0;
	for(i=0;i<10;i++) {
		ReadEeprom_x8 (adr_out_phone_1+i,&tmp);
		out_phone_1[i]=tmp;
	}
	for(i=0;i<10;i++) {
		ReadEeprom_x8 (adr_out_phone_2+i,&tmp);
		out_phone_2[i]=tmp;
	}
	for(i=0;i<10;i++) {
		ReadEeprom_x8 (adr_in_phone_1+i,&tmp);
		in_phone_1[i]=tmp;
	}
	for(i=0;i<10;i++) {
		ReadEeprom_x8 (adr_in_phone_2+i,&tmp);
		in_phone_2[i]=tmp;
	}
		ReadEeprom_x8 (adr_flag_activity_out_phone_1,&tmp);
		flag_activity_out_phone_1=tmp;

		ReadEeprom_x8 (adr_flag_activity_out_phone_2,&tmp);
		flag_activity_out_phone_2=tmp;
}
//--------------------------------------------------
void InitPortsSim800L() {
	DDR_RESET_SIM800L |= 1<<RESET_SIM800L;
	PORT_RESET_SIM800L |= 1<<RESET_SIM800L;

	DDR_INCOMING_SIM800L &= ~(1<<INCOMING_SIM800L);
	PORT_INCOMING_SIM800L |= 1<<INCOMING_SIM800L;
}
void InitTestLines() {
	DDR_LINE_1 &= ~(1<<LINE_1);
	PORT_LINE_1 |= (1<<LINE_1);

	DDR_LINE_2 &= ~(1<<LINE_2);
	PORT_LINE_2 |= (1<<LINE_2);

	DDR_LINE_3 &= ~(1<<LINE_3);
	PORT_LINE_3 |= (1<<LINE_3);
}
//--------------------------------------------
void ResetSim800L() {
	PORT_RESET_SIM800L &= ~(1<<RESET_SIM800L);
	CLI
	_delay_ms(100);
	SEI
	PORT_RESET_SIM800L |= (1<<RESET_SIM800L);
}


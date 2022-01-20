#include "KN2.h"

extern u08 f2_hold;	//CHANGE
extern u08 main_mode;
extern u08 holder;
//------------------------
void InitPortsKn2() {			//CHANGE
	DDR_KN2 &= ~(1<<KN2);		//CHANGE	
	PORT_KN2 |= (1<<KN2);		//CHANGE
	
}
//------------------------
void ProcessKn2(uint8_t *pf2_hold) {	//CHANGE
volatile static uint8_t counter=2;
volatile static uint8_t f_1=1;
volatile static uint8_t f_2=0;
volatile static uint8_t f_5=0;
volatile static uint16_t cnt_long=0;
volatile static uint8_t f_long=0;

		if (f_1==0) 						//���� ������ ���� ��� ������				
			goto counting_kn;						//���� �� ��������
		if (BIC(PIN_KN2,KN2)) 	//CHANGE	//���� ������ ������
			goto kn_a;						
		return;						
kn_a:
		f_1=0;						// ���� "������ ������" �������  
		counter=2;						//���������� ��������

counting_kn:		
		counter--;						
		if (counter!=0)					
			return;		
		if (f_5==1) 				//���� ������ ���� ��� ������	
			goto kn_b;					
		if ((BIC(PIN_KN2,KN2)))	//CHANGE	// �������� ���������� �������			
			goto kn_c;						
		else
			goto clean_flags;							
kn_c:	
		f_5=1;							//fknr 5=1 - ������ ������������� ������
		DoFastK2();		//CHANGE

kn_b:
		if (f_2==0)						// 0 - ���� �������, 1 - ���� ����������
			goto repeat_reading;			
		else	
			goto release_kn;
repeat_reading:					
		if ((BIC(PIN_KN2,KN2))) //CHANGE	// ��������� ���������� ������
			goto kn_d;						
		else
			goto kn_e;						
kn_d:	
		counter=2;							//!!! �������� �2 (���������) ��� ������� ������ 
		cnt_long++;
		if((cnt_long>=15)&&(cnt_long<50))
			f_long=1;			
					
		if (cnt_long>=50) {
			*pf2_hold=1;	//CHANGE
			holder|=1<<2;
		}
		return;
	
kn_e:
		f_2=1;					//������ 2 ��� �.�. ���� ����������
		counter=2;				// !!! �������� �4 - ��� ���������� (20)
		return;			

release_kn:
	if ((f_long==0)&&(*pf2_hold==0))	//CHANGE
		DoK2();							//CHANGE
	if ((f_long==1)&&(*pf2_hold==0))	//CHANGE
		DoK2Long();						//CHANGE
	if (*pf2_hold==1)					//CHANGE
		DoK2ReleaseAfterHold(&f2_hold);	//CHANGE

		f_long=0;
		cnt_long=0;

clean_flags:
		f_1=1;								
		f_2=0;							
		f_5=0;

		return;
	
}//void
//----------------------------------------
void DoFastK2(){	//CHANGE
	SendMessage(MSG_KN2_FAST_PRESSED);	//CHANGE
	StopGTimer(timer_total_reset);
	StartGTimer(timer_total_reset,DELAY_TOTAL_RESET);
}
//----------------------------------------
void DoK2(){			//CHANGE
	SendMessage(MSG_KN2_PRESSED);		//CHANGE
}
//----------------------------------------
void DoK2Long(){			//CHANGE
	SendMessage(MSG_KN2_LONGPRESSED);		//CHANGE	
}
//----------------------------------------
void DoK2ReleaseAfterHold(uint8_t *pf2_hold){		//CHANGE
	SendMessage(MSG_KN2_RELEASED);		//CHANGE
	*pf2_hold=0;						//CHANGE
	holder &= ~(1<<2);
}


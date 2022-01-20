#include "KN1.h"

extern u08 f1_hold;
extern u08 main_mode;
extern u08 holder;
//------------------------
void InitPortsKn1() {
	DDR_KN1 &= ~(1<<KN1);
	PORT_KN1 |= (1<<KN1);
}
//------------------------
void ProcessKn1(uint8_t *pf1_hold) {	
volatile static uint8_t counter=2;
volatile static uint8_t f_1=1;
volatile static uint8_t f_2=0;
volatile static uint8_t f_5=0;
volatile static uint16_t cnt_long=0;
volatile static uint8_t f_long=0;

		if (f_1==0) 						//если кнопка была уже нажата				
			goto counting_kn;						//идем на задержку
		if (BIC(PIN_KN1,KN1)) 			//если кнопка нажата
			goto kn_a;						
		return;						
kn_a:
		f_1=0;						// флаг "кнопка отжата" сброшен  
		counter=2;						//установили задержку

counting_kn:		
		counter--;						
		if (counter!=0)					
			return;		
		if (f_5==1) 				//если кнопка была уже нажата	
			goto kn_b;					
		if ((BIC(PIN_KN1,KN1)))		// проверка случайного нажатия			
			goto kn_c;						
		else
			goto clean_flags;							
kn_c:	
		f_5=1;							//fknr 5=1 - кнопка действительно нажата
		DoFastK1();

kn_b:
		if (f_2==0)						// 0 - было нажатие, 1 - было отпускание
			goto repeat_reading;			
		else	
			goto release_kn;
repeat_reading:					
		if ((BIC(PIN_KN1,KN1))) 	// повторное считывание кнопок
			goto kn_d;						
		else
			goto kn_e;						
kn_d:	
		counter=2;							//!!! задержка №2 (повторная) при нажатой кнопке (5)
		cnt_long++;
		if((cnt_long>=15)&&(cnt_long<50))
			f_long=1;			
					
		if (cnt_long>=50) {
			*pf1_hold=1;
			holder|=1<<1;
		}
		return;
	
kn_e:
		f_2=1;				//ставим 2 бит т.к. было отпускание
		counter=2;				// !!! задержка №4 - при отпускании (20)
		return;			

release_kn:
	if ((f_long==0)&&(*pf1_hold==0))
		DoK1();
	if ((f_long==1)&&(*pf1_hold==0))
		DoK1Long();
	if (*pf1_hold==1)
		DoK1ReleaseAfterHold(&f1_hold);

		f_long=0;
		cnt_long=0;

clean_flags:
		f_1=1;								
		f_2=0;							
		f_5=0;

		return;
	
}//void
//----------------------------------------
void DoFastK1(){
	SendMessage(MSG_KN1_FAST_PRESSED);
	StopGTimer(timer_total_reset);
	StartGTimer(timer_total_reset,DELAY_TOTAL_RESET);
}
//----------------------------------------
void DoK1(){
	SendMessage(MSG_KN1_PRESSED);
}
//--------------------------------------
void DoK1Long(){
	SendMessage(MSG_KN1_LONGPRESSED);
}
//--------------------------------------
void DoK1ReleaseAfterHold(uint8_t *pf1_hold){
	SendMessage(MSG_KN1_RELEASED);
	*pf1_hold=0;
	holder &= ~(1<<1);
}
//--------------------------------------


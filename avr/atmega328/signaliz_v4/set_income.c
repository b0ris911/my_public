#include "set_income.h"

extern char in_phone_1[];
extern char in_phone_2[];
extern char in_phone_3[];
extern char text_saved[];

char text_set_in_phone_1[]={"set_in_phone_1:"};
char text_set_in_phone_2[]={"set_in_phone_2:"};
char text_new_in_phone_1[]={"new_in_phone_1"};
char text_new_in_phone_2[]={"new_in_phone_2"};

u08 SetupInPhone1() {
//--------------------------------------------------
volatile static u08 step_setup_in_phone_1=5,i=0;
u08 tmp=0;
switch (step_setup_in_phone_1) {
	case 5:
		LcdGoto(100);
		LcdString(text_set_in_phone_1);		
		LcdCursorCube();
		LcdGoto(200);	
		//читаем номер из памяти
		for(u08 i=0;i<10;i++) {
			ReadEeprom_x8 (adr_in_phone_1+i,&tmp);
			in_phone_1[i]=tmp;
		}
		step_setup_in_phone_1=10;		
	break;
		
	case 10:// вводим новый номер
		if(GetMessage(MSG_KN1_FAST_PRESSED)){
			in_phone_1[i]++;
			if(in_phone_1[i]>9) {
				in_phone_1[i]=0;
			}
				
			LcdGoto(200+i);	
			Convert(in_phone_1[i],1);
			LCD(1);
			LcdGoto(200+i);
		}
		if(GetMessage(MSG_KN2_FAST_PRESSED)){ //или меняем цифру
			i++;
			LcdGoto(200+i);
			if(i>9) {
				i=0;
				LcdGoto(215);
				step_setup_in_phone_1=15;				
			}		
		}			
	break;
	case 15:
			for(u08 k=0;k<10;k++) {
				tmp=in_phone_1[k];
				WriteEeprom_x8 (adr_in_phone_1+k,&tmp);//записали вх. номер 1
			}			
			LcdGoto(200);	
			LcdString(text_saved);	//показываем Saved и пауза 2 с
			StartGTimer(timer_delay,2000);
			step_setup_in_phone_1=20;
	break;			
	case 20:
		if(ExpGTimer(timer_delay)) {			
			LcdCursorOff();
			step_setup_in_phone_1=30;
		}		
	break;
	case 30://проверочное чтение 
		for(u08 i=0;i<10;i++) {
			ReadEeprom_x8 (adr_in_phone_1+i,&tmp);
			in_phone_1[i]=tmp;
		}

		step_setup_in_phone_1=35;
	
	case 35:	//показываем проверочные данные
		LcdClear(); 
		LcdGoto(100);
		LcdString(text_new_in_phone_1);		
		LcdGoto(200);	//показываем что записали
		for (u08 i=0;i<10;i++){
			Convert(in_phone_1[i],1);					
			LCD(1);
		}
		step_setup_in_phone_1=40;									
	break;
			
	case 40://выходим
		if(GetMessage(MSG_KN2_FAST_PRESSED)){ 
			step_setup_in_phone_1=5;
			i=0;
			return 1;
		}			
	break;

}
return 0;
}

//-------------------------------------------------
u08 SetupInPhone2() {
volatile static u08 step_setup_in_phone_2=5,i=0;
u08 tmp=0;
switch (step_setup_in_phone_2) {
	case 5:
		LcdGoto(100);
		LcdString(text_set_in_phone_2);		
		LcdCursorCube();
		LcdGoto(200);	
		//читаем номер из памяти
		for(u08 i=0;i<10;i++) {
			ReadEeprom_x8 (adr_in_phone_2+i,&tmp);
			in_phone_2[i]=tmp;
		}

		step_setup_in_phone_2=10;		
	break;
		
	case 10:// вводим новый номер
		if(GetMessage(MSG_KN1_FAST_PRESSED)){
			in_phone_2[i]++;
			if(in_phone_2[i]>9) {
				in_phone_2[i]=0;
			}	
			LcdGoto(200+i);	
			Convert(in_phone_2[i],1);
			LCD(1);
			LcdGoto(200+i);
		}
		if(GetMessage(MSG_KN2_FAST_PRESSED)){ //или меняем цифру
			i++;
			LcdGoto(200+i);
			if(i>9) {
				i=0;
				LcdGoto(213);				
				step_setup_in_phone_2=15;				
			}		
		}			
	break;
	case 15:	
			for(u08 k=0;k<10;k++) {
				tmp=in_phone_2[k];
				WriteEeprom_x8 (adr_in_phone_2+k,&tmp);
			}					
							
			LcdGoto(200);	
			LcdString(text_saved);	//показываем Saved и пауза 2 с
			StartGTimer(timer_delay,2000);
			step_setup_in_phone_2=20;
	break;	
			
	case 20:
		if(ExpGTimer(timer_delay)) {			
			LcdCursorOff();
			step_setup_in_phone_2=30;
		}		
	break;

	case 30://проверочное чтение 
		for(u08 i=0;i<10;i++) {
			ReadEeprom_x8 (adr_in_phone_2+i,&tmp);
			in_phone_2[i]=tmp;
		}

		step_setup_in_phone_2=35;
	
	case 35:	//показываем проверочные данные
		LcdClear(); 
		LcdGoto(100);
		LcdString(text_new_in_phone_2);		
		LcdGoto(200);	//показываем что записали
		for (u08 i=0;i<10;i++){
			Convert(in_phone_2[i],1);					
			LCD(1);
		}
		step_setup_in_phone_2=40;									
	break;
			
	case 40://выходим
		if(GetMessage(MSG_KN2_FAST_PRESSED)){ 
			step_setup_in_phone_2=5;
			i=0;
			return 1;
		}			
	break;

}
return 0;
}//-------------------------------------------------


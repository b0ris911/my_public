#include "din_ind.h"

extern volatile u08 work_mode;

volatile u08 d0r,d1r,d2r,d3r,segm;
volatile s16 digit;
//-----------------------------------------------
volatile u08 display_mode=TEMP;	
//----------------------------------
//----------------------------ДИНАМИЧЕСКАЯ ИНДИКАЦИЯ----------------------------------------------------------
void minus() {
volatile static u08 step=0;
volatile static u08 timer=0;
	timer++;
	if (timer==20) {
		timer=0;
		step++;
		if(step==2)
			step=0;
	}			
	switch (step) {
		case 0:
			SB(port_dp,bit_dp);
		break;
		case 1:
			CB(port_dp,bit_dp);
		break;
	}//sw
}//v
//--------------------------------------
void di(volatile s16 digit) {
volatile static u08 crazr=2;
volatile static u08 tmp;
volatile static s16 dig;
	
		if (digit<0)
			dig=-digit;			
		else 
			dig=digit;			
		tmp=dig/10;
		d0r=dig%10;
		d1r=tmp%10;
		d2r=tmp/10;

	if (digit==12345) {		
			d0r=51;
			d1r=51;
			d2r=51;		
	}

	switch (crazr){
		case 2: 				//старший разряд
		   if ((d2r==0)&&((work_mode!=SET_MIN)||(work_mode!=SET_MAX)))		//выключение нуля
		   	    SB(port_r_2,bit_r_2);
   			else
				CB(port_r_2,bit_r_2);				
	   		SB(port_r_1,bit_r_1);
	   		SB(port_r_0,bit_r_0);

//			if(work_mode!=WORK)
				CB(port_dp,bit_dp);
//			else
//				SB(port_dp,bit_dp);

			segm=d2r;
	   		segm_set();
	   		crazr=1;
 		break;

		case 1:				//средний разряд
	   		SB(port_r_2,bit_r_2);
	   		SB(port_r_0,bit_r_0);

//			if ( (d2r==0)&&(d1r==0)&&(display_mode!=TEMP))//выключение нуля
//				SB(port_r_1,bit_r_1);
//			else
	   			CB(port_r_1,bit_r_1);

			
			if (((work_mode==WORK)||(work_mode==ALARM))&&(display_mode==TEMP)){
	 			if (digit>=0)
					SB(port_dp,bit_dp);
				if (digit<0)
					minus();								
			}
			else	
				CB(port_dp,bit_dp);			

	   		segm=d1r;
	   		segm_set();
	   		crazr=0;
	 	break;	
		
		case 0:					// Младший разряд			
	   		SB(port_r_2,bit_r_2);
	   		SB(port_r_1,bit_r_1);
	   		CB(port_r_0,bit_r_0);
			CB(port_dp,bit_dp);

	   		segm=d0r;
	   		segm_set();
	   		crazr=2;
		break;
	}
}
void segm_set(){
switch (segm){
	case 0:
		SB(port_s_a,bit_s_a);
		SB(port_s_b,bit_s_b);
		SB(port_s_c,bit_s_c);
		SB(port_s_d,bit_s_d);
		SB(port_s_e,bit_s_e);
		SB(port_s_f,bit_s_f);
		CB(port_s_g,bit_s_g);
		break;
	case 1:
		CB(port_s_a,bit_s_a);
		SB(port_s_b,bit_s_b);
		SB(port_s_c,bit_s_c);
		CB(port_s_d,bit_s_d);
		CB(port_s_e,bit_s_e);
		CB(port_s_f,bit_s_f);
		CB(port_s_g,bit_s_g);
		break;
	case 2:
		SB(port_s_a,bit_s_a);
		SB(port_s_b,bit_s_b);
		CB(port_s_c,bit_s_c);
		SB(port_s_d,bit_s_d);
		SB(port_s_e,bit_s_e);
		CB(port_s_f,bit_s_f);
		SB(port_s_g,bit_s_g);
		break;
	case 3:
		SB(port_s_a,bit_s_a);
		SB(port_s_b,bit_s_b);
		SB(port_s_c,bit_s_c);
		SB(port_s_d,bit_s_d);
		CB(port_s_e,bit_s_e);
		CB(port_s_f,bit_s_f);
		SB(port_s_g,bit_s_g);
		break;
	case 4:
		CB(port_s_a,bit_s_a);
		SB(port_s_b,bit_s_b);
		SB(port_s_c,bit_s_c);
		CB(port_s_d,bit_s_d);
		CB(port_s_e,bit_s_e);
		SB(port_s_f,bit_s_f);
		SB(port_s_g,bit_s_g);
		break;
	case 5:
		SB(port_s_a,bit_s_a);
		CB(port_s_b,bit_s_b);
		SB(port_s_c,bit_s_c);
		SB(port_s_d,bit_s_d);
		CB(port_s_e,bit_s_e);
		SB(port_s_f,bit_s_f);
		SB(port_s_g,bit_s_g);
		break;
	case 6:
		SB(port_s_a,bit_s_a);
		CB(port_s_b,bit_s_b);
		SB(port_s_c,bit_s_c);
		SB(port_s_d,bit_s_d);
		SB(port_s_e,bit_s_e);
		SB(port_s_f,bit_s_f);
		SB(port_s_g,bit_s_g);
		break;
	case 7:
		SB(port_s_a,bit_s_a);
		SB(port_s_b,bit_s_b);
		SB(port_s_c,bit_s_c);
		CB(port_s_d,bit_s_d);
		CB(port_s_e,bit_s_e);
		CB(port_s_f,bit_s_f);
		CB(port_s_g,bit_s_g);
		break;
	case 8:
		SB(port_s_a,bit_s_a);
		SB(port_s_b,bit_s_b);
		SB(port_s_c,bit_s_c);
		SB(port_s_d,bit_s_d);
		SB(port_s_e,bit_s_e);
		SB(port_s_f,bit_s_f);
		SB(port_s_g,bit_s_g);
		break;
	case 9:
		SB(port_s_a,bit_s_a);
		SB(port_s_b,bit_s_b);
		SB(port_s_c,bit_s_c);
		SB(port_s_d,bit_s_d);
		CB(port_s_e,bit_s_e);
		SB(port_s_f,bit_s_f);
		SB(port_s_g,bit_s_g);
		break;
	case 10:
		CB(port_s_a,bit_s_a);
		CB(port_s_b,bit_s_b);
		CB(port_s_c,bit_s_c);
		CB(port_s_d,bit_s_d);
		CB(port_s_e,bit_s_e);
		CB(port_s_f,bit_s_f);
		SB(port_s_g,bit_s_g);
		break;

	case 51:
		CB(port_s_a,bit_s_a);
		CB(port_s_b,bit_s_b);
		CB(port_s_c,bit_s_c);
		CB(port_s_d,bit_s_d);
		CB(port_s_e,bit_s_e);
		CB(port_s_f,bit_s_f);
		SB(port_s_g,bit_s_g);
		break;
	case 100:
		CB(port_s_a,bit_s_a);
		CB(port_s_b,bit_s_b);
		CB(port_s_c,bit_s_c);
		CB(port_s_d,bit_s_d);
		CB(port_s_e,bit_s_e);
		CB(port_s_f,bit_s_f);
		CB(port_s_g,bit_s_g);
		break;
	case 101:
		CB(port_s_a,bit_s_a);
		SB(port_s_b,bit_s_b);
		SB(port_s_c,bit_s_c);
		CB(port_s_d,bit_s_d);
		SB(port_s_e,bit_s_e);
		SB(port_s_f,bit_s_f);
		SB(port_s_g,bit_s_g);
		break;
	case 102:
		SB(port_s_a,bit_s_a);
		SB(port_s_b,bit_s_b);
		CB(port_s_c,bit_s_c);
		CB(port_s_d,bit_s_d);
		CB(port_s_e,bit_s_e);
		SB(port_s_f,bit_s_f);
		SB(port_s_g,bit_s_g);
		break;
	case 103:
		SB(port_s_a,bit_s_a);
		CB(port_s_b,bit_s_b);
		CB(port_s_c,bit_s_c);
		SB(port_s_d,bit_s_d);
		SB(port_s_e,bit_s_e);
		SB(port_s_f,bit_s_f);
		CB(port_s_g,bit_s_g);
		break;

}
}
//-------------------------------
void InitPortsDI() {
SB(ddr_s_a,bit_s_a);
SB(ddr_s_b,bit_s_b);
SB(ddr_s_c,bit_s_c);
SB(ddr_s_d,bit_s_d);
SB(ddr_s_e,bit_s_e);
SB(ddr_s_f,bit_s_f);
SB(ddr_s_g,bit_s_g);
SB(ddr_dp,bit_dp);
SB(ddr_r_0,bit_r_0);
SB(ddr_r_1,bit_r_1);
SB(ddr_r_2,bit_r_2);
}

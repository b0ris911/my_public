#ifndef di_h
#define di_h

#include "_def.h"
#include "head_files.h"


#define ddr_s_a  DDRB	//+
#define port_s_a PORTB 
#define bit_s_a 3

#define ddr_s_b  DDRB	//+
#define port_s_b PORTB 
#define bit_s_b 4

#define ddr_s_c  DDRC	//+
#define port_s_c PORTC 
#define bit_s_c 0

#define ddr_s_d  DDRC	//+
#define port_s_d PORTC 
#define bit_s_d 2

#define ddr_s_e  DDRC 	//+
#define port_s_e PORTC 
#define bit_s_e 3

#define ddr_s_f  DDRB	//+
#define port_s_f PORTB 
#define bit_s_f 2

#define ddr_s_g  DDRB	//+
#define port_s_g PORTB 
#define bit_s_g 5

#define ddr_r_0  DDRD
#define port_r_0 PORTD
#define bit_r_0 6

#define ddr_r_1  DDRD
#define port_r_1 PORTD
#define bit_r_1 5

#define ddr_r_2  DDRC
#define port_r_2 PORTC
#define bit_r_2 4

#define ddr_dp  DDRC
#define port_dp PORTC
#define bit_dp 1

void InitPortsDI();
void segm_set();
void di(volatile s16 digit);
void minus();
//void Display7();


#endif

#ifndef setup_h
#define setup_h

#include "head_files.h"

//#define DDR_LCD_BL				DDRB
//#define PORT_LCD_BL				PORTB
//#define LCD_BL					5

#define DDR_POWER_LCD			DDRC
#define PORT_POWER_LCD			PORTC
#define POWER_LCD				0

//setup modes
#define MAIN					0
#define SETUP_OUT_PHONE_1		1
#define SETUP_OUT_PHONE_2		2
#define SETUP_IN_PHONE_1		3
#define SETUP_IN_PHONE_2		4
#define SETUP_IN_PHONE_3		5

#define DELAY_TOTAL_RESET		10000 //ms

u08 CAD(char data);
u08 SetupOutPhone1();
u08 SetupOutPhone2();

#define adr_out_phone_1		100
#define adr_out_phone_2		115
#define adr_in_phone_1		130
#define adr_in_phone_2		145
#define adr_in_phone_3		160
#define adr_flag_activity_out_phone_1	180
#define adr_flag_activity_out_phone_2	182
#define adr_flag_activity_in_phone_1	184
#define adr_flag_activity_in_phone_2	186
#define adr_flag_activity_in_phone_3	188
#endif

#ifndef kn2x_h
#define kn2x_h
//---------------
#include "head_files.h"
//defs
#define PORT_KN2 PORTD
#define PIN_KN2  PIND
#define DDR_KN2 DDRD
#define KN2 4

#define NOT_PRESSED		0
#define PRESSED			1

#define NUMBER_CHECKS_IN	5		//*5ms
#define NUMBER_CHECKS_OUT	5		//*5ms
#define DELAY_PRESS			5		//*5ms
#define DELAY_LONG_PRESS	60		//*5ms
#define DELAY_HOLD			200		//*5ms
//prots
void InitPortsKn2();
void ProcessKn2(volatile u08 *hold);

#endif

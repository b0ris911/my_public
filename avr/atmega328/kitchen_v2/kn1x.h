#ifndef kn1x_h
#define kn1x_h
//---------------
#include "head_files.h"
//defs
#define PORT_KN1 PORTD
#define PIN_KN1  PIND
#define DDR_KN1 DDRD
#define KN1 3

#define NOT_PRESSED		0
#define PRESSED			1

#define NUMBER_CHECKS_IN	5		//*5ms
#define NUMBER_CHECKS_OUT	5		//*5ms
#define DELAY_PRESS			5		//*5ms
#define DELAY_LONG_PRESS	60		//*5ms
#define DELAY_HOLD			200		//*5ms
//prots
void InitPortsKn1();
void ProcessKn1(volatile u08 *hold);

#endif

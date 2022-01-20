#ifndef KN2_h
#define KN2_h
//---------------
#include "_def.h"
#include "head_files.h"

//defs

#define PORT_KN2 PORTB
#define PIN_KN2  PINB
#define DDR_KN2 DDRB
#define KN2 0

//prots
void InitPortsKn2();
void ProcessKn2();
void DoFastK2();
void DoK2();			
void DoK2Long();			
void DoK2ReleaseAfterHold();


#endif

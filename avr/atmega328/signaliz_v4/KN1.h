#ifndef KN1_h
#define KN1_h
//---------------
#include "head_files.h"

//defs
#define PORT_KN1 PORTB
#define PIN_KN1  PINB
#define DDR_KN1 DDRB
#define KN1 1

//prots
void InitPortsKn1();
void ProcessKn1();
void DoFastK1();
void DoK1();			
void DoK1Long();			
void DoK1ReleaseAfterHold();


#endif

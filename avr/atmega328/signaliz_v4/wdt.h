#ifndef wdt
#define wdt

#include "head_files.h"

#define WDR asm("wdr");

void WDT_off();
void WDT_Prescaler_Change_8s();	
void WDT_Prescaler_Change_4s();	
void WDT_Prescaler_Change_2s();	
void WDT_Prescaler_Change_1s();	
void WDT_Prescaler_Change_500ms();
void WDT_Prescaler_Change_250ms();
void WDT_Prescaler_Change_125ms();
void WDT_Prescaler_Change_64ms();
void WDT_Prescaler_Change_32ms();
void WDT_Prescaler_Change_16ms();


#endif

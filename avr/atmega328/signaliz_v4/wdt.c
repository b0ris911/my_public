#include "wdt.h"

void WDT_off() {
	CLI
	WDR
	/* Clear WDRF in MCUSR */
	MCUSR &= ~(1<<WDRF);
	/* Write logical one to WDCE and WDE */
	/* Keep old prescaler setting to prevent unintentional time-out */
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	/* Turn off WDT */
	WDTCSR = 0x00;
	SEI
}
//------------------------
void WDT_Prescaler_Change_8s() {
	CLI
	WDR
	/* Start timed  equence */
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	/* Set new prescaler(time-out) value = 2 s /0111/*/
	WDTCSR  = (1<<WDE)|(1<<WDP3)|(0<<WDP2)|(0<<WDP1)|(1<<WDP0);
	SEI
}
void WDT_Prescaler_Change_4s() {	
	CLI
	WDR
	/* Start timed  equence */
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	/* Set new prescaler(time-out) value = 2 s /0111/*/
	WDTCSR  = (1<<WDE)|(1<<WDP3)|(0<<WDP2)|(0<<WDP1)|(0<<WDP0);
	SEI
}	
void WDT_Prescaler_Change_2s() {
	CLI
	WDR
	/* Start timed  equence */
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	/* Set new prescaler(time-out) value = 2 s /0111/*/
	WDTCSR  = (1<<WDE)|(0<<WDP3)|(1<<WDP2)|(1<<WDP1)|(1<<WDP0);
	SEI
}	
void WDT_Prescaler_Change_1s() {	
	CLI
	WDR
	/* Start timed  equence */
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	/* Set new prescaler(time-out) value = 2 s /0111/*/
	WDTCSR  = (1<<WDE)|(0<<WDP3)|(1<<WDP2)|(1<<WDP1)|(0<<WDP0);
	SEI
}	
void WDT_Prescaler_Change_500ms() {	
	CLI
	WDR
	/* Start timed  equence */
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	/* Set new prescaler(time-out) value = 2 s /0111/*/
	WDTCSR  = (1<<WDE)|(0<<WDP3)|(1<<WDP2)|(0<<WDP1)|(1<<WDP0);
	SEI
}	
void WDT_Prescaler_Change_250ms() {
	CLI
	WDR
	/* Start timed  equence */
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	/* Set new prescaler(time-out) value = 2 s /0111/*/
	WDTCSR  = (1<<WDE)|(0<<WDP3)|(1<<WDP2)|(0<<WDP1)|(0<<WDP0);
	SEI
}
void WDT_Prescaler_Change_125ms() {	
	CLI
	WDR
	/* Start timed  equence */
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	/* Set new prescaler(time-out) value = 2 s /0111/*/
	WDTCSR  = (1<<WDE)|(0<<WDP3)|(0<<WDP2)|(1<<WDP1)|(1<<WDP0);
	SEI
}	
void WDT_Prescaler_Change_64ms() {	
	CLI
	WDR
	/* Start timed  equence */
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	/* Set new prescaler(time-out) value = 2 s /0111/*/
	WDTCSR  = (1<<WDE)|(0<<WDP3)|(0<<WDP2)|(1<<WDP1)|(0<<WDP0);
	SEI
}
void WDT_Prescaler_Change_32ms() {			
	CLI
	WDR
	/* Start timed  equence */
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	/* Set new prescaler(time-out) value = 2 s /0111/*/
	WDTCSR  = (1<<WDE)|(0<<WDP3)|(0<<WDP2)|(0<<WDP1)|(1<<WDP0);
	SEI
}	
void WDT_Prescaler_Change_16ms() {
	CLI
	WDR
	/* Start timed  equence */
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	/* Set new prescaler(time-out) value = 2 s /0111/*/
	WDTCSR  = (1<<WDE)|(0<<WDP3)|(0<<WDP2)|(0<<WDP1)|(0<<WDP0);
	SEI
}


#include "ISR_timers.h"

ISR (TIMER0_OVF_vect) {
}
//-------------------------
ISR (TIMER0_COMPA_vect) {
	SysTick_Handler();
}
//-------------------------
ISR (TIMER2_OVF_vect) {	

}
//-------------------------
ISR (TIMER1_COMPA_vect) {
//	PORTB ^= 1<<1;
}

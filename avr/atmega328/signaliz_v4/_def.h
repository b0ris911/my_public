#ifndef _def_h
#define _def_h
//********************
#define F_CPU 4000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <bits_macros.h>
#include <string.h>

#define HIGH 1
#define LOW 0
#define YES 1
#define NO 0
#define ON 1
#define OFF 0
#define UP 1
#define DOWN 0

#define FREE		0
#define BUSY		1
#define END			2

#define u08 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define s08 int8_t
#define s16 int16_t
#define s32 int32_t


//*******
#define CLI asm("cli");
#define SEI asm("sei");
#define SLEEP asm("sleep");

inline void sleep_idle_enable() {
SMCR |= (1<<SE)|(0<<SM2)|(0<<SM1)|(0<<SM0);
}

inline void sleep_power_down_enable() {
	SMCR |= (1<<SE)|(0<<SM2)|(1<<SM1)|(0<<SM0);
}
/*
#define sb1	SB(PORTD,4);
#define cb1	CB(PORTD,4);
#define sb2	SB(PORTD,5);
#define cb2	CB(PORTD,5);
*/
#endif

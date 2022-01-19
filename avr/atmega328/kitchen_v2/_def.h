#ifndef _def_h
#define _def_h
//********************
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "bits_macros.h"

#define __ATmega328P__

#define HIGH 1
#define LOW 0
#define YES 1
#define NO 0
#define ON 1
#define OFF 0
#define UP 1
#define DOWN 0

//display mods
#define TEMP		0
#define HUM 		1


//work mods
#define WORK		0
#define SET_MIN		1
#define SET_MAX		2
#define ALARM		3
#define DIST		4

#define u08 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define s08 int8_t
#define s16 int16_t
#define s32 int32_t


//*******
#define CLI asm("cli");
#define SEI asm("sei");
#define WDR asm("wdr");
/*
#define sb1	SB(PORTD,4);
#define cb1	CB(PORTD,4);
#define sb2	SB(PORTD,5);
#define cb2	CB(PORTD,5);
*/
#endif

#ifndef lcd1602_h
#define lcd1602_h

#include "head_files.h"

//порт шины данных
#define DDR_DATA4 DDRC
#define PIN_DATA4  PINC
#define PORT_DATA4 PORTC
#define PDATA4 1

#define DDR_DATA5 DDRC
#define PIN_DATA5  PINC
#define PORT_DATA5 PORTC
#define PDATA5 2

#define DDR_DATA6 DDRC
#define PIN_DATA6  PINC
#define PORT_DATA6 PORTC
#define PDATA6 3

#define DDR_DATA7 DDRC
#define PIN_DATA7  PINC
#define PORT_DATA7 PORTC
#define PDATA7 4

//порт шины команд
#define PORT_RS PORTB
#define PIN_RS  PINB
#define DDR_RS DDRB
#define RS 3

#define PORT_RW PORTB
#define PIN_RW  PINB
#define DDR_RW DDRB
#define RW 4

#define PORT_EN PORTB
#define PIN_EN  PINB
#define DDR_EN DDRB
#define EN 5

void LcdBackLightAlarm();
void ReplaceDataPins();
void LCD (u08 num);
void LcdBackLightOn();
void LcdBackLightOff();
//ф-€ записи команд
void LcdWriteCom(unsigned char data);
//ф-€ записи данных
void LcdWriteData (unsigned char data);
//ф-€ вывода строки
void LcdString(const char *str);
//ф-€ инициализации
void InitLcd();

//очистка диспле€
void LcdClear();

//возврат курсора в начало
void LcdCursorBegin();

//установка курсора в позицию (100-115, 200-215)
void LcdGoto(u08 num_poz);

// выключение диспле€
void LcdOff();

//выключение курсора
void LcdCursorOff();

//Ћинейна€ форма курсора
void LcdCursorLine();

// ѕр€моугольна€ форма курсора
void LcdCursorCube();
//  омплексна€ форма курсора
void LcdCursorComplex();

//—двиг курсора влево
void LcdCursorLeft();
//—двиг курсора вправо
void LcdCursorRight();

#endif

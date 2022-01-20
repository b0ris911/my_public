#ifndef lcd1602_h
#define lcd1602_h

#include "head_files.h"

//���� ���� ������
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

//���� ���� ������
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
//�-� ������ ������
void LcdWriteCom(unsigned char data);
//�-� ������ ������
void LcdWriteData (unsigned char data);
//�-� ������ ������
void LcdString(const char *str);
//�-� �������������
void InitLcd();

//������� �������
void LcdClear();

//������� ������� � ������
void LcdCursorBegin();

//��������� ������� � ������� (100-115, 200-215)
void LcdGoto(u08 num_poz);

// ���������� �������
void LcdOff();

//���������� �������
void LcdCursorOff();

//�������� ����� �������
void LcdCursorLine();

// ������������� ����� �������
void LcdCursorCube();
// ����������� ����� �������
void LcdCursorComplex();

//����� ������� �����
void LcdCursorLeft();
//����� ������� ������
void LcdCursorRight();

#endif

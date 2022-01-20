#ifndef convert2lcd_h
#define convert2lcd_h

#include "head_files.h"

//defs

//��� �-��� �������������� ����� � �������
#define DIG_BASE  10 /* ��������� ������� ��������� ��� �������� */
#define MAX_SIZE 9 /* ������������ ����� ��������� �������� (��� �����)*/ 
#define SPACE_CHAR  ' ' /* ������ "�������" ����� */
#define NEG_CHAR '-' /* ������ "�����" */
#define MAX_TEXT 20

//prots
void Convert(uint32_t NUM,uint8_t X);
void TrimConvert(uint32_t NUM,uint8_t X);
void STrimConvert(int32_t NUM,uint8_t X);

#endif

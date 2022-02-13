#ifndef my_convert2lcd_h
#define my_convert2lcd_h

#include "my_head_files.h"

//defs

//для ф-ции преобразования числа в символы
#define DIG_BASE  10 /* основание системы счисления для перевода */
#define MAX_SIZE 10 /* максимальное число выводимых символов (без знака)*/
#define SPACE_CHAR  ' ' /* символ "пустого" места */
#define NEG_CHAR '-' /* символ "минус" */
#define MAX_TEXT 20

//prots
void Convert(uint32_t NUM,uint8_t X);
void TrimConvert(uint32_t NUM,uint8_t X);
void STrimConvert(int32_t NUM,uint8_t X);

#endif

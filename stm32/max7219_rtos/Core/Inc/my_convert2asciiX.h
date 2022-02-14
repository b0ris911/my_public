#ifndef my_convert2asciiX_h
#define convert2asciiX_h

#include "my_head_files.h"

//defs

//для ф-ции преобразования числа в символы
#define DIG_BASE  10 /* основание системы счисления для перевода */
#define MAX_SIZE 9 /* максимальное число выводимых символов (без знака)*/
#define SPACE_CHAR  ' ' /* символ "пустого" места */
#define NEG_CHAR '-' /* символ "минус" */
#define MAX_TEXT 20

//prots
void ConvertX(char* outx,u32 NUM,u08 X);
void TrimConvertX(char *outx,u32 NUM,u08 X);
void STrimConvertX(char *outx,s32 NUM,u08 X);

#endif

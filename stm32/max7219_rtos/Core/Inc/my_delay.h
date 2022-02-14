
#ifndef MY_DELAY_H_
#define MY_DELAY_H_

#include "my_head_files.h"

void DWT_DelayUpdate(void);

void DWT_Init(void);

uint32_t DWT_GetTick(void);

void _delay_sec(uint32_t sec); // В секундах.

void _delay_ms(uint32_t ms); // В миллисекундах

void _delay_us(uint32_t us); // В микросекундах.

#endif /* MY_DELAY_H_ */

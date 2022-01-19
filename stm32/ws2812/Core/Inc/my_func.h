#ifndef MY_FUNC_H
#define MY_FUNC_H

#include "my_head_files.h"

//#define SB(PORT,PIN) HAL_GPIO_WritePin(PORT, PIN, GPIO_PIN_SET)
#define SB(PORT,PIN) (PORT->BSRR |= PIN);
//#define CB(PORT,PIN) HAL_GPIO_WritePin(PORT, PIN, GPIO_PIN_RESET)
#define CB(PORT,PIN) (PORT->BSRR |= ((u32)PIN<<16u));
#define BIC(PIN_PORT,PIN) ReadPin(PIN_PORT, PIN)==0
#define BIS(PIN_PORT,PIN) ReadPin(PIN_PORT, PIN)==1

// Запретить прерывания IRQ
#define CLI __disable_irq ();
 // Разрешить прерывания IRQ
#define SEI __enable_irq ();

//#define abs(x) ((x) > 0 ? (x) : -(x));
//----------Functions-------------

//#define IB(PORT,PIN) HAL_GPIO_TogglePin(PORT, PIN)
void TB(GPIO_TypeDef *GPIOx, u16 GPIO_Pin);
u08 ReadPin(GPIO_TypeDef *GPIOx, u16 GPIO_Pin);
uint16_t sqrt_new ( uint32_t L );

u08 InverseByte(u08 byte);


#endif

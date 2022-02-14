#include "my_delay.h"

extern uint32_t SystemCoreClock;
static uint32_t Delay_us, Delay_ms;

void DWT_DelayUpdate(void)
{
    Delay_ms = SystemCoreClock / 1000;    // Число тактов ядра за миллисекунду.
    Delay_us = SystemCoreClock / 1000000; // Число тактов ядра за микросекунду.
}

void DWT_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    DWT_DelayUpdate();
}

uint32_t DWT_GetTick(void)
{
   return DWT->CYCCNT;
}

void _delay_sec(uint32_t sec) // В секундах.
{
    uint32_t Count = DWT->CYCCNT;
    sec = sec * SystemCoreClock;
    while((DWT->CYCCNT - Count) < sec);
}

void _delay_ms(uint32_t ms) // В миллисекундах
{
    uint32_t Count = DWT->CYCCNT;
    ms = ms * Delay_ms;
    while((DWT->CYCCNT - Count) < ms);
}

void _delay_us(uint32_t us) // В микросекундах.
{
    uint32_t Count = DWT->CYCCNT;
    us = us * Delay_us;
    while((DWT->CYCCNT - Count) < us);
}


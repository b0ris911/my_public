#include "my_maintimer.h"

#define TIMER_STOPPED	0					//Таймер остановлен
#define TIMER_RUNNING	1					//Таймер работает



u32 GTStates[MAX_GTIMERS];		//В массиве хранятся текущие состояния глобальных таймеров
u32 GTDelay[MAX_GTIMERS];		//Массив задержек для каждого таймера

volatile static u32 TimeMs = 0;
volatile u08 flag_1ms=0;
//-----------------------------------------
void StartGTimer(u32 GTimerID,u32 delay) { 		// Функция запуска таймера на заданную задержку
  	if(GTStates[GTimerID]==TIMER_STOPPED)  	{
		GTStates[GTimerID]=TIMER_RUNNING;
		CLI
		GTDelay[GTimerID]=TimeMs+delay;
		SEI
  	}
}
//-----------------------------------------
void StopGTimer(u32 GTimerID)	{			//Остановка таймера
  	if(GTStates[GTimerID]==TIMER_RUNNING)
		GTStates[GTimerID]=TIMER_STOPPED;
}
//-----------------------------------------
u32 ExpGTimer(u32 GTimerID) {				//Проверка таймера
	if(GTStates[GTimerID]==TIMER_RUNNING) {
		CLI
		if ((TimeMs - GTDelay[GTimerID]) < (1UL << 31)) {
			if (GTDelay[GTimerID] <= TimeMs) {				
				GTStates[GTimerID]=TIMER_STOPPED;
				SEI
				return 1;
			}			
		}
	}	
	SEI	
	return 0;		
}
//-----------------------------------------
void InitGTimers() {
	TimeMs = 0;
}

//-----------------------------------------
void MySysTick_Handler() {
	TimeMs++;
	flag_1ms=1;
}
/*
//-----------------------------------------
static __inline uint32_t delta(uint32_t t0, uint32_t t1) {
    return (t1 - t0);
}
void _delay_us(u32 us){
    uint32_t t0 =  DWT->CYCCNT;
    uint32_t us_count_tic =  us * (SystemCoreClock/1000000);
    while (delta(t0, DWT->CYCCNT) < us_count_tic) ;
}
*/


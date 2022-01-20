#ifndef maintimer32_h
#define maintimer32_h

#include "head_files.h"

#define MAX_GTIMERS			20

#define timer_led							0
#define timer_kn							1
#define timer_send_at						2
#define timer_OK							3
#define timer_delay_ccalr					4
#define timer_power_down					5
#define timer_setup							6
#define timer_total_reset					7
#define timer_delay_repeat_alarm_calling	8
#define timer_delay_500ms					9
#define timer_delay_release_guard			10
#define timer_delay							11
#define timer_delay_reset_release_guard		12
#define timer_inc_counter_system_reset		13
#define timer_sirena						14
#define timer_sirena_off					15

void InitGTimers();
void SysTick_Handler();
void StartGTimer(u08 GTimerID,u32 delay); 	
void StopGTimer(u08 GTimerID);
u08 ExpGTimer(u08 GTimerID);

#endif 

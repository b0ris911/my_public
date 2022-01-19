#ifndef maintimer16_h
#define maintimer16_h

#include "head_files.h"

#define MAX_GTIMERS		15

#define timer_kn						0
#define timer_di						1
#define timer_delay_ds18b20				2	
#define timer_si7021					3
#define timer_reset_i2c					4
#define timer_process_sheduler_i2c		5
#define timer_delay_start_hcsr			6
#define timer_hot_water					7
#define timer_flash_red					8
#define timer_led						9
#define timer_trig						10
#define timer_buzzer					11

void StartGTimer(u08 GTimerID,u16 delay); 	
void StopGTimer(u08 GTimerID);
u08 ExpGTimer(u08 GTimerID);
void InitGTimers();
void SysTick_Handler();

#endif 

#ifndef maintimer16_h
#define maintimer16_h

#include "head_files.h"

#define MAX_GTIMERS		15

#define timer_led					0
#define timer_kn					1
#define timer_send_at				2
#define timer_OK					3
#define timer_delay_ccalr			4
#define timer_power_down			5
#define timer_setup					6
#define timer_total_reset			7
#define timer_delay_repeat_alarm_calling	8
#define timer_delay_500ms			9
#define timer_delay_release_guard	10
//#define timer_adc					4
//#define timer_light_autooff			5

//#define timer_process_sheduler_i2c	6
//#define timer_delay_si7021			7	
//#define timer_reset_i2c				8
//#define timer_start_i2c				9
//#define timer_tsl					10
//#define timer_delay_start_tsl		11

void StartGTimer(u08 GTimerID,u16 delay); 	
void StopGTimer(u08 GTimerID);
u08 ExpGTimer(u08 GTimerID);
void InitGTimers();
void SysTick_Handler();

#endif 

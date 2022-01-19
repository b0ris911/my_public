#ifndef my_maintimer_h
#define my_maintimer_h

#include "my_head_files.h"

#define MAX_GTIMERS					50

#define timer_led					0
#define timer_kn					1
#define timer_motor					2
#define timer_led_green				3
#define timer_counter				4
#define timer_reset_i2c				5
#define timer_delay_si7021			6
#define timer_func_timer_motor		7
#define timer_smooth_start			8
#define timer_smooth_stop			9
#define timer_trig					10
#define timer_delay_bme680			11
#define timer_process_sheduler_i2c	12
#define timer_uart					13
#define timer_smooth_moving			14
#define timer_show_res_adc			15
#define timer_start_adc				16
#define timer_start_dma_tim1_ch3	17
#define timer_rotate_colors			18
#define timer_process_ws2812		19
#define timer_change_arrays			20
#define timer_change_flag			21
#define timer_change_brightness		22
#define timer_smooth_change_color	23
#define timer_start_i2c				24
#define timer_pause_temp			25
#define timer_change_func_color		26
//#define timer_do_something

void InitGTimers();
void MySysTick_Handler();
void StartGTimer(u32 GTimerID,u32 delay);
void StopGTimer(u32 GTimerID);
u32 ExpGTimer(u32 GTimerID);
void _delay_us(u32 us);


#endif 

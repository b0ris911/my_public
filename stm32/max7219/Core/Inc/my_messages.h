//messages.h
#ifndef my_MESSAGES_h
#define my_MESSAGES_h

#include "my_def.h"
#include "my_head_files.h"

#define MSG_KN1_FAST_PRESSED	0
#define MSG_KN1_PRESSED			1 
#define MSG_KN1_LONGPRESSED		2
#define MSG_KN1_RELEASED		3

#define MSG_KN2_FAST_PRESSED	4
#define MSG_KN2_PRESSED			5 
#define MSG_KN2_LONGPRESSED		6
#define MSG_KN2_RELEASED		7

#define MSG_KN3_FAST_PRESSED	8
#define MSG_KN3_PRESSED			9 
#define MSG_KN3_LONGPRESSED		10
#define MSG_KN3_RELEASED		11

#define MSG_ADCEx_InjectedConvCpltCallback	12
#define MSG_ADC_ConvCpltCallback		13
#define MSG_FLAG_SHOW_DATA_HCSR			14

//def
#define MAX_MESSAGES 30
#define MAX_BROADCAST_MESSAGES 0
//prots
void ProcessMessages();
void InitMessages();
void SendMessage(uint8_t Msg);
uint8_t GetMessage(uint8_t Msg);
void SendBroadcastMessage(uint8_t Msg);
uint8_t GetBroadcastMessage(uint8_t msg);

#endif

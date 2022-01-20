//messages.h
#ifndef MESSAGES_h
#define MESSAGES_h

#include "head_files.h"

#define MSG_KN1_FAST_PRESSED	0
#define MSG_KN1_PRESSED			1 //delta-
#define MSG_KN1_LONGPRESSED		2
#define MSG_KN1_RELEASED		3

#define MSG_KN2_FAST_PRESSED	4
#define MSG_KN2_PRESSED			5 //delta+
#define MSG_KN2_LONGPRESSED		6
#define MSG_KN2_RELEASED		7

#define MSG_SIM800L_OK			8
#define MSG_SIM800L_RING		9
#define MSG_SIM800L_CCALR1		10
#define MSG_SIM800L_CCALR0		11
#define MSG_SIM800L_CSQ			12
#define MSG_SIM800L_BUSY		13	//если вызов отклонен
#define MSG_SIM800L_NO_CARRIER	14	//повесили трубку
#define MSG_SIM800L_NO_DIALTONE	15	//нет сигнала
#define MSG_SIM800L_NO_ANSWER	16	//нет ответа
#define MSG_SIM800L_INCOMING_PHONE_1	17
#define MSG_SIM800L_INCOMING_PHONE_2	18
#define MSG_SIM800L_INCOMING_PHONE_3	19
#define MSG_SIM800L_INCOMING_UNKNOWN	20
#define MSG_SIM800L_DTMF				21
/*
#define MSG_KN3_FAST_PRESSED	8
#define MSG_KN3_PRESSED			9 //freq-
#define MSG_KN3_LONGPRESSED		10
#define MSG_KN3_RELEASED		11

#define MSG_KN4_FAST_PRESSED	12
#define MSG_KN4_PRESSED			13 //freq+
#define MSG_KN4_LONGPRESSED		14
#define MSG_KN4_RELEASED		15

#define MSG_KN5_FAST_PRESSED	16
#define MSG_KN5_PRESSED			17 //impulse
#define MSG_KN5_LONGPRESSED		18
#define MSG_KN5_RELEASED		19

#define MSG_KN6_FAST_PRESSED	20
#define MSG_KN6_PRESSED			21 //light
#define MSG_KN6_LONGPRESSED		22
#define MSG_KN6_RELEASED		23
*/


//def
#define MAX_MESSAGES 25
#define MAX_BROADCAST_MESSAGES 0
//prots
void ProcessMessages();
void InitMessages();
void SendMessage(uint8_t Msg);
uint8_t GetMessage(uint8_t Msg);
void SendBroadcastMessage(uint8_t Msg);
uint8_t GetBroadcastMessage(uint8_t msg);

#endif

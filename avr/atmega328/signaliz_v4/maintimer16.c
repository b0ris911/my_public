#include "maintimer16.h"

#define TIMER_STOPPED	0					//������ ����������
#define TIMER_RUNNING	1					//������ ��������

u08 GTStates[MAX_GTIMERS];		//� ������� �������� ������� ��������� ���������� ��������
u16 GTDelay[MAX_GTIMERS];		//������ �������� ��� ������� �������

volatile static u16 TimeMs = 0;
volatile u08 f1ms=0;

//-----------------------------------------
void StartGTimer(u08 GTimerID,u16 delay) { 		// ������� ������� ������� �� �������� ��������
  	if(GTStates[GTimerID]==TIMER_STOPPED)  	{
		GTStates[GTimerID]=TIMER_RUNNING;
		CLI
		GTDelay[GTimerID]=TimeMs+delay;
		SEI
  	}
}
//-----------------------------------------
void StopGTimer(u08 GTimerID)	{			//��������� �������
  	if(GTStates[GTimerID]==TIMER_RUNNING)
		GTStates[GTimerID]=TIMER_STOPPED;
}
//-----------------------------------------
u08 ExpGTimer(u08 GTimerID) {				//�������� �������
	if(GTStates[GTimerID]==TIMER_RUNNING) {
		CLI
		if ((TimeMs - GTDelay[GTimerID]) < (1UL << 15)) {
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
 	for(u08 i=0; i<MAX_GTIMERS; i++)
 		GTStates[i]=TIMER_STOPPED;
 	for(u08 i=0; i<MAX_GTIMERS; i++)
 		GTDelay[i]=0;
}
//-----------------------------------------
void SysTick_Handler() {
	TimeMs++;
	f1ms=1;
}


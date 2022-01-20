#include "maintimer32.h"

#define TIMER_STOPPED	0					//������ ����������
#define TIMER_RUNNING	1					//������ ��������

u08 GTStates[MAX_GTIMERS];		//� ������� �������� ������� ��������� ���������� ��������
u32 GTDelay[MAX_GTIMERS];		//������ �������� ��� ������� �������

volatile static u32 TimeMs = 0;

//-----------------------------------------
void StartGTimer(u08 GTimerID,u32 delay) { 		// ������� ������� ������� �� �������� ��������
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
void SysTick_Handler() {
	TimeMs++;
}

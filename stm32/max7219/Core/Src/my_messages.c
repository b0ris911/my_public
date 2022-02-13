#include "my_messages.h"

//vars
uint8_t Messages[MAX_MESSAGES];
uint8_t Broadcast_Messages[MAX_BROADCAST_MESSAGES];

//prototypes
void InitMessages() {
	uint8_t i;
	for (i=0;i<MAX_MESSAGES;i++)
		Messages[i]=0;
	for (i=0;i<MAX_BROADCAST_MESSAGES;i++)
		Broadcast_Messages[i]=0;
}
void SendMessage(uint8_t msg) {
	if (Messages[msg]==0)
		Messages[msg]=1;
}
/*
void SendBroadcastMessage(uint8_t msg) {
	if (Broadcast_Messages[msg]==0)
	Broadcast_Messages[msg]=1;
}
*/
void ProcessMessages() {
	uint8_t i;
	for (i=0;i<MAX_MESSAGES;i++) {
		if (Messages[i]==2) Messages[i]=0;
		if (Messages[i]==1) Messages[i]=2;	
	}
	for (i=0;i<MAX_BROADCAST_MESSAGES;i++) {
		if (Broadcast_Messages[i]==2) Broadcast_Messages[i]=0;
		if (Broadcast_Messages[i]==1) Broadcast_Messages[i]=2;	
	}

}

uint8_t GetMessage(uint8_t msg) {
	if (Messages[msg]==2) {
		Messages[msg]=0;
		return 1;
	}
	return 0;
}

/*
uint8_t GetBroadcastMessage(uint8_t msg) {
	if (Broadcast_Messages[msg]==2) {
		Broadcast_Messages[msg]=0;
		return 1;
	}
	return 0;
}
*/

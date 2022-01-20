#include "uart328_sh.h"

extern char out[]; //находится в convert2ascii.c
extern char in_phone_1[];
extern char in_phone_2[];
extern char in_phone_3[];
//--------------------------------------------
volatile u08 status_uart=FREE;
volatile s08 queue=0;
char array_of_strings[NUMBER_OF_STRINGS][STRING_LENGTH+1]; //массив указателей на строки
char array_out[STRING_LENGTH]={};	//выходная строка
volatile u08 newline_of_string[NUMBER_OF_STRINGS]={0};//массив признака новой строки для каждой строки
char in_buf[STRING_LENGTH]={};
char data_dtmf=0;
//--------------------------------------------
char signal_power[3]={0};
//--------------------------------------------
void SendDigitUart(u32 data,u08 digits,u08 new_line){
	Convert(data,digits);
//	for(u08 i=0;i<STRING_LENGTH;i++)	
//		array_of_strings[queue][i]=0;
	strcpy(array_of_strings[queue],out);
	array_of_strings[queue][digits]=0;//пишем окончание строки после цифр
	newline_of_string[queue]=new_line;
	queue++;;
	if (queue==NUMBER_OF_STRINGS+1)
		queue--;		
}
//--------------------------------------------
void SendTextUart(char *text_in,u08 new_line) {
//	for(u08 i=0;i<STRING_LENGTH;i++)
//		array_of_strings[queue][i]=0;
	strcpy(array_of_strings[queue],text_in);
	newline_of_string[queue]=new_line;
	queue++;
	if(queue==NUMBER_OF_STRINGS+1)
		queue--;
}
//------------------------------------------
void ProcessShedulerUart() {
	switch (status_uart) {
		case BUSY:
			return;
		break;	
		
		case END:
			//.....
			status_uart=FREE;
		break;

		case FREE:
			//.....
		break;				
}//sw
}//v
//----------------------------------------------
ISR(USART_UDRE_vect)
{

void TxUart() {

volatile static u08 i=0,step=0;	
	switch (step) {
	case 0:			
		UDR0=array_out[i];			
		i++;			
		if (array_out[i]=='\0') {
			i=0;
			if(newline_of_string[0]==1)
				step=1;				
			else 
				step=3;									
		}										
	break;
	case 1:	
			UDR0='\r';	
			step=2;
//			StopTxUart();
//			status_uart=END;		
	break;			
	case 2:	//Enter, конец передачи
			UDR0='\n';	
			step=0;
			StopTxUart();
			status_uart=END;		
	break;			
	case 3:	
			step=0;
			StopTxUart();
			status_uart=END;		
	break;			

	}//sw
}//void
	TxUart();
}//ISR
//---------------------------------------
ISR(USART_RX_vect) {
volatile static u08 i=0,step=0;//1
	switch(step) {
		case 0:
			if(UDR0=='\n') {//пропускаем повтор команды в ответе от модуля
				step=1;//del
				i=0;
			}		
		break;
		case 1:
			in_buf[i]=UDR0;//складываем в буфер
			i++;
			if(in_buf[i-1]=='\n') {	//ждем символа новой строки		
				step=0;//del
				i=0;
				StopGTimer(timer_inc_counter_system_reset);
				if( (in_buf[0]=='O')&&
					(in_buf[1]=='K')) {
						SendMessage(MSG_SIM800L_OK);						
						return;
				}//if
				if( (in_buf[0]=='R')&&
					(in_buf[1]=='I')&&
					(in_buf[2]=='N')&&
					(in_buf[3]=='G')) {
						SendMessage(MSG_SIM800L_RING);
					return;
				}//if		
//-*-*-
				if( (in_buf[0]=='+')&&
					(in_buf[1]=='D')&&
					(in_buf[2]=='T')&&
					(in_buf[3]=='M')&&
					(in_buf[4]=='F')&&
					(in_buf[5]==':')&&
					(in_buf[6]==' ')) {
					SendMessage(MSG_SIM800L_DTMF);
					data_dtmf=in_buf[7];
					return;
				}//if		

				if( (in_buf[0]=='N')&&
					(in_buf[1]=='O')&&
					(in_buf[2]==' ')&&
					(in_buf[3]=='C')&&
					(in_buf[4]=='A')&&
					(in_buf[5]=='R')&&
					(in_buf[6]=='R')&&
					(in_buf[7]=='I')&&
					(in_buf[8]=='E')&&
					(in_buf[9]=='R')) {
						SendMessage(MSG_SIM800L_NO_CARRIER);						
					return;
				}//if		
				if( (in_buf[0]=='B')&&
					(in_buf[1]=='U')&&
					(in_buf[2]=='S')&&
					(in_buf[3]=='Y')) {
						SendMessage(MSG_SIM800L_BUSY);						
					return;
				}//if
				if( (in_buf[0]=='+')&&
					(in_buf[1]=='C')&&
					(in_buf[2]=='C')&&
					(in_buf[3]=='A')&&
					(in_buf[4]=='L')&&
					(in_buf[5]=='R')&&
					(in_buf[6]==':')&&
					(in_buf[7]==' ')&&					
					(in_buf[8]=='1')) {
						SendMessage(MSG_SIM800L_CCALR1);						
					return;
				}//if
				if( (in_buf[0]=='+')&&
					(in_buf[1]=='C')&&
					(in_buf[2]=='C')&&
					(in_buf[3]=='A')&&
					(in_buf[4]=='L')&&
					(in_buf[5]=='R')&&
					(in_buf[6]==':')&&
					(in_buf[7]==' ')&&					
					(in_buf[8]=='0')) {
						SendMessage(MSG_SIM800L_CCALR0);						
					return;
				}//if
				if( (in_buf[0]=='N')&&
					(in_buf[1]=='O')&&
					(in_buf[2]==' ')&&
					(in_buf[3]=='D')&&
					(in_buf[4]=='I')&&
					(in_buf[5]=='A')&&
					(in_buf[6]=='L')&&
					(in_buf[7]=='T')&&
					(in_buf[8]=='O')&&
					(in_buf[9]=='N')&&
					(in_buf[10]=='E')) {
						SendMessage(MSG_SIM800L_NO_DIALTONE);							
					return;
				}//if		
				if( (in_buf[0]=='N')&&
					(in_buf[1]=='O')&&
					(in_buf[2]==' ')&&
					(in_buf[3]=='A')&&
					(in_buf[4]=='N')&&
					(in_buf[5]=='S')&&
					(in_buf[6]=='W')&&
					(in_buf[7]=='E')&&					
					(in_buf[8]=='R')) {
						SendMessage(MSG_SIM800L_NO_ANSWER);											
					return;
				}//if		

//+CSQ: 12,0
				if( (in_buf[0]=='+')&&
					(in_buf[1]=='C')&&
					(in_buf[2]=='S')&&
					(in_buf[3]=='Q')&&
					(in_buf[4]==':')&&					
					(in_buf[5]==' ')) {
						SendMessage(MSG_SIM800L_CSQ);
						signal_power[0]=in_buf[6];
						signal_power[1]=in_buf[7];					
					return;
				}//if
//+CLIP
				if( (in_buf[0]=='+')&&
					(in_buf[1]=='C')&&
					(in_buf[2]=='L')&&
					(in_buf[3]=='I')&&
					(in_buf[4]=='P')&&
					(in_buf[5]==':')&&
					(in_buf[6]==' ')&&
					(in_buf[7]=='"')&&
					(in_buf[8]=='+')&&					
					(in_buf[9]=='3')&&
					(in_buf[10]=='8')&& 
					(in_buf[11]==in_phone_1[0]+48)&&
					(in_buf[12]==in_phone_1[1]+48)&&
					(in_buf[13]==in_phone_1[2]+48)&&
					(in_buf[14]==in_phone_1[3]+48)&&
					(in_buf[15]==in_phone_1[4]+48)&&
					(in_buf[16]==in_phone_1[5]+48)&&
					(in_buf[17]==in_phone_1[6]+48)&&
					(in_buf[18]==in_phone_1[7]+48)&&
					(in_buf[19]==in_phone_1[8]+48)&&
					(in_buf[20]==in_phone_1[9]+48)) {						
							SendMessage(MSG_SIM800L_INCOMING_PHONE_1);							
							return;
				}//if		
				if( (in_buf[0]=='+')&&
					(in_buf[1]=='C')&&
					(in_buf[2]=='L')&&
					(in_buf[3]=='I')&&
					(in_buf[4]=='P')&&
					(in_buf[5]==':')&&
					(in_buf[6]==' ')&&
					(in_buf[7]=='"')&&
					(in_buf[8]=='+')&&					
					(in_buf[9]=='3')&&
					(in_buf[10]=='8')&& 
					(in_buf[11]==in_phone_2[0]+48)&&
					(in_buf[12]==in_phone_2[1]+48)&&
					(in_buf[13]==in_phone_2[2]+48)&&
					(in_buf[14]==in_phone_2[3]+48)&&
					(in_buf[15]==in_phone_2[4]+48)&&
					(in_buf[16]==in_phone_2[5]+48)&&
					(in_buf[17]==in_phone_2[6]+48)&&
					(in_buf[18]==in_phone_2[7]+48)&&
					(in_buf[19]==in_phone_2[8]+48)&&
					(in_buf[20]==in_phone_2[9]+48)) {						
							SendMessage(MSG_SIM800L_INCOMING_PHONE_2);
							return;
				}//if		
				if( (in_buf[0]=='+')&&
					(in_buf[1]=='C')&&
					(in_buf[2]=='L')&&
					(in_buf[3]=='I')&&
					(in_buf[4]=='P')&&
					(in_buf[5]==':')) {												
						SendMessage(MSG_SIM800L_INCOMING_UNKNOWN);
					return;
				}//if		

			}//if
		break;		
	}//sw					
}//v


//ISR(USART_RX_vect)
//{}
/*
	switch (UDR) {
		case '1':
			state_joy=UP;
			SendMessage(MSG_JOY_PRESSED);
		break;
		case '2':
			state_joy=DOWN;
			SendMessage(MSG_JOY_PRESSED);
		break;
		case '3':
			state_joy=LEFT;
			SendMessage(MSG_JOY_PRESSED);
		break;
		case '4':
			state_joy=RIGHT;
			SendMessage(MSG_JOY_PRESSED);
		break;
		case '5':
			state_joy=CENTER;
			SendMessage(MSG_JOY_PRESSED);
		break;
		case '7':
			state_joy=FREE;
			SendMessage(MSG_JOY_PRESSED);
		break;
		case '8':
			state_key=WHITE;
			SendMessage(MSG_KEY_PRESSED);
		break;
		case '9':
			if (mig==OFF){
				mig=ON;
				StopGTimer(timer_mig);
			}		
			else {
				mig=OFF;		
				StopGTimer(timer_mig);
			}
		break;
	}
}*/
/*
static unsigned char j=0,i=0,k=0;

	tmp=UDR;
	if ((tmp==13)||(tmp==27)) //если нажата Enter или Escape
		i=0;   				//счетчик в 0
	else 
	{
		input[i]=tmp;
		i++;
		if (i>2)
		 i=0;
	}
	if (tmp==27) 
	{					//если нажата Escape
		for (k=0;k<2;k++) 
			input[k]='0';			//обнуляем массив
	}
	if (tmp==13) 
	{					//если нажата Enter
		for (j=0;j<3;j++)
			num[j]=input[j];		//массив на выход
	}		
	switch (tmp)
	{
		case 27: //LCD_Write_Com(0x01);		//перерисовываем дисплей
		break;
		case 'r': //Init_LCD();			//переинициализация дисплея
		break;
		default: break;
	}
}*/

//-----------------------------------
/*
extern volatile uint8_t out[MAX_SIZE];
UDR=out[i];
	i++;
	if (i==4) {
		i=0;
		StopTxUart();	
	}
}
extern volatile uint8_t out[MAX_SIZE];	
volatile static uint8_t i=0;
	UDR=out[i];
	i++;
	if (i==3) {
		i=0;
		StopTxUart();	
	}
}
*/
/*extern volatile unsigned char text_out[];	
volatile static uint8_t i=0;
if (text_out[0]!=0){
	UDR=text_out[i];
	i++;
	if (text_out[i]==0) {
		i=0;
		StopTxUart();
}
}
*/

/*
static unsigned char i=0;
	UDR=ar[i];
	i++;
	if (ar[i]==0)
		i=0;
//	if (i==14)
//		i=48;
StopTxUart();
*/
/*
static unsigned char i=0;
		if ((text_out[i]>=32)&&(text_out[i]<=126)) 
					UDR=text_out[i];
					i++;							
					if (i==size_text_out) { 												
						i=0;
						UDR=13;
						StopTxUart();
					}							
*/
/*static unsigned char i=0,state=0;
	switch (state) {
	 case 0:
		
		switch (button) {
			case 1:
				if ((text0[i]>=32)&&(text0[i]<=126)) 
					UDR=text0[i];
					i++;							
					if (i==MAX_TEXT) {												
						i=0;					
						state=1;	
					}		
			break;
			case 2:
				if ((text1[i]>=32)&&(text1[i]<=126)) 
					UDR=text1[i];
					i++;							
					if (i==MAX_TEXT) {						
						i=0;
						state=1;
					}		
			break;



			}//sw
	 break;			
	case 1:
		UDR=13;
		state=0;
		Stop_TX_UART();				
	break;
		}//switch	
				
}//ISR
*/

void InitUart() {
UBRR0L = LO(bauddivider);
UBRR0H = HI(bauddivider);
UCSR0A = 0;
UCSR0B = (1<<RXCIE0)|(0<<TXCIE0)|(0<<UDRIE0)|(1<<RXEN0)|(0<<TXEN0)|(0<<UCSZ02);/*
UCSR0C = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
*/
}
void StartTxUart() {
	UCSR0B = (0<<RXEN0)|(1<<TXEN0)|(0<<RXCIE0)|(0<<TXCIE0)|(1<<UDRIE0)|(0<<UCSZ02);
}
void StopTxUart() {
	UCSR0B = (1<<RXEN0)|(0<<TXEN0)|(1<<RXCIE0)|(0<<TXCIE0)|(0<<UDRIE0)|(0<<UCSZ02);

}




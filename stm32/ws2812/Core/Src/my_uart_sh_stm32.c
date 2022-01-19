#include "my_uart_sh_stm32.h"
#include "usart.h"

extern char out[]; //находится в convert2ascii.c

volatile u08 uart_data_rx=0;
//volatile u08 allow_show_data_on_lcd=OFF;
//--------------------------------------------
//--------------------------------------------
/*
void ShowDataUartLcd() {
	if (allow_show_data_on_lcd==ON) {
		allow_show_data_on_lcd=OFF;
//		LcdGoto(200);
	//	LcdWriteData(uart_data_rx);
	}
}
*/
//--------------------------------------------
volatile u08 status_uart=FREE_UART;
volatile s08 queue=0;
char array_of_strings[NUMBER_OF_STRINGS][STRING_LENGTH+1]; //массив указателей на строки
char array_out[STRING_LENGTH]={};	//выходная строка
volatile u08 newline_of_string[NUMBER_OF_STRINGS]={0};//массив признака новой строки для каждой строки
char in_buf[STRING_LENGTH]={};
//--------------------------------------------
//--------------------------------------------
//--------------------------------------------
void SendDigitUart(u32 data,u08 digits,u08 new_line){
	CLI
	Convert(data,digits);
	strcpy(array_of_strings[queue],out);
	array_of_strings[queue][digits]=0;//пишем окончание строки после цифр
	newline_of_string[queue]=new_line;
	queue++;;
	if (queue==NUMBER_OF_STRINGS+1)
		queue--;
	SEI
}
//--------------------------------------------
void SendTrimDigitUart(u32 data,u08 digits,u08 new_line){
	CLI
	TrimConvert(data,digits);
	strcpy(array_of_strings[queue],out);
	array_of_strings[queue][digits]=0;//пишем окончание строки после цифр
	newline_of_string[queue]=new_line;
	queue++;;
	if (queue==NUMBER_OF_STRINGS+1)
		queue--;
	SEI
}
//--------------------------------------------
//--------------------------------------------
void SendTextUart(char *text_in,u08 new_line) {
	CLI
	strcpy(array_of_strings[queue],text_in);
	newline_of_string[queue]=new_line;
	queue++;
	if(queue==NUMBER_OF_STRINGS+1)
		queue--;
	SEI
}
//------------------------------------------
void ProcessShedulerUart(UART_HandleTypeDef *huart) {
//void ProcessShedulerUart() {
	switch (status_uart) {
		case BUSY_UART:
			return;
		break;

		case END_UART:
			//............
			status_uart=FREE_UART;
		break;

		case FREE_UART:
			if (queue==0)
				return;
			else {
				//............
				HAL_UART_Transmit_IT(huart,array_out,strlen(array_out));
			}
		break;
}//sw
}//v
//----------------------------------------------
void HAL_UART_TxCpltCallback (UART_HandleTypeDef * huart) {
	status_uart=END_UART;
}
//----------------------------------------------------------------
/*
void FuncUart1() {
//	uint8_t d = USART1->DR; // получить данное
	//USART1->DR = d; // отослать данное назад
if (USART1->ISR & USART_ISR_TC) {
	volatile static u08 i=0,step=0;
	switch (step) {
		case 0:
			USART1->RDR=out[i];
			i++;
			if (out[i]=='\0') {
				i=0;
				step=3;
			}
		break;
		case 1:
				USART1->RDR='\r';
				step=2;
		break;
		case 2:
				USART1->RDR='\n';
				step=0;
				StopUart1();
				status_uart=END;
		break;
		case 3:
				step=0;
				StopUart1();
				status_uart=END;
		break;

	}//sw
}}
*/
//-----------------------------------------------------------------------
/*
void FuncUart1Sh() {

volatile static u08 i=0,step=0;
//RX
//	if (USART1->ISR & USART_ISR_RXNE) {
	//	uart_data_rx = USART1->RDR;
//		return;
//	}
//TX
		if (USART1->ISR & USART_ISR_TC) {
		switch (step) {
			case 0:
				USART1->RDR=array_out[i];
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
				USART1->RDR='\r';
					step=2;
			break;
			case 2:
				USART1->RDR='\n';
					step=0;
					StopUart1();
					StartRxUart1();
					status_uart=END;
			break;
			case 3:
					step=0;
					StopUart1();
					StartRxUart1();
					status_uart=END;
			break;

		}//sw
	}//if
}//v
*/
/*
//-----------------------------------------------------------------------
void InitUart1() {
	// инициализация UART1
//	Включаем тактирование UART1. Он подключен к шине APB2.
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // включаем тактирование UART1
//	UART1 использует выводы: PA9 (для сигнала TX) и PA10 (сигнал RX). Надо задать конфигурацию для них.
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; // разрешаем тактирование порта GPIOA
	//Тактирование альтернативных функций GPIO
	//RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	// настройка вывода PA9 (TX1) на режим альтернативной функции с активным выходом
	// Биты CNF = 10, ,биты MODE = X1
	GPIOA->CRH &= (~GPIO_CRH_CNF9_0);
	GPIOA->CRH |= (GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9);
	// настройка вывода PA10 (RX1) на режим входа с подтягивающим резистором
	// Биты CNF = 10, ,биты MODE = 00, ODR = 1
	GPIOA->CRH &= (~GPIO_CRH_CNF10_0);
	GPIOA->CRH |= GPIO_CRH_CNF10_1;
	GPIOA->CRH &= (~(GPIO_CRH_MODE10));
	GPIOA->BSRR |= GPIO_ODR_ODR10;
//	Теперь конфигурация самого UART.
	// конфигурация UART1
	USART1->CR1 = USART_CR1_UE; // разрешаем USART1, сбрасываем остальные биты
//	Устанавливаем скорость обмена.
//	Частота тактирования UART1 72 мГц, нам нужна скорость 9600 бод. Вычисляем значение USARTDIV.
	//USARTDIV = Fck / (16 * BAUD) = 72000000 / (16 * 9600) = 468,75
	//	Значение регистра USART_BRR = 468,75 * 16 = 7500.
	//USART1->BRR = 7500; // скорость 9600 бод
	USART1->BRR = USARTDIV*16;
	// разрешаем приемник, передатчик и прерывание по приему
	//USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;
	USART1->CR1 |= USART_CR1_RE | USART_CR1_RXNEIE;
	USART1->CR2 = 0;
	USART1->CR3 = 0;
	// разрешения прерывания UART1 в контроллере прерываний
	NVIC_EnableIRQ (USART1_IRQn);
//	Инициализация закончена.
}
*/
//------------------------------------
/*
void StartTxUart1() {
	USART1->CR1 = 0;
	USART1->CR1 = USART_CR1_UE;
	USART1->CR1 |= USART_CR1_TE | (USART_CR1_TCIE);
	//UCSR0B = (0<<RXEN0)|(1<<TXEN0)|(0<<RXCIE0)|(0<<TXCIE0)|(1<<UDRIE0)|(0<<UCSZ02);
}
void StopUart1() {
	USART1->CR1 = 0;
	//USART1->CR1 &= ~(USART_CR1_TE);
	//USART1->CR1 &= ~(USART_CR1_TXEIE);
}
void StartRxUart1() {
	USART1->CR1 = 0;
	USART1->CR1 = USART_CR1_UE;
	USART1->CR1 |= USART_CR1_RE | USART_CR1_RXNEIE;
	//	UCSR0B = (1<<RXEN0)|(0<<TXEN0)|(1<<RXCIE0)|(0<<TXCIE0)|(0<<UDRIE0)|(0<<UCSZ02);
}
*/

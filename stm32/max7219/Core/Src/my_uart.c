#include "my_uart.h"
void SendLogUART(void){
	SendTextUart(" ",1);
	SendTextUart("adc1  ",0);
	SendTrimDigitUart(AdcResult_get_data_mv(),5,1);
	SendTextUart("BMP180:",0);
	SendTextUart("  Temp= ",0);
	SendTrimDigitUart(Temp_BMP180_get_data()/10,3,0);
	SendTextUart(".",0);
	SendTrimDigitUart(Temp_BMP180_get_data()%10,1,0);
	SendTextUart(" C",0);
	SendTextUart("  Pres=",0);
	SendTrimDigitUart(Pres_BMP180_get_data(),3,0);
	SendTextUart(" mm",0);
	SendTextUart("    Si7021:",0);
	SendTextUart("  Temp= ",0);
	SendTrimDigitUart(Temp_Si7021_get_data()/10,3,0);
	SendTextUart(".",0);
	SendTrimDigitUart(Temp_Si7021_get_data()%10,1,0);
	SendTextUart(" C",0);
	SendTextUart("  Hum=",0);
	SendTrimDigitUart(Hum_Si7021_get_data(),3,0);
	SendTextUart(" %",1);
}

/*
extern unsigned char out[];

void  USART1_IRQHandler() {
	FuncUartIT();
}
//----------------------------------------------------------------
void FuncUartIT() {
//	uint8_t d = USART1->DR; // получить данное
	//USART1->DR = d; // отослать данное назад
if (USART1->SR & USART_SR_TXE) {
	volatile static u08 i=0,step=0;
		switch (step) {
			case 0:
				USART1->DR=out[i];
				i++;
				if (out[i]=='\0') {
					i=0;
					step=3;
					//if(newline_of_string[0]==1)
						//step=1;
					//else
						//step=3;
				}
			break;
			case 1:
					USART1->DR='\r';
					step=2;
			break;
			case 2:
					USART1->DR='\n';
					step=0;
					StopUart1();
					//status_uart=END;
			break;
			case 3:
					step=0;
					StopUart1();
					//status_uart=END;
			break;

			}//sw
//	if (USART1->SR & USART_SR_RXNE) {
	//	USART1->DR = (USART1->DR)+1;
	 //}
}}
//-----------------------------------------------------------------------

void InitUart1() {
	// инициализация UART1
//	Включаем тактирование UART1. Он подключен к шине APB2.
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // включаем тактирование UART1
//	UART1 использует выводы: PA9 (для сигнала TX) и PA10 (сигнал RX). Надо задать конфигурацию для них.
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // разрешаем тактирование порта GPIOA
	//Тактирование альтернативных функций GPIO
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
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
	USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;
	USART1->CR2 = 0;
	USART1->CR3 = 0;
	// разрешения прерывания UART1 в контроллере прерываний
	NVIC_EnableIRQ (USART1_IRQn);
//	Инициализация закончена.
}
//------------------------------------

void StartTxUart1() {
	USART1->CR1 = 0;
	USART1->CR1 = USART_CR1_UE;
	USART1->CR1 |= USART_CR1_TE | (USART_CR1_TXEIE);
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

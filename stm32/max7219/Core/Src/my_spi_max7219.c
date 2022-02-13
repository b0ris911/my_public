#include "my_spi_max7219.h"

extern char FONT_7x5[96][5];

volatile u32 tmp=0;
volatile static u16 s1x=1,s1y=1,s2x=1,s2y=1,s3x=1,s3y=1,s4x=1,s4y=1;
static u08 b0[SIZE_VIRTUAL_ARRAY+NUMBER_OF_SEGMENTS*8]={0};
static u08 b1[NUMBER_OF_SEGMENTS*8]={0};//32 columns by 1 byte
static u08 b2[8][NUMBER_OF_SEGMENTS]={0};//8 lines by xxx segments
static u08 step_regime_max7219=0;
//--------------------------------------------------
//--------------------------------------------------
void Test_Modes_Max7219(void){//переключаемся между стат. и динам. массивами
	switch(step_regime_max7219) {
		case 0:
			StartGTimer(timer_max7219,1000);
			if(ExpGTimer(timer_max7219)){
				if(StaticVA())
					step_regime_max7219=1;
			}
			break;
		case 1:
			StartGTimer(timer_max7219,40);
			if(ExpGTimer(timer_max7219)){
				if(RunVA())
					step_regime_max7219=2;
			}
			break;
		case 2:
			StartGTimer(timer_max7219,15);
			if(ExpGTimer(timer_max7219)){
				if(RunningDots())
					step_regime_max7219=0;
			}
			break;
	}
}
//--------------------------------------------------
u08 RunVA(void){//выводим динамический массив
	CleanArray();
	if(DinVA()){
		return 1;
	}
	SwapArrays();
	ShowMax7219();
	return 0;
}
//--------------------------------------------------
u08 StaticVA(void){//по очереди выводим статические строки
volatile static u08 step_max7219=0;
	switch(step_max7219){
	case 0:
		CleanArray();
		SetString("Boris",26);
		step_max7219=1;
	break;
	case 1:
		CleanArray();
		SetString("  is ",26);
		step_max7219=2;
	break;
	case 2:
		CleanArray();
		SetString("super",26);
		step_max7219=3;
	break;
	case 3:
		CleanArray();
		SetString(" man!",26);
		step_max7219=4;
	break;
	case 4:
		step_max7219=0;
		return 1;
	}
	SwapArrays();
	ShowMax7219();
	return 0;
}
//--------------------------------------------------
u08 DinVA(void){//динамически заполняем массив
volatile static u16 i=0,max=SIZE_VIRTUAL_ARRAY-1;
volatile static u16 step=0;
	switch(step){
		case 0:
			for(u16 k=0;k<i+1;k++){
				b1[k]=b0[max+k];
			}
			i++;
			max--;
			if(i==NUMBER_OF_SEGMENTS*8){
				i=NUMBER_OF_SEGMENTS*8-1;
				step=1;
			}
		break;
		case 1:
			for(u16 k=0;k<NUMBER_OF_SEGMENTS*8;k++){
				b1[k]=b0[max+k];
			}
			max--;
			if(max==0){
				max=SIZE_VIRTUAL_ARRAY-1;
				step=0;
				return 1;
			}
		break;
	}
	return 0;
}
//--------------------------------------------------
void SetVirtualArray(char *string){//копируем строку во входящий динам. массив
volatile static u16 place=SIZE_VIRTUAL_ARRAY-5;
volatile static u08 i=0;
	while(string[i]!='\0'){
		b0[place+4]=FONT_7x5[string[i]-32][0];
		b0[place+3]=FONT_7x5[string[i]-32][1];
		b0[place+2]=FONT_7x5[string[i]-32][2];
		b0[place+1]=FONT_7x5[string[i]-32][3];
		b0[place]=FONT_7x5[string[i]-32][4];
		place-=6;
		i++;
		//counter+=6;
}}
//--------------------------------------------------
void CleanArray(void){//очищаем выходной массив в памяти
	for(u08 j=0;j<8;j++){
		for(u08 i=0;i<NUMBER_OF_SEGMENTS;i++){
			b2[j][i]=0;
		}
	}
}
//--------------------------------------------------
void SetString(char *string,u08 place){ //помещаем символ в место на матрице
volatile u08 i=0,k=0;
	while(string[i]!='\0'){
		SetSymbol(string[i++], place-k);
		k+=6;
	}
}
//--------------------------------------------------
void SetSymbol(char symbol,u08 place){ //place 31...0
	if(place>(NUMBER_OF_SEGMENTS*8-5)) place=NUMBER_OF_SEGMENTS*8-5;
	b1[place+4]=FONT_7x5[symbol-32][0];
	b1[place+3]=FONT_7x5[symbol-32][1];
	b1[place+2]=FONT_7x5[symbol-32][2];
	b1[place+1]=FONT_7x5[symbol-32][3];
	b1[place]=FONT_7x5[symbol-32][4];
}
//--------------------------------------------------
void ShowMax7219(void){//выводим выходной массив на матрицу
		for(u08 i=0;i<8;i++){
			CB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
			for(u08 s=NUMBER_OF_SEGMENTS;s>0;s--){
				SendWord(i+1,b2[i][s-1]);
			}
			SB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
		}
}
//--------------------------------------------------
//--------------------------------------------------------------------
void SwapArrays(void){//uncomment for 8 segments //меняем перпендикулярные массивы
	for(u08 j=0,k=1;j<8;j++,k*=2){
		for(u08 i=0;i<8;i++){
			b2[j][0]|=((b1[i]&k)>>j)<<i;
		}
	}
	for(u08 j=0,k=1;j<8;j++,k*=2){
		for(u08 i=8;i<16;i++){
			b2[j][1]|=((b1[i]&k)>>j)<<(i-8);
		}
	}
	for(u08 j=0,k=1;j<8;j++,k*=2){
		for(u08 i=16;i<24;i++){
			b2[j][2]|=((b1[i]&k)>>j)<<(i-16);
		}
	}

	for(u08 j=0,k=1;j<8;j++,k*=2){
		for(u08 i=24;i<32;i++){
			b2[j][3]|=((b1[i]&k)>>j)<<(i-24);
		}
	}

/*	for(u08 j=0,k=1;j<8;j++,k*=2){
		for(u08 i=32;i<40;i++){
			b2[j][4]|=((b1[i]&k)>>j)<<(i-32);
		}
	}
	for(u08 j=0,k=1;j<8;j++,k*=2){
		for(u08 i=40;i<48;i++){
			b2[j][5]|=((b1[i]&k)>>j)<<(i-40);
		}
	}
	for(u08 j=0,k=1;j<8;j++,k*=2){
		for(u08 i=48;i<56;i++){
			b2[j][6]|=((b1[i]&k)>>j)<<(i-48);
		}
	}
	for(u08 j=0,k=1;j<8;j++,k*=2){
		for(u08 i=56;i<64;i++){
			b2[j][7]|=((b1[i]&k)>>j)<<(i-56);
		}
	}*/
}
//--------------------------------------------------------------------
void SendOutBuffer(void){
	StartGTimer(timer_test_max7219,1000);
	if(ExpGTimer(timer_test_max7219)){
		for(u08 i=0;i<8;i++){
			CB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
			for(u08 j=4;j>0;j--){
				SendWord(j,b2[i][j]);
			}
			SB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
		}
	}
}
//--------------------------------------------------------------------
/*
void TestLine(void){
	StartGTimer(timer_test_max7219,1000);
	if(ExpGTimer(timer_test_max7219)){
		CB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
		SendWord(8,0b10000000);
		SendWord(7,0b01000000);
		SendWord(6,0b00100000);
		SendWord(5,0b00010000);
		SB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
		CB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
		SendWord(4,0b11110000);
		SendWord(3,0b01111000);
		SendWord(2,0b00111100);
		SendWord(1,0b00011110);
		SB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
	}
}
*/
//------------------------------------------
u08 RunningDots(void){
//volatile static u08 i=1,j=1,z=1;
volatile static u08 step=10;
//StartGTimer(timer_test_max7219,20);
	//if(ExpGTimer(timer_test_max7219)){
		CB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
		SendWord(s1y,s1x);
		SendWord(s2y,s2x);
		SendWord(s3y,s3x);
		SendWord(s4y,s4x);
		SB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);

		switch(step){
		case 10:
			s4x*=2;
			if(s4x>128){
				s4x=0;
				step=20;
				s3x=1;
			}
			break;
		case 20:
			s3x*=2;
			if(s3x>128){
				s3x=0;
				s2x=1;
				step=30;
			}
			break;
		case 30:
			s2x*=2;
			if(s2x>128){
				s2x=0;
				s1x=1;
				step=40;
			}
			break;
		case 40:
			s1x*=2;
			if(s1x>128){
				s1x=0;
				s4x=1;
				s4y++;
				s3y++;
				s2y++;
				s1y++;
				step=10;
				if(s4y>8){
					s4y=1;
					s3y=1;
					s2y=1;
					s1y=1;
					return 1;
				}
			}
			break;
		}
	return 0;
}
//------------------------------------------
void Clean_All(void){
	for(u08 i=1;i<9;i++){
		CB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
		SendWord(i,0);
		SendWord(i,0);
		SendWord(i,0);
		SendWord(i,0);
		SB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
	}
}
//------------------------------------------
void Init_4_MAX7219(void){      //инициализация MAX7219
	_delay_us(10);

	CB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
	SendWord(0x0C,0x01);   //Гашение индикатора
	SendWord(0x0C,0x01);   //Гашение индикатора
	SendWord(0x0C,0x01);   //Гашение индикатора
	SendWord(0x0C,0x01);   //Гашение индикатора
	SB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
	_delay_us(10);
	CB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
	SendWord(0x0A,0x00);   // Яркость минимум
	SendWord(0x0A,0x00);   // Яркость минимум
	SendWord(0x0A,0x00);   // Яркость минимум
	SendWord(0x0A,0x00);   // Яркость минимум
	SB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
	_delay_us(10);
	CB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
	SendWord(0x0B,0x07);   // Используется вся матрица
	SendWord(0x0B,0x07);   // Используется вся матрица
	SendWord(0x0B,0x07);   // Используется вся матрица
	SendWord(0x0B,0x07);   // Используется вся матрица
	SB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
	_delay_us(10);
	CB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
	SendWord(0x09,0x00);   // Отключение декодирования
	SendWord(0x09,0x00);   // Отключение декодирования
	SendWord(0x09,0x00);   // Отключение декодирования
	SendWord(0x09,0x00);   // Отключение декодирования
	SB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
}
void Init_MAX7219(void){      //инициализация MAX7219
	_delay_us(10);
	SendWord(0x0C,0x01);   //Гашение индикатора
	SendWord(0x0A,0x03);   // Яркость минимум
	SendWord(0x0B,0x07);   // Используется вся матрица
	SendWord(0x09,0x00);   // Отключение декодирования
}
//------------------------------------------
void Test_MAX7219(void){      //Тест матрицы
	CB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
	SendWord(0x0F,0x01);   //Включение всей матрицы на 0.2 секунды
	SendWord(0x0F,0x01);   //Включение всей матрицы на 0.2 секунды
	SendWord(0x0F,0x01);   //Включение всей матрицы на 0.2 секунды
	SendWord(0x0F,0x01);   //Включение всей матрицы на 0.2 секунды
	SB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
	_delay_ms(200);
	CB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
	SendWord(0x0F,0x00);
	SendWord(0x0F,0x00);
	SendWord(0x0F,0x00);
	SendWord(0x0F,0x00);
	SB(CS_MAX7219_GPIO_Port,CS_MAX7219_Pin);
}
//------------------------------------------
void SendWord(u08 reg,u08 byte){
	SendDataSPI_X((reg<<8)|byte);
}
//------------------------------------------
void  SendDataSPI_X(u16 data) {
	while(!(SPI_MODULE_MAX7219->SR & SPI_SR_TXE));
	*(u08*)&(SPI_MODULE_MAX7219->DR) = data>>8;
	tmp++;tmp++;
    while(!(SPI_MODULE_MAX7219->SR & SPI_SR_TXE));
    *(u08*)&(SPI_MODULE_MAX7219->DR) = data;
    tmp++;tmp++;
	while((SPI_MODULE_MAX7219->SR & SPI_SR_BSY));
}

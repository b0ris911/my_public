//--------------------------------------
#include "lcd1602.h"

volatile static u08 outreg=0;
extern u08 out[];
//-------------------------------
//-------------------------------
void LcdBackLightAlarm() {
volatile static u08 step=0;
switch (step) {
	case 0:
		TCCR1A = (1<<COM1A1)|(0<<COM1A0)|(0<<COM1B1)|(0<<COM1B0)|(0<<WGM11)|(1<<WGM10);
		TCCR1B = (0<<ICNC1)|(0<<ICES1)|(0<<WGM13)|(1<<WGM12)|(0<<CS12)|(1<<CS11)|(1<<CS10); 
		step=1;
	break;
	case 1:
		TCCR1A = 0;
		TCCR1B = 0;
		step=0;
	break;
}}
//-------------------------------

//-------------------------------
void LcdBackLightOn() {
TCCR1A = (1<<COM1A1)|(0<<COM1A0)|(0<<COM1B1)|(0<<COM1B0)|(0<<WGM11)|(1<<WGM10);
TCCR1B = (0<<ICNC1)|(0<<ICES1)|(0<<WGM13)|(1<<WGM12)|(0<<CS12)|(1<<CS11)|(1<<CS10); 
//StopGTimer(timer_backlightcounter);
//StartGTimer(timer_backlightcounter);
}
//-------------------------------
void LcdBackLightOff() {
TCCR1A = 0;
TCCR1B = 0;
}
//-------------------------------
volatile u08 light_lcd=OFF;
//funcs			
//-------------------------------
void LCD (u08 num) {

	for (u08 i=0; i<num; i++) {
		LcdWriteData(out[i]);
	}
}
//-------------------------------
void ReplaceDataPins() {
uint8_t temp=0;

temp=outreg&0b10000000;
if(temp>0)
	SB(PORT_DATA7,PDATA7);
else CB(PORT_DATA7,PDATA7);

temp=outreg&0b01000000;
if(temp>0)
	SB(PORT_DATA6,PDATA6);
else CB(PORT_DATA6,PDATA6);

temp=outreg&0b00100000;
if(temp>0)
	SB(PORT_DATA5,PDATA5);
else CB(PORT_DATA5,PDATA5);

temp=outreg&0b00010000;
if(temp>0)
	SB(PORT_DATA4,PDATA4);
else CB(PORT_DATA4,PDATA4);
}
//-------------------------------
void LcdClear() {
LcdWriteCom(0x01);
}
//-------------------------------
void LcdCursorBegin(){
LcdWriteCom(0x02);
}
//-------------------------------
void LcdGoto(u08 num_poz){
	if ((num_poz>=100)&&(num_poz<116))
		LcdWriteCom(128+(num_poz-100));
	if ((num_poz>=200)&&(num_poz<216))
		LcdWriteCom(192+(num_poz-200));		
}
//-------------------------------
void LcdOff() {
	LcdWriteCom(0x08);
}
//-------------------------------
void LcdCursorOff() {
	LcdWriteCom(0x0C);
}
//-------------------------------
void LcdCursorLine() {
	LcdWriteCom(0x0E);
}
//-------------------------------
void LcdCursorCube() {
	LcdWriteCom(0x0D);
}
//-------------------------------
void LcdCursorComplex() {
	LcdWriteCom(0x0F);
}
//-------------------------------
void LcdCursorLeft() {
	LcdWriteCom(0x04);
}
//-------------------------------
void LcdCursorRight() {
	LcdWriteCom(0x06);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void LcdWriteCom(unsigned char data)
{
uint8_t maj=0,min=0;

		maj=data & 0b11110000; 			//старшая тетрада
		min=(data<<4) & 0b11110000;		// младшая тетрада	
  		//pin03=outreg & 0b00001111;
		//ReplaceDataPins();

  		CB(PORT_RS, RS);    // уст. RS в 0
		CB(PORT_RW, RW);    // уст. RW в 0

		SB(PORT_EN, EN);				//поднимаем строб
  		_delay_us(5);
				
//		DDR_DATA |= (1<<4)|(1<<5)|(1<<6)|(1<<7);
		SB(DDR_DATA4,PDATA4);
		SB(DDR_DATA5,PDATA5);
		SB(DDR_DATA6,PDATA6);
		SB(DDR_DATA7,PDATA7);

		outreg = maj;		// выводим старшую тетраду  на шину
		ReplaceDataPins();
		CB(PORT_EN, EN); 				 //опускаем строб
  		_delay_us(5);

  		SB(PORT_EN, EN);
  		_delay_us(5);
		outreg = min;		// выводим младшую тетраду  на шину
		ReplaceDataPins();
		CB(PORT_EN,EN);

		if ((data==0x01)||(data==0x02)){			
			CLI
			_delay_us(1600);
			SEI
		}			
		else _delay_us(50);

//		CB(DDR_DATA4,PDATA4);
//		CB(DDR_DATA5,PDATA5);
//		CB(DDR_DATA6,PDATA6);
//		CB(DDR_DATA7,PDATA7);
}
 //ф-я записи данных
void LcdWriteData (unsigned char data)
{  	
uint8_t maj=0,min=0;

		maj=data & 0b11110000; 			//старшая тетрада
		min=(data<<4) & 0b11110000;		// младшая тетрада	
  				
		SB(PORT_RS, RS);     		// уст. RS в 1
		CB(PORT_RW, RW);    		// уст. RW в 0

		SB(PORT_EN, EN);				//поднимаем строб
  		_delay_us(5);
				
		SB(DDR_DATA4,PDATA4);
		SB(DDR_DATA5,PDATA5);
		SB(DDR_DATA6,PDATA6);
		SB(DDR_DATA7,PDATA7);		

		outreg = maj;		// выводим старшую тетраду  на шину
		ReplaceDataPins();
		CB(PORT_EN, EN); 				 //опускаем строб
  		_delay_us(5);

  		SB(PORT_EN, EN);
  		_delay_us(5);
		outreg = min;		// выводим младшую тетраду  на шину
		ReplaceDataPins();
		CB(PORT_EN,EN);
  		_delay_us(50);					//опускаем строб

}

//ф-я вывода строки
void LcdString(const char *str)
{
uint32_t data = 0;
	while (*str)
	{
		data = *str++;
		LcdWriteData(data);		
	}
}
//ф-я инициализации
void InitLcd()
{
		SB(DDR_RS,RS);
		SB(DDR_RW,RW);
		SB(DDR_EN,EN);
		SB(DDR_DATA4,PDATA4);
		SB(DDR_DATA5,PDATA5);
		SB(DDR_DATA6,PDATA6);
		SB(DDR_DATA7,PDATA7);

		_delay_ms(20);
  		CB(PORT_RS, RS);    // уст. RS в 0
  		CB(PORT_RW, RW);    // уст. RW в 0
  
  		SB(PORT_EN, EN);			//поднимаем строб
  		_delay_us(5);
  		outreg = 0b00110000;        	// выводим данные на шину
		ReplaceDataPins();
		CB(PORT_EN, EN); 			 //опускаем строб
  		_delay_ms(5);

  		SB(PORT_EN, EN);
  		_delay_us(5);
		outreg = 0b00110000;
		ReplaceDataPins();
		CB(PORT_EN,EN);
  		_delay_us(150);

   		SB(PORT_EN, EN);
  		_delay_us(2);
		outreg = 0b00110000;
		ReplaceDataPins();
		CB(PORT_EN,EN);
  		_delay_us(150);

   		SB(PORT_EN, EN);
  		_delay_us(5);		
		outreg = 0b00100000;		//перевели в 4-бит
		ReplaceDataPins();
		CB(PORT_EN,EN);  		
		_delay_us(50);		
   		SB(PORT_EN, EN);
  		_delay_us(5);
				
		outreg = 0b00100000;		//старшая тетрада 
		ReplaceDataPins();
		CB(PORT_EN,EN);
		
   		SB(PORT_EN, EN);
  		_delay_us(5);		
		outreg = 0b10000000;		//младшая тетрада 2 строки, символы 5*8
		ReplaceDataPins();
		CB(PORT_EN,EN);
		_delay_us(50);		
   		
		SB(PORT_EN, EN);
  		_delay_us(5);		
		outreg = 0b00000000;		//старшая тетрада 
		ReplaceDataPins();
		CB(PORT_EN,EN);

   		SB(PORT_EN, EN);
  		_delay_us(5);		
		outreg = 0b11100000;		//младшая тетрада вкл дисп, курсор в виде квадрата
		ReplaceDataPins();
		CB(PORT_EN,EN);
		_delay_us(50);		

   		SB(PORT_EN, EN);
  		_delay_us(5);		
		outreg = 0b00000000;		//старшая тетрада 
		ReplaceDataPins();
		CB(PORT_EN,EN);

   		SB(PORT_EN, EN);
  		_delay_us(5);		
		outreg = 0b00010000;		//младшая тетрада очистка дисплея
		ReplaceDataPins();
		CB(PORT_EN,EN);
		_delay_us(50);		

   		SB(PORT_EN, EN);
  		_delay_us(5);		
		outreg = 0b00000000;		//старшая тетрада 
		ReplaceDataPins();
		CB(PORT_EN,EN);

   		SB(PORT_EN, EN);
  		_delay_us(5);		
		outreg = 0b01100000;		//младшая тетрада инкремент, без сдвига
		ReplaceDataPins();
		CB(PORT_EN,EN);
		 _delay_ms(50);
 }

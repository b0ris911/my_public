#include "my_ws2812s.h"
#include "tim.h"

//static u16 array_work[]={WHITE,YELLOW,BLUE,CYAN,DARKCYAN,DARKGREEN,GREEN,GREENYELLOW,MAGENTA,MAROON,NAVY,OLIVE,ORANGE,PINK,PURPLE,RED,WHITE,YELLOW};
//u16 array_all_2[]={WHITE,YELLOW,BLUE,GREEN,RED,WHITE,YELLOW};
u16 array_all_3[]={BLUE,GREEN,RED,WHITE};
//static u16 array_work[]={BLUE,GREEN,RED,WHITE,ORANGE};
//static u16 array_work[]={RED,GREEN,BLUE,WHITE,YELLOW};
static u16 array_work[LED_COUNT]={0};
static u16 array_black[]={BLACK,BLACK,BLACK};
//volatile static u16 RGB565[LED_COUNT]={BLUE,RED,GREEN};
volatile static u16 mas[ARRAY_LENGTH*LED_COUNT+LED_COUNT]={0};
volatile static u16 red=0,green=0,blue=0;
volatile static u08 flag_step=OFF;
volatile static u16 top_of_brightness=100;
volatile static u16 brightness=0;
volatile static u08 flag_start_light_up=OFF;
volatile static u08 flag_start_light_down=OFF;
const u08 RGB565_8[]={
31,4,0,31,20,0,31,36,0,31,52,0,30,62,0,22,62,0,14,62,0,6,62,0,
0,62,2,0,62,10,0,62,18,0,62,26,0,60,31,0,44,31,0,28,31,0,12,31,
2,0,31,10,0,31,18,0,31,26,0,31,31,0,30,31,0,22,31,0,14,31,0,6};
volatile static u16 ind[LED_COUNT]={0};//индексы смещения по таблице RGB565 для каждого элемента массива array_work
volatile static u16 sizex=sizeof(RGB565_8);
//-------------------------------------------------------------
void ColorSnake(void){
volatile static u08 step=10;
u16 tmp1=0;
u08 y=0,k=0;
switch(step){
	case 10://заполняем начальные смещения
		tmp1=LED_COUNT/(sizex/3);//кол-во целых групп
		//tmp2=LED_COUNT - tmp1*(sizex/3);//неполная группа (если есть)
		while(y<tmp1){
			for(u08 i=0;i<(sizex/3);i++){//идем по группе
				k=i+y*(sizex/3);//индекс меняется в пределах одной группы
				ind[k]+=i*3; //смещаем по глубине в таблице цвета
				if(ind[k]>(sizex-1)){	 //идем по кругу в таблице цвета
					ind[k]=0;
				}
			}
			y++;//переходим на следующую группу
		}
		step=20;
	break;
	case 20:
		for(u08 i=0;i<LED_COUNT;i++){
				array_work[i]=RGB565_8[ind[i]]<<11 | RGB565_8[ind[i]+1]<<5 | RGB565_8[ind[i]+2];
				ind[i]+=3;
				if(ind[i]==sizex){
					ind[i]=0;
				}
			}
		break;
}}
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
void RunningColor2(void) {
volatile static u08 counter=0;
volatile static u08 step=20;
volatile static u08 r0=31,g0,b0;
volatile static u08 r1=31,g1,b1=31;
volatile static u08 r2,g2,b2=31;
volatile static u08 r3,g3=62,b3=31;
volatile static u08 r4,g4=62,b4;
volatile static u08 r5=31,g5=62,b5;
switch(step) {
	case 20:
		counter++;
		if(counter==31) {
			counter=0;
			step=30;
		}
		b0++;
		r1--;
		g2+=2;
		b3--;
		r4++;
		g5-=2;
		break;
	case 30:
		counter++;
		if(counter==31) {
			counter=0;
			step=40;
		}
		r0--;
		g1+=2;
		b2--;
		r3++;
		g4-=2;
		b5++;
		break;
	case 40:
		counter++;
		if(counter==31) {
			counter=0;
			step=50;
		}
		g0+=2;
		b1--;
		r2++;
		g3-=2;
		b4++;
		r5--;
		break;
	case 50:
		counter++;
		if(counter==31) {
			counter=0;
			step=60;
		}
		b0--;
		r1++;
		g2-=2;
		b3++;
		r4--;
		g5+=2;
		break;
	case 60:
		counter++;
		if(counter==31) {
			counter=0;
			step=70;
		}
		r0++;
		g1-=2;
		b2++;
		r3--;
		g4+=2;
		b5--;
		break;
	case 70:
		counter++;
		if(counter==31) {
			counter=0;
			step=20;
		}
		g0-=2;
		b1++;
		r2--;
		g3+=2;
		b4--;
		r5++;
		break;

}//sw
volatile u08 i=0;

	for(i=0;i<120;i+=6){//каждый шестой лед
		array_work[i]=r0<<11|g0<<5|b0;
	}
	for(i=1;i<120;i+=6){
		array_work[i]=r1<<11|g1<<5|b1;
	}
	for(i=2;i<120;i+=6){
		array_work[i]=r2<<11|g2<<5|b2;
	}
	for(i=3;i<120;i+=6){
		array_work[i]=r3<<11|g3<<5|b3;
	}
	for(i=4;i<120;i+=6){
		array_work[i]=r4<<11|g4<<5|b4;
	}
	for(i=5;i<120;i+=6){
		array_work[i]=r5<<11|g5<<5|b5;
	}
/*	SendTextUart("Red ",0);
	SendTrimDigitUart(r0,5,0);
	SendTextUart("      Green ",0);
	SendTrimDigitUart(g0,5,0);
	SendTextUart("      Blue ",0);
	SendTrimDigitUart(b0,5,1);
	*/
}
//-------------------------------------------------------------
//-------------------------------------------------------------
void RunningColor(void) {
volatile static u08 counter=0;
volatile static u08 step=20;
volatile static u08 r0=31,g0,b0;
volatile static u08 r1=31,g1,b1=31;
volatile static u08 r2,g2,b2=31;
volatile static u08 r3,g3=62,b3=31;
volatile static u08 r4,g4=62,b4;
volatile static u08 r5=31,g5=62,b5;
switch(step) {
	case 20:
		counter++;
		if(counter==31) {
			counter=0;
			step=30;
		}
		g0+=2;
		b1--;
		r2++;
		g3-=2;
		b4++;
		r5--;
		break;
	case 30:
		counter++;
		if(counter==31) {
			counter=0;
			step=40;
		}
		r0--;
		g1+=2;
		b2--;
		r3++;
		g4-=2;
		b5++;
		break;
	case 40:
		counter++;
		if(counter==31) {
			counter=0;
			step=50;
		}
		b0++;
		r1--;
		g2+=2;
		b3--;
		r4++;
		g5-=2;
		break;
	case 50:
		counter++;
		if(counter==31) {
			counter=0;
			step=60;
		}
		g0-=2;
		b1++;
		r2--;
		g3+=2;
		b4--;
		r5++;
		break;
	case 60:
		counter++;
		if(counter==31) {
			counter=0;
			step=70;
		}
		r0++;
		g1-=2;
		b2++;
		r3--;
		g4+=2;
		b5--;
		break;
	case 70:
		counter++;
		if(counter==31) {
			counter=0;
			step=20;
		}
		b0--;
		r1++;
		g2-=2;
		b3++;
		r4--;
		g5+=2;
		break;

}//sw
volatile u08 i=0;

	for(i=0;i<120;i+=6){//каждый шестой лед
		array_work[i]=r0<<11|g0<<5|b0;
	}
	for(i=1;i<120;i+=6){
		array_work[i]=r1<<11|g1<<5|b1;
	}
	for(i=2;i<120;i+=6){
		array_work[i]=r2<<11|g2<<5|b2;
	}
	for(i=3;i<120;i+=6){
		array_work[i]=r3<<11|g3<<5|b3;
	}
	for(i=4;i<120;i+=6){
		array_work[i]=r4<<11|g4<<5|b4;
	}
	for(i=5;i<120;i+=6){
		array_work[i]=r5<<11|g5<<5|b5;
	}
/*	SendTextUart("Red ",0);
	SendTrimDigitUart(r0,5,0);
	SendTextUart("      Green ",0);
	SendTrimDigitUart(g0,5,0);
	SendTextUart("      Blue ",0);
	SendTrimDigitUart(b0,5,1);
	*/
}
//-------------------------------------------------------------
void SmoothColorChange (void) {
volatile static u08 step=10;
volatile static u08 red=0,green=0,blue=0;
volatile static u16 difcolor=0;
switch(step) {
		case 10:
			red++;
			if(red==31) {
				step=20;
			}
			difcolor=red<<11|green<<5|blue;
			array_work[0]=difcolor;
			break;
		case 20:
			green+=2;
			if(green==62) {
				step=30;
			}
			difcolor=red<<11|green<<5|blue;
			array_work[0]=difcolor;

			break;
		case 30:
			red--;
			if(red==0){
				step=40;
			}
			difcolor=red<<11|green<<5|blue;
			array_work[0]=difcolor;
			break;
		case 40:
			blue++;
			if(blue==31){
				step=50;
			}
			difcolor=red<<11|green<<5|blue;
			array_work[0]=difcolor;
			break;
		case 50:
			green-=2;
			if(green==0){
				step=60;
			}
			difcolor=red<<11|green<<5|blue;
			array_work[0]=difcolor;
			break;
		case 60:
			red++;
			if(red==31){
				step=70;
			}
			difcolor=red<<11|green<<5|blue;
			array_work[0]=difcolor;
			break;
		case 70:
			blue--;
			if(blue==0){
				step=20;
			}
			difcolor=red<<11|green<<5|blue;
			array_work[0]=difcolor;
			break;
}}
//-------------------------------------------------------------
void Long_Line(void) {
volatile static u08 i=1;
volatile static u08 step_color=0;
volatile static u16 color=RED;
	if(i==1) {
		array_work[LED_COUNT-1]=0;
	}
	array_work[i]=color;
	array_work[i-1]=BLACK;
	i++;
	if(i==LED_COUNT) {
		i=1;
		step_color++;
		if(step_color==5)
			step_color=0;
		switch(step_color) {
			case 0:
				color=GREEN;
				break;
			case 1:
				color=BLUE;
				break;
			case 2:
				color=YELLOW;
				break;
			case 3:
				color=CYAN;
				break;
			case 4:
				color=RED;
				break;

		}
	}
}
//-------------------------------------------------------------
//-------------------------------------------------------------
void SetFlag(void) {
	flag_step=ON;
}
//-------------------------------------------------------------
void RUN_TestRotateColors(void) {
	TestRotateColors(10);
}
//-------------------------------------------------------------
void TestRotateColors(u08 number_of_colors){
volatile static u08 step=0;
	if(flag_step==ON) {
		flag_step=OFF;
		step++;
		if(step==4){
			step=0;
		}
	}
	switch(step){
		case 0:
			flag_start_light_up=ON;
			//RotateColors(array_RED,number_of_colors);
			break;
		case 1:
			flag_start_light_up=ON;
			//RotateColors(array_GREEN,number_of_colors);
			break;
		case 2:
			flag_start_light_up=ON;
			//RotateColors(array_BLUE,number_of_colors);
			break;
		case 3:
			flag_start_light_up=ON;
			RotateColors(array_all_3,number_of_colors);
			break;

	}
}
//-------------------------------------------------------------
void RotateColors(u16 array[],u08 number_of_colors) {//заполняем массив array_work нужным цветом
volatile static u08 k=0;
	if((number_of_colors<1)||(number_of_colors>10)) return;

	for(u08 i=0;i<number_of_colors;i++){
		if((i+k)<number_of_colors) {
			array_work[i]=array[i+k];
		}else {
			array_work[i]=array[i+k-number_of_colors];
		}
	}
	k++;
	if(k==number_of_colors ){
		k=0;
	}
}
//-------------------------------------------------------------
//-------------------------------------------------------------
void RUN_LedLine(void){
	ConvertRGB565to24_X(array_work,(u16)AdcResult_get_data_mv());//выводим array_work на ленту
}
//-------------------------------------------------------------
void ConvertRGB565to24_X(u16 RGB565[],u16 adc_data) {
volatile u32 color;
volatile u08 k=0;//переменная для кол-ва светодиодов (групп светодиодов)
volatile static s16 counter_light=0;
volatile static u08 step_counter=0;
volatile u08 delta=100/((TIME_ONE_COLOR/2)/TIME_LEDLINE);
//adc_data=100;
	if(flag_start_light_up==ON) {
		flag_start_light_up=OFF;
		step_counter=0;
		counter_light=0;
		top_of_brightness=adc_data/33;		//coeff of brightness in percent
	}

	switch(step_counter) {
		case 0:
			counter_light+=delta;
			if(counter_light>=100) {
				counter_light=100;
				step_counter=1;
			}
			break;
		case 1:
			counter_light-=delta;
			if(counter_light<=0) {
				counter_light=0;
				step_counter=2;
			}
			break;
		case 2:
			break;
	}
	brightness=(top_of_brightness*counter_light)/100;
	brightness=adc_data/33;
	//brightness=100;

	for(k=0;k<LED_COUNT;k++){
		red = ((RGB565[k] & 0xF800)>>11)*8;
		red=(red*brightness)/100;
		green = ((RGB565[k] & 0x07E0)>>5)*4;
		green=(green*brightness)/100;
		blue = (RGB565[k] & 0x001F)*8;
		blue=(blue*brightness)/100;

		color = (InverseByte((u08)blue))<<16 | (InverseByte((u08)red))<<8 | InverseByte((u08)green);
		mas[k*25]=0;
		for(u08 i=0;i<ARRAY_LENGTH;i++) {
			if(color & (1<<i)) {
				mas[(ARRAY_LENGTH+1)*k + i+1]=HIGH_TIME;
			}
			else {
				mas[(ARRAY_LENGTH+1)*k + i+1]=LOW_TIME;
			}
		}
	}
	mas[ARRAY_LENGTH*LED_COUNT+LED_COUNT]=0;
	HAL_TIM_Base_Stop(&htim1);
	__HAL_TIM_SET_COUNTER (&htim1, 0);
	HAL_TIM_PWM_Start_DMA (&htim1,TIM_CHANNEL_1,(u32*)mas,ARRAY_LENGTH*LED_COUNT+LED_COUNT+1);
}//v
//-------------------------------------------------------------
void BlackLine(void) {
	ConvertRGB565to24_X(array_black,4000);
}



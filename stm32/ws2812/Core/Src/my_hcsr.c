#include "my_hcsr.h"

#include "tim.h"


volatile static u16 data_from_hcsr=0;

volatile static u08 step_int_hcsr=0;
//---------------------------------------------
u16 DataFromHcsr_get_data() {
	return data_from_hcsr;
}
u16 Distance_get_data() {
	return data_from_hcsr/59;
}
//---------------------------------------------
void Alg_HCSR () {
	  u16 tmp=0;
  if (GetMessage(MSG_FLAG_SHOW_DATA_HCSR)) {
	  tmp=DataFromHcsr_get_data()/59;
	  if(tmp>300)
		  tmp=300;
	  TFTDrawUT32(64,2,GREEN,FONE,tmp,4,2);
  }//if
}
//---------------------------------------------
void StartTrig() {
	StartGTimer(timer_trig,250);
	if(ExpGTimer(timer_trig)) {
		step_int_hcsr=0;
//		CLI
		HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);
		_delay_us(11);
		HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);

		EXTI->IMR=EXTI_IMR_IM0; //enable EXTI
		EXTI->RTSR=EXTI_RTSR_TR0;//rising
//		SEI
	}
}
void HAL_GPIO_EXTI_Callback(u16 GPIO_Pin) {
	if(GPIO_Pin == ECHO_Pin) {
		switch(step_int_hcsr) {
			case 0:
				TIM7->CNT=0;
				HAL_TIM_Base_Start(&htim7);

				EXTI->FTSR=EXTI_FTSR_TR0;//switch to falling
				step_int_hcsr=1;

			break;

			case 1:
				HAL_TIM_Base_Stop(&htim7);
				EXTI->IMR &= ~EXTI_IMR_IM0;//disable EXTI
				data_from_hcsr=TIM7->CNT;
				SendMessage(MSG_FLAG_SHOW_DATA_HCSR);
				//flag_show_data_hcsr=ON;
			break;
		}//sw
	}//if
}//void

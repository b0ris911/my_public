/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_ADC1_Init();
  MX_UART4_Init();
  MX_SPI3_Init();
  MX_I2C1_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
  InitGTimers();
  InitMessages();
  /* USER CODE END 2 */
  DWT_Init();

   __HAL_SPI_ENABLE(&hspi3);
   _delay_ms(1);
   ST7735Init();
   _delay_ms(5);
   St7735FillScreen(FONE);
   _delay_ms(200);

   TFTDrawString(0,2,YELLOW,FONE,"Dis:",2);
   TFTDrawString(0,18, GREEN,FONE, "U=",2);
   TFTDrawString(95,18, GREEN,FONE, "mV",2);

   TFTDrawString(20,34,ORANGE,FONE,"Si7021",2);
   TFTDrawString(0,50,GREEN,FONE,"H:",2);
   TFTDrawString(0,66,GREEN,FONE,"T:",2);

   TFTDrawString(20,89,ORANGE,FONE,"BMP180",2);
   TFTDrawString(0,107,GREEN,FONE,"P:",2);
   TFTDrawString(85,107,GREEN,FONE,"mm",2);
   TFTDrawString(0,125,GREEN,FONE,"T:",2);

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)  {

  	  StartGTimer(timer_process_ws2812,TIME_LEDLINE);
  	  if(ExpGTimer(timer_process_ws2812)) {
  		RUN_LedLine();
  	  }

volatile static u08 time_color=40;
volatile static u08 func_color=0;

  	  StartGTimer(timer_smooth_change_color,time_color);
  	  if(ExpGTimer(timer_smooth_change_color)){
  		  switch(func_color){
  		  	  case 0:
  		  		  ColorSnake();
  		  		  break;
  		  	  case 1:
  		  		  RunningColor2();
  		  		  break;
  		  }
  	  }

  	  volatile static u08 step_fc=1;
  	  StartGTimer(timer_change_func_color,5000);
  	  if(ExpGTimer(timer_change_func_color)){
		  switch(step_fc){
			  case 0:
				  time_color=40;
				  step_fc=1;
				  func_color=0;
				  break;
			  case 1:
				  time_color=2;
				  step_fc=0;
				  func_color=1;
				  break;
		  }
  	  }

	  StartGTimer(timer_led,1000);
	  if(ExpGTimer(timer_led)) {
		  TB(GPIOF,Sysled_PF9_Pin);
	  }//i

	  //Run HCSR-04
	  StartTrig();
	  Alg_HCSR();

	  //Run log at UART
	  StartGTimer(timer_uart,300);
	  if(ExpGTimer(timer_uart)) {
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

		  TFTDrawUT32(32,18,GREEN,FONE,AdcResult_get_data_mv(),4,2);
	  }//i
	//--------------------------------------------------
	  StartGTimer(timer_start_adc,2);
	  if(ExpGTimer(timer_start_adc)) {
		  HAL_ADC_Start_IT(&hadc1);
	  }

	  StartGTimer(timer_start_i2c,2000);
	  if(ExpGTimer(timer_start_i2c)){
		  ShedulerI2C(BMP180);
		  ShedulerI2C(Si7021);
	  }
	//--------------------------------------------------
	ProcessShedulerI2c();
	//--------------------------------------------------
	ProcessShedulerUart(&huart4);
	//--------------------------------------------------
	ProcessMessages();
	//--------------------------------------------------
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

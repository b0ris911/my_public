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
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
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

TaskHandle_t Handle_vTaskTestTimer;
TaskHandle_t Handle_vTaskTestLed;
TaskHandle_t Handle_vTaskStartAdcConversion;
TaskHandle_t Handle_vTaskShowAdcResultOnUART;
TaskHandle_t Handle_vTaskSi7021_BMP180;
TaskHandle_t Handle_vTaskProcessShedulerI2C;
TaskHandle_t Handle_vTaskMemory;
TaskHandle_t Handle_vTaskStartTrig;
TaskHandle_t Handle_vTaskRunLedLine;
TaskHandle_t Handle_vTaskGSCC;
TaskHandle_t Handle_vTaskProcessUart;
TaskHandle_t Handle_vTaskAlg_HCSR;
TaskHandle_t Handle_vTaskStartTrig;
TaskHandle_t Handle_vTaskLightEffects;
TaskHandle_t Handle_vTaskRunLedLine;
TaskHandle_t Handle_vTaskChangeLightEffects;
TaskHandle_t Handle_vTaskTest_Modes_Max7219;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
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
  MX_SPI3_Init();
  MX_I2C1_Init();
  MX_ADC1_Init();
  MX_TIM7_Init();
  MX_TIM1_Init();
  MX_UART4_Init();
//  MX_SPI1_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */

  DWT_Init();

  InitQueueUART();
  __HAL_SPI_ENABLE(&hspi3);
  __HAL_SPI_ENABLE(&hspi2);
  _delay_ms(500);
   InitTFT4();
   TFTDrawPixel(2,2,GREEN);
  //ST7735Init();
  _delay_ms(5);
  TFTFillScreen(FONE);
  _delay_ms(200);

  TFTFillScreen(GREEN);
  _delay_ms(100);
  TFTFillScreen(RED);
  _delay_ms(50);
  TFTFillScreen(FONE);
  _delay_ms(100);

  //TFTDrawString(0,2,YELLOW,FONE,"Dist:",2);
  TFTDrawString(0,18, GREEN,FONE, "U=",2);
  TFTDrawString(95,18, GREEN,FONE, "mV",2);

  TFTDrawString(20,34,ORANGE,FONE,"Si7021",2);
  TFTDrawString(0,51,GREEN,FONE,"H:",2);
  TFTDrawString(0,69,GREEN,FONE,"T:",2);

  TFTDrawString(20,89,ORANGE,FONE,"BMP180",2);
  TFTDrawString(0,107,GREEN,FONE,"P:",2);
  TFTDrawString(85,107,GREEN,FONE,"mm",2);
  TFTDrawString(0,125,GREEN,FONE,"T:",2);

//max7219
  Init_4_MAX7219();
  Test_MAX7219();
  Clean_All();
  SetVirtualArray("Come with me, baby :)       ");


  //LED
   xTaskCreate(vTaskTestLed, (const char * const)"TestLed",configMINIMAL_STACK_SIZE,NULL,1,&Handle_vTaskTestLed);
   //UART
   xTaskCreate(vTaskProcessUart,(const char * const)"vTaskProcessUart",configMINIMAL_STACK_SIZE,NULL,1,&Handle_vTaskProcessUart);
   //Memory
   xTaskCreate(vTaskMemory,(const char * const)"vTaskMemory",configMINIMAL_STACK_SIZE,NULL,1,&Handle_vTaskMemory);
   //ADC
   xTaskCreate(vTaskStartAdcConversion,(const char * const)"StartADC",configMINIMAL_STACK_SIZE,NULL,1,&Handle_vTaskStartAdcConversion);
   xTaskCreate(vTaskShowADC, (const char * const)"ShowADC",configMINIMAL_STACK_SIZE,NULL,1,&Handle_vTaskShowAdcResultOnUART);
   //I2C
   xTaskCreate(vTaskSi7021_BMP180,(const char * const)"vTaskSi7021_BMP180",configMINIMAL_STACK_SIZE,NULL,1,&Handle_vTaskSi7021_BMP180);
   xTaskCreate(vTaskProcessShedulerI2C,(const char * const)"ProcessShedulerI2C",configMINIMAL_STACK_SIZE,NULL,3,&Handle_vTaskProcessShedulerI2C);
   //max7219
   xTaskCreate(vTaskTest_Modes_Max7219, (const char * const)"Test_Modes_Max7219",configMINIMAL_STACK_SIZE,NULL,1,&Handle_vTaskTest_Modes_Max7219);

  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();
  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)  {
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
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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

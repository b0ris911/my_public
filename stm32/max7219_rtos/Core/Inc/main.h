/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "my_head_files.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_PF9_Pin GPIO_PIN_9
#define LED_PF9_GPIO_Port GPIOF
#define LED_PF10_Pin GPIO_PIN_10
#define LED_PF10_GPIO_Port GPIOF
#define CS_TOUCH_Pin GPIO_PIN_4
#define CS_TOUCH_GPIO_Port GPIOC
#define CS_MAX7219_Pin GPIO_PIN_11
#define CS_MAX7219_GPIO_Port GPIOB
#define TOUCH_TRIG_Pin GPIO_PIN_7
#define TOUCH_TRIG_GPIO_Port GPIOC
#define CS_TFT_Pin GPIO_PIN_0
#define CS_TFT_GPIO_Port GPIOD
#define DC_Pin GPIO_PIN_1
#define DC_GPIO_Port GPIOD
#define RST_Pin GPIO_PIN_2
#define RST_GPIO_Port GPIOD
#define ECHO_Pin GPIO_PIN_0
#define ECHO_GPIO_Port GPIOE
#define ECHO_EXTI_IRQn EXTI0_IRQn
#define TRIG_Pin GPIO_PIN_1
#define TRIG_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define SOL1_Pin GPIO_PIN_2
#define SOL1_GPIO_Port GPIOE
#define SOL2_Pin GPIO_PIN_3
#define SOL2_GPIO_Port GPIOE
#define SOL3_Pin GPIO_PIN_4
#define SOL3_GPIO_Port GPIOE
#define SOL4_Pin GPIO_PIN_0
#define SOL4_GPIO_Port GPIOA
#define SOL5_Pin GPIO_PIN_1
#define SOL5_GPIO_Port GPIOA
#define SOL6_Pin GPIO_PIN_2
#define SOL6_GPIO_Port GPIOA
#define STATUS_G_Pin GPIO_PIN_8
#define STATUS_G_GPIO_Port GPIOD
#define STATUS_R_Pin GPIO_PIN_9
#define STATUS_R_GPIO_Port GPIOD
#define STATUS_B_Pin GPIO_PIN_10
#define STATUS_B_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

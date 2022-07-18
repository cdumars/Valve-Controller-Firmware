/*******************************************************************************
*
* FILE:
* 		main.c
*
* DESCRIPTION:
* 		Processes commands recieved from a host PC, provides fine control over
*       valve controller hardware resources
*
*******************************************************************************/


/*------------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "main.h"
#include "commands.h"
#include "solenoid.h"


/*------------------------------------------------------------------------------
 Global Variables
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 MCU Peripheral Handlers
------------------------------------------------------------------------------*/
UART_HandleTypeDef huart4;


/*------------------------------------------------------------------------------
 Function prototypes
------------------------------------------------------------------------------*/
void SystemClock_Config(void); /* Clock configuration */
static void GPIO_Init(void); /* GPIO Initialization */
static void UART4_Init(void); /* UART Initialization  */


/*------------------------------------------------------------------------------
 Application entry point
------------------------------------------------------------------------------*/
int main
	(
	void
	)
{
/*------------------------------------------------------------------------------
 Local Variables
------------------------------------------------------------------------------*/
uint8_t data; /* USB Incoming Data Buffer */
uint8_t sol_subcommand; /* Solenoid subcommand code */
uint8_t command_status; /* UART timeout status */

/*------------------------------------------------------------------------------
 MCU Initialization
------------------------------------------------------------------------------*/
HAL_Init(); /* Reset peripherals, initialize flash interface and Systick. */
SystemClock_Config(); /* System clock */
GPIO_Init(); /* GPIO  */
UART4_Init(); /* USB UART */


/*------------------------------------------------------------------------------
 Event Loop
------------------------------------------------------------------------------*/
while (1)
	{
	/* Read data from UART reciever */
	command_status = HAL_UART_Receive(&huart4, &data, 1, 1);

	/* Parse command input if HAL_UART_Receive doesn't timeout */
	if ( command_status != HAL_TIMEOUT )
		{
		switch(data)
			{
			/* Ping Command -----------------------------------------------------*/
			case PING_OP:
				ping(&huart4);
				break;

			/* Connect Command --------------------------------------------------*/
			case CONNECT_OP:
				ping(&huart4);
				break;

			/* Solenoid Command -------------------------------------------------*/
			case SOL_OP:
				command_status = HAL_UART_Receive(&huart4, &sol_subcommand, 1, 1);
				if ( command_status != HAL_TIMEOUT )
					{
					solenoid_cmd_execute(sol_subcommand);
					}
				else
					{
					/* Do nothing */
					Error_Handler();
					}
				break;

			default:
				/* Do nothing */
            break;
			}
		}
	else /* USB connection times out */
		{
		/* Do nothing */
		}
	}
} /* main */

/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
* 		SystemClock_Config                                                     *
*                                                                              *
* DESCRIPTION:                                                                 *
* 		Initializes the microcontroller clock. Enables peripheral clocks and   *
*       sets prescalers                                                        *
*                                                                              *
*******************************************************************************/
void SystemClock_Config
	(
	void
	)
{
RCC_OscInitTypeDef RCC_OscInitStruct = {0};
RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

/** Supply configuration update enable
*/
HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
/** Configure the main internal regulator output voltage
*/
__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY))
	{
	/* Wait for PWR_FLAG_VOSRDY flag */
	}

/* Initializes the RCC Oscillators according to the specified parameters
    in the RCC_OscInitTypeDef structure. */
RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
	Error_Handler();
	}
else /* RCC Oscillator configuration is okay */
	{
	/* Do nothing */
	}

/* Initializes the CPU, AHB and APB buses clocks */
RCC_ClkInitStruct.ClockType =      RCC_CLOCKTYPE_HCLK    |
                                   RCC_CLOCKTYPE_SYSCLK  |
						           RCC_CLOCKTYPE_PCLK1   |
                                   RCC_CLOCKTYPE_PCLK2   |
						           RCC_CLOCKTYPE_D3PCLK1 |
                                   RCC_CLOCKTYPE_D1PCLK1;
RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_HSI;
RCC_ClkInitStruct.SYSCLKDivider  = RCC_SYSCLK_DIV1;
RCC_ClkInitStruct.AHBCLKDivider  = RCC_HCLK_DIV1;
RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
	{
	Error_Handler();
	}
else /* RCC Configuration okay */
	{
	/* Do Nothing */
	}
} /* SystemClock_Config */

/*******************************************************************************
*                                                                              *
* PROCEDURE NAME:                                                              *
* 		UART_Init                                                              *
*                                                                              *
* DESCRIPTION:                                                                 *
* 		Initializes the UART interface used for USB communication with a host  *
*       PC                                                                     *
*                                                                              *
*******************************************************************************/
static void UART4_Init
	(
	void
	)
{
/* UART handler instance */
huart4.Instance = UART4;

/* Initialization settings */
huart4.Init.BaudRate = 9600;
huart4.Init.WordLength = UART_WORDLENGTH_8B;
huart4.Init.StopBits = UART_STOPBITS_1;
huart4.Init.Parity = UART_PARITY_NONE;
huart4.Init.Mode = UART_MODE_TX_RX;
huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
huart4.Init.OverSampling = UART_OVERSAMPLING_16;
huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
huart4.Init.ClockPrescaler = UART_PRESCALER_DIV1;
huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

/* Write to registers and call error handler if initialization fails */
if (HAL_UART_Init(&huart4) != HAL_OK)
	{
	Error_Handler();
	}
if (HAL_UARTEx_SetTxFifoThreshold(&huart4, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
	Error_Handler();
	}
if (HAL_UARTEx_SetRxFifoThreshold(&huart4, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
	Error_Handler();
	}
if (HAL_UARTEx_DisableFifoMode(&huart4) != HAL_OK)
	{
	Error_Handler();
	}
} /* UART_Init */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
* 		GPIO_Init                                                              *
*                                                                              *
* DESCRIPTION:                                                                 *
* 		Initializes all GPIO pins and sets alternate functions                 *
*                                                                              *
*******************************************************************************/
static void GPIO_Init
	(
    void
	)
{
/* GPIO Initialization Struct */
GPIO_InitTypeDef GPIO_InitStruct = {0};

/* GPIO Ports Clock Enable */
__HAL_RCC_GPIOA_CLK_ENABLE();
__HAL_RCC_GPIOC_CLK_ENABLE();
__HAL_RCC_GPIOD_CLK_ENABLE();
__HAL_RCC_GPIOE_CLK_ENABLE();

/*Configure GPIO pin Output Levels */
HAL_GPIO_WritePin(GPIOE, SOL1_PIN|SOL2_PIN|SOL3_PIN, GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOA, SOL4_PIN|SOL5_PIN|SOL6_PIN|STATUS_PIN, GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOD, EXCEPT_PIN, GPIO_PIN_RESET);

/* Configure Solenoid GPIO pins 1-3 */
GPIO_InitStruct.Pin   = SOL1_PIN|SOL2_PIN|SOL3_PIN;
GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull  = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

/* Configure STATUS GPIO pin and Solenoid GPIO pins 4-6 */
GPIO_InitStruct.Pin   = SOL4_PIN|SOL5_PIN|SOL6_PIN|STATUS_PIN;
GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull  = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* Configure EXCEPT GPIO pin */
GPIO_InitStruct.Pin   = EXCEPT_PIN;
GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull  = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(EXCEPT_PORT, &GPIO_InitStruct);

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
  HAL_GPIO_WritePin(EXCEPT_PORT, EXCEPT_PIN, GPIO_PIN_SET);
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
}
#endif /* USE_FULL_ASSERT */


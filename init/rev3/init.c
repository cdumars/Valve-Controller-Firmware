/*******************************************************************************
*                                                                              *
* FILE:                                                                        *
* 		init.c                                                                 *
*                                                                              *
* DESCRIPTION:                                                                 *
* 		Contains initialization routines for MCU core and peripherals          *
*                                                                              *
*******************************************************************************/


/*------------------------------------------------------------------------------
 Standard Includes                                                              
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 Project Includes                                                               
------------------------------------------------------------------------------*/
#include "sdr_pin_defines_L0005.h"
#include "main.h"
#include "init.h"


/*------------------------------------------------------------------------------
 Global Variables 
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 Procedures 
------------------------------------------------------------------------------*/


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

/* Supply configuration update enable */
HAL_PWREx_ConfigSupply( PWR_LDO_SUPPLY );

/* Configure the main internal regulator output voltage */
__HAL_PWR_VOLTAGESCALING_CONFIG( PWR_REGULATOR_VOLTAGE_SCALE3 );

while( !__HAL_PWR_GET_FLAG( PWR_FLAG_VOSRDY ) )
	{
	/* Wait for PWR_FLAG_VOSRDY flag */
	}

/* Initializes the RCC Oscillators according to the specified parameters
   in the RCC_OscInitTypeDef structure. */
RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
RCC_OscInitStruct.HSIState            = RCC_HSI_DIV1;
RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_NONE;
if ( HAL_RCC_OscConfig( &RCC_OscInitStruct ) != HAL_OK )
	{
	Error_Handler();
	}
else /* RCC Oscillator configuration is okay */
	{
	/* Do nothing */
	}

/* Initializes the CPU, AHB and APB buses clocks */
RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK    |
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

if ( HAL_RCC_ClockConfig( &RCC_ClkInitStruct, FLASH_LATENCY_1 ) != HAL_OK )
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
* PROCEDURE:                                                                   *
* 		Valve_TIM_Init                                                         *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Initializes the valve control timers and PWM channels                  *
*                                                                              *
*******************************************************************************/
void Valve_TIM_Init
	(
	void
	)
{
/* HAL Init structs */
TIM_ClockConfigTypeDef         sClockSourceConfig = {0};
TIM_MasterConfigTypeDef        sMasterConfig      = {0};
TIM_OC_InitTypeDef             sConfigOC = {0};
TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

/* Base timer initialization */
htim15.Instance               = TIM15;
htim15.Init.Prescaler         = 0;
htim15.Init.CounterMode       = TIM_COUNTERMODE_UP;
htim15.Init.Period            = 63999;
htim15.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
htim15.Init.RepetitionCounter = 0;
htim15.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
if ( HAL_TIM_Base_Init( &htim15 ) != HAL_OK )
	{
	Error_Handler();
	}

/* Clock source configuration */
sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
if ( HAL_TIM_ConfigClockSource( &htim15, &sClockSourceConfig ) != HAL_OK )
	{
	Error_Handler();
	}

/* PWM Initialization */
if ( HAL_TIM_PWM_Init( &htim15 ) != HAL_OK )
	{
	Error_Handler();
	}

/* Master slave mode configuration */
sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
sMasterConfig.MasterSlaveMode     = TIM_MASTERSLAVEMODE_DISABLE;
if ( HAL_TIMEx_MasterConfigSynchronization( &htim15, &sMasterConfig ) != HAL_OK )
	{
	Error_Handler();
	}

/* Setup PWM Outputs */
sConfigOC.OCMode       = TIM_OCMODE_PWM1;
sConfigOC.Pulse        = 32000;
sConfigOC.OCPolarity   = TIM_OCPOLARITY_HIGH;
sConfigOC.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
sConfigOC.OCFastMode   = TIM_OCFAST_DISABLE;
sConfigOC.OCIdleState  = TIM_OCIDLESTATE_RESET;
sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
if ( HAL_TIM_PWM_ConfigChannel( &htim15, &sConfigOC, TIM_CHANNEL_1 ) != HAL_OK )
	{
	Error_Handler();
	}
if ( HAL_TIM_PWM_ConfigChannel( &htim15, &sConfigOC, TIM_CHANNEL_2 ) != HAL_OK )
	{
	Error_Handler();
	}

/* Additional inits */
sBreakDeadTimeConfig.OffStateRunMode  = TIM_OSSR_DISABLE;
sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
sBreakDeadTimeConfig.LockLevel        = TIM_LOCKLEVEL_OFF;
sBreakDeadTimeConfig.DeadTime         = 0;
sBreakDeadTimeConfig.BreakState       = TIM_BREAK_DISABLE;
sBreakDeadTimeConfig.BreakPolarity    = TIM_BREAKPOLARITY_HIGH;
sBreakDeadTimeConfig.BreakFilter      = 0;
sBreakDeadTimeConfig.AutomaticOutput  = TIM_AUTOMATICOUTPUT_DISABLE;
if ( HAL_TIMEx_ConfigBreakDeadTime( &htim15, &sBreakDeadTimeConfig ) != HAL_OK )
	{
	Error_Handler();
	}
HAL_TIM_MspPostInit( &htim15 );

} /* Valve_TIM_Init */


/*******************************************************************************
*                                                                              *
* PROCEDURE NAME:                                                              *
* 		USB_UART_Init                                                          *
*                                                                              *
* DESCRIPTION:                                                                 *
* 		Initializes the UART interface used for USB communication with a host  *
*       PC                                                                     *
*                                                                              *
*******************************************************************************/
void USB_UART_Init 
	(
	void
	)
{
/* UART handler instance */
huart3.Instance = USART3;

/* Initialization settings */
huart3.Init.BaudRate               = 921600;
huart3.Init.WordLength             = UART_WORDLENGTH_8B;
huart3.Init.StopBits               = UART_STOPBITS_1;
huart3.Init.Parity                 = UART_PARITY_NONE;
huart3.Init.Mode                   = UART_MODE_TX_RX;
huart3.Init.HwFlowCtl              = UART_HWCONTROL_NONE;
huart3.Init.OverSampling           = UART_OVERSAMPLING_16;
huart3.Init.OneBitSampling         = UART_ONE_BIT_SAMPLE_DISABLE;
huart3.Init.ClockPrescaler         = UART_PRESCALER_DIV1;
huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

/* Write to registers and call error handler if initialization fails */
if ( HAL_UART_Init( &huart3 ) != HAL_OK )
	{
	Error_Handler();
	}
if ( HAL_UARTEx_SetTxFifoThreshold( &huart3, UART_TXFIFO_THRESHOLD_1_8 ) != HAL_OK )
	{
	Error_Handler();
	}
if ( HAL_UARTEx_SetRxFifoThreshold( &huart3, UART_RXFIFO_THRESHOLD_1_8 ) != HAL_OK )
	{
	Error_Handler();
	}
if ( HAL_UARTEx_DisableFifoMode( &huart3 ) != HAL_OK )
	{
	Error_Handler();
	}
} /* USB_UART_Init */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
* 		GPIO_Init                                                              *
*                                                                              *
* DESCRIPTION:                                                                 *
* 		Initializes all GPIO pins and sets alternate functions                 *
*                                                                              *
*******************************************************************************/
void GPIO_Init
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

/*--------------------------- LED MCU PINS -----------------------------------*/

/*Configure GPIO pin Output Levels */
HAL_GPIO_WritePin( STATUS_GPIO_PORT, STATUS_PIN, GPIO_PIN_RESET );
HAL_GPIO_WritePin( EXCEPT_GPIO_PORT, EXCEPT_PIN, GPIO_PIN_RESET );

/* Configure STATUS GPIO pin and Solenoid GPIO pins 4-6 */
GPIO_InitStruct.Pin   = STATUS_PIN;
GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull  = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init( STATUS_GPIO_PORT, &GPIO_InitStruct );

/* Configure EXCEPT GPIO pin */
GPIO_InitStruct.Pin   = EXCEPT_PIN;
GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull  = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init( EXCEPT_GPIO_PORT, &GPIO_InitStruct );

/*------------------------ SOLENOID MCU PINS ---------------------------------*/

/* Configure GPIO pin Output Levels */
HAL_GPIO_WritePin( SOL1_GPIO_PORT, SOL1_PIN|SOL2_PIN|SOL3_PIN, GPIO_PIN_RESET );
HAL_GPIO_WritePin( SOL4_GPIO_PORT, SOL4_PIN|SOL5_PIN|SOL6_PIN, GPIO_PIN_RESET );

/* Configure Solenoid GPIO pins 1-3 */
GPIO_InitStruct.Pin   = SOL1_PIN | SOL2_PIN | SOL3_PIN;
GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull  = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init( SOL1_GPIO_PORT, &GPIO_InitStruct);

/* Configure Solenoid GPIO pins 4-6 */
GPIO_InitStruct.Pin   = SOL4_PIN | SOL5_PIN | SOL6_PIN;
GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull  = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init( SOL4_GPIO_PORT, &GPIO_InitStruct);

/*----------------------- MAIN VALVE MCU PINS --------------------------------*/

/* LOX Encoder */
GPIO_InitStruct.Pin  = LOX_ENC_A_PIN | LOX_ENC_B_PIN;
GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
GPIO_InitStruct.Pull = GPIO_NOPULL;
HAL_GPIO_Init( LOX_ENC_GPIO_PORT, &GPIO_InitStruct );

/* Fuel Encoder */
GPIO_InitStruct.Pin  = KER_ENC_A_PIN;
GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
GPIO_InitStruct.Pull = GPIO_NOPULL;
HAL_GPIO_Init( GPIOC, &GPIO_InitStruct );
GPIO_InitStruct.Pin  = KER_ENC_B_PIN;
GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
GPIO_InitStruct.Pull = GPIO_NOPULL;
HAL_GPIO_Init( GPIOD, &GPIO_InitStruct );

/* EXTI Init */
HAL_NVIC_SetPriority( EXTI9_5_IRQn,   0, 0 );
HAL_NVIC_EnableIRQ  ( EXTI9_5_IRQn         );
HAL_NVIC_SetPriority( EXTI15_10_IRQn, 0, 0 );
HAL_NVIC_EnableIRQ  ( EXTI15_10_IRQn       );

/* Enable and direction pins */
GPIO_InitStruct.Pin  = LOX_EN_PIN | KER_EN_PIN | LOX_DIR_PIN;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
HAL_GPIO_Init( LOX_EN_GPIO_PORT, &GPIO_InitStruct );
GPIO_InitStruct.Pin  = KER_DIR_PIN;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
HAL_GPIO_Init( KER_DIR_GPIO_PORT, &GPIO_InitStruct );

} /* GPIO_Init */


/*******************************************************************************
* END OF FILE                                                                  *
*******************************************************************************/
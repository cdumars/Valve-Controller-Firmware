/*******************************************************************************
*                                                                              *
* FILE:                                                                        *
*       stm32h7xx_hal_msp.c                                                    *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Contains implementation of MSP initialization and de-initialization    *
*                routines                                                      *
*                                                                              *
*******************************************************************************/

/*------------------------------------------------------------------------------
 Standard Includes                                                              
------------------------------------------------------------------------------*/
#include "main.h"

/*------------------------------------------------------------------------------
 Function Prototypes 
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 Procedures 
------------------------------------------------------------------------------*/

/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
*       HAL_MspInit                                                            *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Initializes the Global MSP                                             *
*                                                                              *
*******************************************************************************/
void HAL_MspInit
    (
    void
    )
{
__HAL_RCC_SYSCFG_CLK_ENABLE();
} /* HAL_MspInit */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
*       HAL_UART_MspInit                                                       *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Initializes the UART MSP                                               *
*                                                                              *
*******************************************************************************/
void HAL_UART_MspInit
    (
    UART_HandleTypeDef* huart
    )
{
/* Initialization Structs */
GPIO_InitTypeDef         GPIO_InitStruct     = {0};
RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

/* USB UART Initialization */
if( huart->Instance == USART1 )
    {
    /* Initializes the peripherals clock */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
    PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
    if ( HAL_RCCEx_PeriphCLKConfig( &PeriphClkInitStruct ) != HAL_OK )
        {
        Error_Handler();
        }

    /* Peripheral clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* USART1 GPIO Configuration
      PA9     ------> USART1_TX
      PA10     ------> USART1_RX */
    GPIO_InitStruct.Pin       = GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init( GPIOA, &GPIO_InitStruct );
    }
} /* HAL_UART_MspInit */
 

/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
*       HAL_UART_MspDeInit                                                     *
*                                                                              *
* DESCRIPTION:                                                                 *
*       De-Initializes the UART MSP                                            *
*                                                                              *
*******************************************************************************/
void HAL_UART_MspDeInit
    (
    UART_HandleTypeDef* huart
    )
{
/* USB UART De-initialization */
if( huart->Instance == USART1 )
    {
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /* USART1 GPIO Configuration
       PA9     ------> USART1_TX
       PA10     ------> USART1_RX */
    HAL_GPIO_DeInit( GPIOA, GPIO_PIN_9 | GPIO_PIN_10 );
    }
} /* HAL_UART_MspDeInit */


/*******************************************************************************
* END OF FILE                                                                  *
*******************************************************************************/
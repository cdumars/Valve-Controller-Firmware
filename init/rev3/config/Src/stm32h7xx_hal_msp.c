/*******************************************************************************
*                                                                              *
* FILE:                                                                        *
* 		stm32h7xx_hal_msp.c                                                    *
*                                                                              *
* DESCRIPTION:                                                                 *
* 		Contains code for the MSP Initialization and de-Initialization codes.  *
*                                                                              *
*******************************************************************************/

/*------------------------------------------------------------------------------
 Standard Includes                                                              
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 Project Includes                                                               
------------------------------------------------------------------------------*/
#include "main.h"


/*------------------------------------------------------------------------------
 Procedures 
------------------------------------------------------------------------------*/


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
* 		HAL_MspInit                                                            *
*                                                                              *
* DESCRIPTION:                                                                 *
*     Initializes the Global MSP.                                              *
*                                                                              *
*******************************************************************************/
void HAL_MspInit
    (
    void
    )
{
/* Enable RCC clock source */
__HAL_RCC_SYSCFG_CLK_ENABLE();
} /* HAL_MspInit */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
* 		HAL_UART_MspInit                                                       *
*                                                                              *
* DESCRIPTION:                                                                 *
*     Initializes the UART MSP.                                                *
*                                                                              *
*******************************************************************************/
void HAL_UART_MspInit
    (
    UART_HandleTypeDef* huart
    )
{
/* Initialization Structs */
GPIO_InitTypeDef         GPIO_InitStruct = {0};
RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

/* USB UART Initialization */
if( huart->Instance == USART1 )
    {
    /* Initializes the peripherals clock */
    PeriphClkInitStruct.PeriphClockSelection  = RCC_PERIPHCLK_USART1;
    PeriphClkInitStruct.PLL2.PLL2M            = 32;
    PeriphClkInitStruct.PLL2.PLL2N            = 80;
    PeriphClkInitStruct.PLL2.PLL2P            = 2;
    PeriphClkInitStruct.PLL2.PLL2Q            = 4;
    PeriphClkInitStruct.PLL2.PLL2R            = 2;
    PeriphClkInitStruct.PLL2.PLL2RGE          = RCC_PLL2VCIRANGE_1;
    PeriphClkInitStruct.PLL2.PLL2VCOSEL       = RCC_PLL2VCOMEDIUM;
    PeriphClkInitStruct.PLL2.PLL2FRACN        = 0;
    PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_PLL2;
    if ( HAL_RCCEx_PeriphCLKConfig( &PeriphClkInitStruct ) != HAL_OK )
        {
        Error_Handler();
        }

    /* Peripheral clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /* USART1 GPIO Configuration
    PB14     ------> USART1_TX
    PB15     ------> USART1_RX */
    GPIO_InitStruct.Pin       = GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF4_USART1;
    HAL_GPIO_Init( GPIOB, &GPIO_InitStruct );
    } /*  if ( huart->Instance == USART1 ) */

/* Engine Controller UART Initialization */
else if( huart->Instance == USART3 )
    {
    /* Initializes the peripherals clock */
    PeriphClkInitStruct.PeriphClockSelection      = RCC_PERIPHCLK_USART3;
    PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
    if ( HAL_RCCEx_PeriphCLKConfig( &PeriphClkInitStruct ) != HAL_OK )
        {
        Error_Handler();
        }

    /* Peripheral clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    /* USART3 GPIO Configuration
    PC10     ------> USART3_TX
    PC11     ------> USART3_RX */
    GPIO_InitStruct.Pin       = GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init( GPIOC, &GPIO_InitStruct );
    }
} /* HAL_UART_MspInit */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
* 		HAL_UART_MspDeInit                                                     *
*                                                                              *
* DESCRIPTION:                                                                 *
*     De-Initializes the UART MSP.                                             *
*                                                                              *
*******************************************************************************/
void HAL_UART_MspDeInit
    (
    UART_HandleTypeDef* huart
    )
{

/* USB UART Interface */
if( huart->Instance == USART1 )
    {
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /* USART1 GPIO Configuration
    PB14     ------> USART1_TX
    PB15     ------> USART1_RX */
    HAL_GPIO_DeInit( GPIOB, GPIO_PIN_14 | GPIO_PIN_15 );
    }

/* Engine Controller UART Interface */
else if( huart->Instance == USART3 )
    {
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /* USART3 GPIO Configuration
    PC10     ------> USART3_TX
    PC11     ------> USART3_RX */
    HAL_GPIO_DeInit( GPIOC, GPIO_PIN_10 | GPIO_PIN_11 );
    }
} /* HAL_UART_MspDeInit */


/*******************************************************************************
* END OF FILE                                                                  *
*******************************************************************************/
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
 Project Includes
------------------------------------------------------------------------------*/

/* Application Layer */
#include "sdr_pin_defines_L0005.h"
#include "main.h"
#include "init.h"

/*  Module Layer */
#include "commands.h"
#include "solenoid.h"
#include "usb.h"


/*------------------------------------------------------------------------------
 Global Variables
------------------------------------------------------------------------------*/
UART_HandleTypeDef huart4; /* UART to engine controller/usb */


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
uint8_t    command;        /* SDEC command code    */
uint8_t    subcommand;     /* SDEC subcommand code */
USB_STATUS usb_status;     /* UART/USB status      */


/*------------------------------------------------------------------------------
 Initializations 
------------------------------------------------------------------------------*/
usb_status = USB_OK;


/*------------------------------------------------------------------------------
 MCU Initialization
------------------------------------------------------------------------------*/
HAL_Init();           /* CMSIS HAL    */
SystemClock_Config(); /* System clock */
GPIO_Init();          /* GPIO         */
USB_UART_Init();      /* USB UART     */


/*------------------------------------------------------------------------------
 Event Loop
------------------------------------------------------------------------------*/
while (1)
	{
	/* Read data from UART reciever */
	usb_status = usb_receive( &command, sizeof( command ), HAL_DEFAULT_TIMEOUT );

	/* Parse command input if HAL_UART_Receive doesn't timeout */
	if ( usb_status == USB_OK )
		{
		switch( command )
			{
			/* Ping Command -----------------------------------------------------*/
			case PING_OP:
				ping();
				break;

			/* Connect Command --------------------------------------------------*/
			case CONNECT_OP:
				ping();
				break;

			/* Solenoid Command -------------------------------------------------*/
			case SOL_OP:
				usb_status = usb_receive( &subcommand, 
				                          sizeof( subcommand ), 
										  HAL_DEFAULT_TIMEOUT );
				if ( usb_status == USB_OK )
					{
					solenoid_cmd_execute( subcommand );
					}
				else
					{
					/* Do nothing */
					Error_Handler();
					}
				break;

			default:
				{
				/* Unrecognized command code */
				Error_Handler();
				break;
				}
			}
		}
	else /* USB connection times out */
		{
		/* Do nothing */
		}
	}
} /* main */


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  __disable_irq();
  HAL_GPIO_WritePin(EXCEPT_GPIO_PORT, EXCEPT_PIN, GPIO_PIN_SET);
  while (1)
	{
	/* Application hangs */
	}
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


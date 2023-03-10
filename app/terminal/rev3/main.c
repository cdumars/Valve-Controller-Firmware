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

/* Module Layer */
#include "commands.h"
#include "led.h"
#include "solenoid.h"
#include "sensor.h"
#include "usb.h"
#include "valve.h"


/*------------------------------------------------------------------------------
 Global Variables
------------------------------------------------------------------------------*/
//TIM_HandleTypeDef  htim15; /* Valve control PWM signals     */
UART_HandleTypeDef huart1; /* UART to USB               */
UART_HandleTypeDef huart3; /* UART to engine controller */


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
uint8_t       command;        /* SDEC command code          */
uint8_t       subcommand;     /* SDEC subcommand code       */
USB_STATUS    usb_status;     /* UART/USB status            */
SENSOR_STATUS sensor_status;  /* Sensor module return codes */


/*------------------------------------------------------------------------------
 Initializations 
------------------------------------------------------------------------------*/
usb_status    = USB_OK;
sensor_status = SENSOR_OK;


/*------------------------------------------------------------------------------
 MCU Initialization
------------------------------------------------------------------------------*/
HAL_Init          ();   /* CMSIS HAL              */
SystemClock_Config();   /* System clock           */
GPIO_Init         ();   /* GPIO                   */
USB_UART_Init     ();   /* USB UART               */
Valve_UART_Init   ();   /* Engine Controller UART */
//Valve_TIM_Init    ();   /* Valve control timers */


/*------------------------------------------------------------------------------
 External Hardware initializations 
------------------------------------------------------------------------------*/

/* Sensor module */
sensor_init();


/*------------------------------------------------------------------------------
 Event Loop
------------------------------------------------------------------------------*/
while (1)
	{
	if ( usb_detect() )
		{
		/* Read data from UART reciever */
		usb_status = usb_receive( &command         , 
		                          sizeof( command ), 
								  HAL_DEFAULT_TIMEOUT );

		/* Parse command input if HAL_UART_Receive doesn't timeout */
		if ( usb_status == USB_OK )
			{
			switch( command )
				{
				/* Ping Command -------------------------------------------------*/
				case PING_OP:
					{
					ping();
					break;
					} /* PING_OP */

				/* Connect Command ----------------------------------------------*/
				case CONNECT_OP:
					{
					ping();
					break;
					} /* CONNECT_OP */

				/* Solenoid Command ---------------------------------------------*/
				case SOL_OP:
					{
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
					} /* SOL_OP */

				/* Sensor Command -----------------------------------------------*/
				case SENSOR_OP:
					{
					usb_status = usb_receive( &subcommand, 
											sizeof( subcommand ),
											HAL_DEFAULT_TIMEOUT );
					if ( usb_status == USB_OK )
						{
						sensor_status = sensor_cmd_execute( subcommand );
						if ( sensor_status != SENSOR_OK )
							{
							Error_Handler();
							}
						}
					else
						{
						Error_Handler();
						}
					break;
					} /* SENSOR_OP */

				/* Unrecognized Command -----------------------------------------*/
				default:
					{
					/* Unrecognized command code */
					Error_Handler();
					break;
					}
				} /* switch( command ) */
			} /* if ( usb_status == USB_OK )*/
		else /* USB connection times out */
			{
			/* Do nothing */
			}
		} /* if ( usb_detect() )*/
	}
} /* main */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
* 		Error_Handler                                                          *
*                                                                              *
* DESCRIPTION:                                                                 *
* 		Handles software errors by turing the status LED red                   *
*                                                                              *
*******************************************************************************/
void Error_Handler(void)
{
  __disable_irq();
  led_error_assert();
  while (1)
	{
	/* Application hangs */
	}
} /* Error_Handler */


/*******************************************************************************
* END OF FILE                                                                  *
*******************************************************************************/
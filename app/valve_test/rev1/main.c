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
TIM_HandleTypeDef  htim2;  /* Fuel main valve control PWM signals */
TIM_HandleTypeDef  htim15; /* LOX main valve control PWM signals  */
UART_HandleTypeDef huart1; /* UART to USB                         */
UART_HandleTypeDef huart3; /* UART to engine controller           */


/*------------------------------------------------------------------------------
 Application entry point
------------------------------------------------------------------------------*/
int main
	(
	void
	)
{


/*------------------------------------------------------------------------------
 MCU Initialization
------------------------------------------------------------------------------*/
HAL_Init           ();   /* CMSIS HAL               */
SystemClock_Config ();   /* System clock            */
GPIO_Init          ();   /* GPIO                    */
USB_UART_Init      ();   /* USB UART                */
Valve_UART_Init    ();   /* Engine Controller UART  */
LOX_Valve_TIM_Init ();   /* LOX Valve control timer */
Fuel_Valve_TIM_Init();   /* Fuel Valve control timer */


/*------------------------------------------------------------------------------
 External Hardware initializations
------------------------------------------------------------------------------*/

/* Sensor module */
sensor_init();

/* Indicate successful initialization with green status LED */
led_set_color( LED_GREEN );


/*------------------------------------------------------------------------------
 Event Loop
------------------------------------------------------------------------------*/
while (1)
	{
		SOL_STATE state;
		
	   for (int i = 0; i < 6; ++i)
		{
			solenoid_toggle(i+1);
		}
		
		state = solenoid_get_state();

		if (state == SOL_ALL_ON)
		{
			led_set_color( LED_BLUE );
		}

		HAL_Delay(2000);
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

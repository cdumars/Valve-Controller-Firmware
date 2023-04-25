/*******************************************************************************
*
* FILE: 
* 		main.h
*
* DESCRIPTION: 
* 		Processes commands recieved from a host PC, provides fine control over 
*       valve controller hardware resources
*
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------
 Includes                                                                     
------------------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"


/*------------------------------------------------------------------------------
 Macros  
------------------------------------------------------------------------------*/

/* General MCU HAL related macros */
#define DEF_BUFFER_SIZE            ( 16  ) /* Default size of buffer arrays   */

/* Timeouts */
#ifndef SDR_DEBUG
	#define HAL_DEFAULT_TIMEOUT    ( 10  ) /* Default timeout for polling 
											   operations                     */
#else
	/* Disable timeouts when debugging */
	#define HAL_DEFAULT_TIMEOUT    ( 0xFFFFFFFF )  
#endif /* SDR_DEBUG */


/*------------------------------------------------------------------------------
 Typdefs 
------------------------------------------------------------------------------*/

/* Serial interface source for receiving command data */
typedef enum _CMD_SOURCE
	{
	CMD_SOURCE_USB,
	CMD_SOURCE_VALVE
	} CMD_SOURCE;

/*------------------------------------------------------------------------------
 Function prototypes                                                          
------------------------------------------------------------------------------*/
void Error_Handler      ( void                    );
void HAL_TIM_MspPostInit( TIM_HandleTypeDef *htim );

/* Processes commands from the SDEC terminal */
void command_handler
	(
	uint8_t    command,     /* sdec command                              */
	CMD_SOURCE cmd_source   /* Determines which serial interface is used */
	);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

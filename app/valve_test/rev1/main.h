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
	#define HAL_DEFAULT_TIMEOUT    ( 1  ) /* Default timeout for polling 
											   operations                     */
#else
	/* Disable timeouts when debugging */
	#define HAL_DEFAULT_TIMEOUT    ( 0xFFFFFFFF )  
#endif /* SDR_DEBUG */

/* State with all solenoids turned on */
#define SOL_ALL_ON ( 0b00111111 )



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


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

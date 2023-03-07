/*******************************************************************************
*                                                                              *
* FILE:                                                                        *
* 		init.h                                                                 *
*                                                                              *
* DESCRIPTION:                                                                 *
* 		Contains initialization routines for MCU core and peripherals          *
*                                                                              *
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INIT_H 
#define INIT_H

#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------------------------------------------
 Standard Includes                                                              
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 Project Includes                                                               
------------------------------------------------------------------------------*/
#include "main.h"


/*------------------------------------------------------------------------------
 Function prototypes                                                          
------------------------------------------------------------------------------*/
void SystemClock_Config( void ); /* Clock configuration  */
void GPIO_Init         ( void ); /* GPIO Initialization  */
void Valve_TIM_Init    ( void ); /* Valve control timers */
void USB_UART_Init     ( void ); /* UART Initialization  */


#ifdef __cplusplus
}
#endif
#endif /* INIT_H */


/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/
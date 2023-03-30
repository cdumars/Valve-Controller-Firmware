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

/* HAL Init */
void HAL_TIM_MspPostInit( TIM_HandleTypeDef *htim );

/* MCU Initialization Functions */
void SystemClock_Config ( void ); /* Clock configuration                      */
void GPIO_Init          ( void ); /* GPIO Initialization                      */
void Fuel_Valve_TIM_Init( void ); /* Main fuel valve control timer            */
void LOX_Valve_TIM_Init ( void ); /* Main OX valve control timer              */
void USB_UART_Init      ( void ); /* USB UART Initialization                  */
void Valve_UART_Init    ( void ); /* Engine Controller UART Initialization    */


#ifdef __cplusplus
}
#endif
#endif /* INIT_H */


/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/
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
 MCU Pin Assignments                                                                     
------------------------------------------------------------------------------*/
#define STATUS GPIO_PIN_15
#define EXCEPT GPIO_PIN_13


/*------------------------------------------------------------------------------
 Function prototypes                                                          
------------------------------------------------------------------------------*/
void Error_Handler(void);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/*******************************************************************************
*
* FILE: 
* 		solenoid.c
*
* DESCRIPTION: 
* 		Basic solenoid actuation API
*
*******************************************************************************/


/*------------------------------------------------------------------------------
 Includes                                                                     
------------------------------------------------------------------------------*/
#include "main.h"
#include "solenoid.h"
#include "stm32h7xx_hal.h"


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		solenoid_cmd_execute                                                   *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Executes a solenoid function based on a subcommand code from a PC      * 
*                                                                              *
*******************************************************************************/
void solenoid_cmd_execute
	(
	uint8_t solenoid_cmd_opcode  /* Solenoid actuation code */
	); /* solenoid_cmd_execute */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		solenoid_on                                                            *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		 Applies power to a specified solenoid                                 * 
*                                                                              *
*******************************************************************************/
void solenoid_on
	(
	uint8_t solenoid_num  /* Solenoid number to actuate */
	); /* solenoid_on */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		solenoid_off                                                           *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		 Removes power from a specified solenoid                               * 
*                                                                              *
*******************************************************************************/
void solenoid_off
	(
	uint8_t solenoid_num  /* Solenoid number to actuate */
	); /* solenoid_off */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		solenoid_toggle                                                        *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		 Toggles the actuation state of a specified solenoid                   * 
*                                                                              *
*******************************************************************************/
void solenoid_toggle
	(
	uint8_t solenoid_num  /* Solenoid number to actuate */
	); /* solenoid_toggle */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		solenoid_reset                                                         *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		 Resets all solenoids to their default state                           * 
*                                                                              *
*******************************************************************************/
void solenoid_reset
	(
	void
	); /* solenoid_reset */


/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/

/*******************************************************************************
*
* FILE: 
* 		solenoid.h
*
* DESCRIPTION: 
* 		Basic solenoid actuation API
*
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SOLENOID_H
#define SOLENOID_H

#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------------------------------------------
 Macros 
------------------------------------------------------------------------------*/
#define SOL_OP     0x51 /* solenoid command line opcode */

/* Microcontroller Pin Assignments */
#define SOL1_PIN   GPIO_PIN_2
#define SOL2_PIN   GPIO_PIN_3
#define SOL3_PIN   GPIO_PIN_4
#define SOL4_PIN   GPIO_PIN_0
#define SOL5_PIN   GPIO_PIN_1
#define SOL6_PIN   GPIO_PIN_2


/*------------------------------------------------------------------------------
 Function Prototypes 
------------------------------------------------------------------------------*/
void solenoid_cmd_execute
	(
	uint8_t solenoid_cmd_opcode  /* Solenoid actuation code */
	); /* solenoid_cmd_execute */

void solenoid_on
	(
	uint8_t solenoid_num  /* Solenoid number to actuate */
	); /* solenoid_on */

void solenoid_off
	(
	uint8_t solenoid_num  /* Solenoid number to actuate */
	); /* solenoid_off */

void solenoid_toggle
	(
	uint8_t solenoid_num  /* Solenoid number to actuate */
	); /* solenoid_toggle */

void solenoid_reset
	(
	void
	); /* solenoid_reset */

#endif /* SOLENOID_H */

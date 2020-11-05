/*
 * Timer0_Configure.h
 *
 *  Created on: Sep 30, 2020
 *      Author: Omar Fahmy
 */

#ifndef MCAL_TIMER0_TIMER0_CONFIGURE_H_
#define MCAL_TIMER0_TIMER0_CONFIGURE_H_

/*****************************************************************************/
/*      					 OPTIONS FOR TIMER MODE:			             */
/*       			NORMAL - PHASE_CORRECT - CTC - FAST_PWM				     */
/*****************************************************************************/
#define MODE						FAST_PWM
/*****************************************************************************/


/*****************************************************************************/
/* OPTIONS FOR OUTPUT COMPARE PIN (OC0) BEHAVIOUR IN CASE OF NON-PWM MODE:   */
/*       		DISCONNECT_OC0 - TOGGLE_OC0 - CLEAR_OC0 - SET_OC0		     */
/*****************************************************************************/
#define OC0_NON_PWM					TOGGLE_OC0
/*****************************************************************************/


/*****************************************************************************/
/* OPTIONS FOR OUTPUT COMPARE PIN (OC0) BEHAVIOUR IN CASE OF FAST PWM MODE:  */
/*       		DISCONNECT_OC0 - NON_INVERTING_OC0 - INVERTING_OC0		     */
/*****************************************************************************/
#define OC0_FAST_PWM			NON_INVERTING_OC0
/*****************************************************************************/


/*****************************************************************************/
/* OPTIONS FOR OUTPUT COMPARE PIN (OC0) BEHAVIOUR IN CASE OF PHASE CORRECT	 */
/* 									MODE:									 */
/*       		DISCONNECT_OC0 - NON_INVERTING_OC0 - INVERTING_OC0		     */
/*****************************************************************************/
#define OC0_PHASE_CORRECT		NON_INVERTING_OC0
/*****************************************************************************/


/*****************************************************************************/
/* 							OPTIONS FOR CLOCK SELECT	 					 */
/*        NO_CLOCK_SOURCE - NO_PRESCALER - PRESCALER_8 - PRESCALER_64	     */
/*	       PRESCALER_256 - PRESCALER_1024 - EXTERNAL_T0_FALLING_EDGE		 */
/* 							EXTERNAL_T0_RISING_EDGE 						 */
/*****************************************************************************/
#define CLOCK_SELECT			PRESCALER_1024
/*****************************************************************************/


#endif /* MCAL_TIMER0_TIMER0_CONFIGURE_H_ */

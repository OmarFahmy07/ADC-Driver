/*
 * ADC_Configure.h
 *
 *  Created on: Sep 22, 2020
 *      Author: Omar Fahmy
 */

#ifndef MCAL_ADC_CONFIGURE_H_
#define MCAL_ADC_CONFIGURE_H_

/*****************************************************************************/
/*      				OPTIONS FOR ADC VOLTAGE REFERENCE:		             */
/*       				  AREF	-	AVCC	- INTERNAL					     */
/*****************************************************************************/
#define VOLTAGE_REFERENCE			AVCC
/*****************************************************************************/


/*****************************************************************************/
/*       				OPTIONS FOR DATA ADJUSTMENT:			             */
/*       			 LEFT_ADJUSTMENT - RIGHT_ADJUSTMENT					     */
/*****************************************************************************/
#define DATA_ADJUSTMENT				RIGHT_ADJUSTMENT
/*****************************************************************************/


/*****************************************************************************/
/*       				OPTIONS FOR ADC MODE:					             */
/*       		   SINGLE_CONVERSION - AUTO_TRIGGERING					     */
/*****************************************************************************/
#define MODE						AUTO_TRIGGERING
/*****************************************************************************/


/*****************************************************************************/
/*    OPTIONS FOR AUTO TRIGGERING SOURCE (IN CASE OF AUTO TRIGGERING MODE):  */
/*       		FREE_RUNNING - ANALOG_COMPARATOR - EXTERNAL_INTERRUPT0		 */
/* 				TIMER_COUNTER0_COMPARE_MATCH - TIMER_COUNTER0_OVERFLOW		 */
/* 				TIMER_COUNTER_COMPARE_MATCH_B - TIMER_COUNTER1_OVERFLOW		 */
/* 						  TIMER_COUNTER1_CAPTURE_EVENT	   	 				 */
/*****************************************************************************/
#define AUTO_TRIGGERING_SOURCE		FREE_RUNNING
/*****************************************************************************/


/*****************************************************************************/
/*    				  OPTIONS FOR ADC PRESCALER CONFIGURATION:				 */
/* 					 DIVISION_FACTOR_2 	 - 	 DIVISION_FACTOR_4				 */
/* 					 DIVISION_FACTOR_8 	 - 	 DIVISION_FACTOR_16				 */
/* 		     		 DIVISION_FACTOR_32  - 	 DIVISION_FACTOR_64				 */
/* 								DIVISION_FACTOR_128							 */
/*****************************************************************************/
#define PRESCALER					DIVISION_FACTOR_64
/*****************************************************************************/


#endif /* MCAL_ADC_CONFIGURE_H_ */

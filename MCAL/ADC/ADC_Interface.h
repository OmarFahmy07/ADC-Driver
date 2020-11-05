/*
 * ADC_Interface.h
 *
 *  Created on: Sep 22, 2020
 *      Author: Omar Fahmy
 */

#ifndef MCAL_ADC_INTERFACE_H_
#define MCAL_ADC_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"


/************************************************************************************/
/*					  USEFUL MACROS AS FUNCTIONS' ARGUMENTS						    */
/************************************************************************************/

/************************************************************************************/
/*								ADC CHANNELS									    */
/************************************************************************************/
#define ADC_CHANNEL0	0
#define ADC_CHANNEL1	1
#define ADC_CHANNEL2	2
#define ADC_CHANNEL3	3
#define ADC_CHANNEL4	4
#define ADC_CHANNEL5	5
#define ADC_CHANNEL6	6
#define ADC_CHANNEL7	7
/************************************************************************************/


/************************************************************************************/
/*							 FUNCTIONS PROTOTYPES								    */
/************************************************************************************/

/************************************************************************************/
/* Description: initializes ADC's voltage reference, adjustment, mode, auto	        */
/* triggering source (in case of using auto triggering mode), and prescaler. 		*/
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 ADC_U8Init(void);
/************************************************************************************/

/************************************************************************************/
/* Description: enables the ADC's peripheral	  								    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 ADC_U8EnableADC(void);
/************************************************************************************/

/************************************************************************************/
/* Description: disables the ADC's peripheral	  								    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 ADC_U8DisableADC(void);
/************************************************************************************/

/************************************************************************************/
/* Description: enables the ADC's interrupt		  								    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 ADC_U8EnableInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: disables the ADC's interrupt	  								    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 ADC_U8DisableInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: selects a specific ADC channel	  								    */
/* Inputs: channel number  															*/
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 ADC_U8SelectChannel(const u8 LOC_U8Channel);
/************************************************************************************/

/************************************************************************************/
/* Description: starts converting analog value to digital value					    */
/* Inputs: nothing		  															*/
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 ADC_U8StartConversion(void);
/************************************************************************************/

/************************************************************************************/
/* Description: polls on the ADC flag					    						*/
/* Inputs: nothing		  															*/
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 ADC_U8PollingOnFlag(void);
/************************************************************************************/

/************************************************************************************/
/* Description: reads the value after being converted to a digital value with a		*/
/* 10-bit resolution																*/
/* Inputs: pointer to a function to receive the value in							*/
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 ADC_U8Read10BitDigitalValue(u16* const LOC_U16Value);
/************************************************************************************/

/************************************************************************************/
/* Description: reads the value after being converted to a digital value with an	*/
/* 8-bit resolution 																*/
/* Inputs: pointer to a function to receive the value in							*/
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 ADC_U8Read8BitDigitalValue(u16* const LOC_U16Value);
/************************************************************************************/

/***********************************************************************************/
/* Description: takes a pointer to a function that is to be executed on		  	   */
/* triggering the ADC interrupt.	  								 			   */
/* Inputs: pointer to a function that takes no arguments and returns no value	   */
/* Output: error checking								  						   */
/***********************************************************************************/
extern u8 ADC_U8SetCallBack( void(*const LOC_VidPtrToFun)(void) );
/***********************************************************************************/


#endif /* MCAL_ADC_INTERFACE_H_ */

/*
 * ADC_Program.c
 *
 *  Created on: Sep 22, 2020
 *      Author: Omar Fahmy
 */


#include "../../HAL/LCD/LCD_Interface.h"
/* 			LIB LAYER 			*/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/COMMON_MACROS.h"
#include "../../LIB/STD_TYPES.h"

/* 			MCAL LAYER 			*/
#include "ADC_Configure.h"
#include "ADC_Private.h"

/* Global Pointer to Function for Calling Back */
void (*GLOB_VidADCPtrCallBack)(void) = NULL;

/***********************************************************************************/
/* 							PUBLIC FUNCTIONS IMPLEMENTATION						   */
/***********************************************************************************/

u8 ADC_U8Init(void)
{
	/* Voltage Reference Configuration */
#if VOLTAGE_REFERENCE == AREF
	CLR_BIT(ADMUX_REGISTER, REFS1);
	CLR_BIT(ADMUX_REGISTER, REFS0);
#elif VOLTAGE_REFERENCE == AVCC
	SET_BIT(ADMUX_REGISTER, REFS0);
	CLR_BIT(ADMUX_REGISTER, REFS1);
#elif VOLTAGE_REFERENCE == INTERNAL
	SET_BIT(ADMUX_REGISTER, REFS0);
	SET_BIT(ADMUX_REGISTER, REFS1);
#else
#error "Incorrect voltage reference configuration"
#endif

	/* Adjustment Configuration */
#if DATA_ADJUSTMENT == RIGHT_ADJUSTMENT
	CLR_BIT(ADMUX_REGISTER, ADLAR);
#elif DATA_ADJUSTMENT == LEFT_ADJUSTMENT
	SET_BIT(ADMUX_REGISTER, ADLAR);
#else
#error "Incorrect adjustment configuration"
#endif

	/* ADC Mode Configuration */
#if MODE == AUTO_TRIGGERING
	SET_BIT(ADCSRA_REGISTER, ADATE);

	/* Auto Triggering Source Configuration */
#if AUTO_TRIGGERING_SOURCE == FREE_RUNNING_MODE
	CLR_BIT(SFIOR_REGISTER, ADTS2);
	CLR_BIT(SFIOR_REGISTER, ADTS1);
	CLR_BIT(SFIOR_REGISTER, ADTS0);
#elif AUTO_TRIGGERING_SOURCE == ANALOG_COMPARATOR
	CLR_BIT(SFIOR_REGISTER, ADTS2);
	CLR_BIT(SFIOR_REGISTER, ADTS1);
	SET_BIT(SFIOR_REGISTER, ADTS0);
#elif AUTO_TRIGGERING_SOURCE == EXTERNAL_INTERRUPT0
	CLR_BIT(SFIOR_REGISTER, ADTS2);
	SET_BIT(SFIOR_REGISTER, ADTS1);
	CLR_BIT(SFIOR_REGISTER, ADTS0);
#elif AUTO_TRIGGERING_SOURCE == TIMER_COUNTER0_COMPARE_MATCH
	CLR_BIT(SFIOR_REGISTER, ADTS2);
	SET_BIT(SFIOR_REGISTER, ADTS1);
	SET_BIT(SFIOR_REGISTER, ADTS0);
#elif AUTO_TRIGGERING_SOURCE == TIMER_COUNTER0_OVERFLOW
	SET_BIT(SFIOR_REGISTER, ADTS2);
	CLR_BIT(SFIOR_REGISTER, ADTS1);
	CLR_BIT(SFIOR_REGISTER, ADTS0);
#elif AUTO_TRIGGERING_SOURCE == TIMER_COUNTER_COMPARE_MATCH_B
	SET_BIT(SFIOR_REGISTER, ADTS2);
	CLR_BIT(SFIOR_REGISTER, ADTS1);
	SET_BIT(SFIOR_REGISTER, ADTS0);
#elif AUTO_TRIGGERING_SOURCE == TIMER_COUNTER1_OVERFLOW
	SET_BIT(SFIOR_REGISTER, ADTS2);
	SET_BIT(SFIOR_REGISTER, ADTS1);
	CLR_BIT(SFIOR_REGISTER, ADTS0);
#elif AUTO_TRIGGERING_SOURCE == TIMER_COUNTER1_CAPTURE_EVENT
	SET_BIT(SFIOR_REGISTER, ADTS2);
	SET_BIT(SFIOR_REGISTER, ADTS1);
	SET_BIT(SFIOR_REGISTER, ADTS0);
#else
#error "Incorrect auto triggering source"
#endif

#elif MODE == SINGLE_CONVERSION
	CLR_BIT(ADCSRA_REGISTER, ADATE);
#else
#error "Incorrect mode configuration"
#endif

	/* For ensuring compatibility with future devices */
	//CLR_BIT(SFIOR_REGISTER, BIT4);

	/* ADC Prescaler Configuration */
#if PRESCALER == DIVISION_FACTOR_2
	CLR_BIT(ADCSRA_REGISTER, ADPS2);
	CLR_BIT(ADCSRA_REGISTER, ADPS1);
	CLR_BIT(ADCSRA_REGISTER, ADPS0);
#elif PRESCALER == DIVISION_FACTOR_4
	CLR_BIT(ADCSRA_REGISTER, ADPS2);
	SET_BIT(ADCSRA_REGISTER, ADPS1);
	CLR_BIT(ADCSRA_REGISTER, ADPS0);
#elif PRESCALER == DIVISION_FACTOR_8
	CLR_BIT(ADCSRA_REGISTER, ADPS2);
	SET_BIT(ADCSRA_REGISTER, ADPS1);
	SET_BIT(ADCSRA_REGISTER, ADPS0);
#elif PRESCALER == DIVISION_FACTOR_16
	SET_BIT(ADCSRA_REGISTER, ADPS2);
	CLR_BIT(ADCSRA_REGISTER, ADPS1);
	CLR_BIT(ADCSRA_REGISTER, ADPS0);
#elif PRESCALER == DIVISION_FACTOR_32
	SET_BIT(ADCSRA_REGISTER, ADPS2);
	CLR_BIT(ADCSRA_REGISTER, ADPS1);
	SET_BIT(ADCSRA_REGISTER, ADPS0);
#elif PRESCALER == DIVISION_FACTOR_64
	SET_BIT(ADCSRA_REGISTER, ADPS2);
	SET_BIT(ADCSRA_REGISTER, ADPS1);
	CLR_BIT(ADCSRA_REGISTER, ADPS0);
#elif PRESCALER == DIVISION_FACTOR_128
	SET_BIT(ADCSRA_REGISTER, ADPS2);
	SET_BIT(ADCSRA_REGISTER, ADPS1);
	SET_BIT(ADCSRA_REGISTER, ADPS0);
#error "Incorrect ADC prescaler selection"
#endif

	return NO_ERROR;
}

u8 ADC_U8EnableADC(void)
{
	SET_BIT(ADCSRA_REGISTER, ADEN);
	return NO_ERROR;
}

u8 ADC_U8DisableADC(void)
{
	CLR_BIT(ADCSRA_REGISTER, ADEN);
	return NO_ERROR;
}

u8 ADC_U8EnableInterrupt(void)
{
	SET_BIT(ADCSRA_REGISTER, ADIE);
	return NO_ERROR;
}

u8 ADC_U8DisableInterrupt(void)
{
	CLR_BIT(ADCSRA_REGISTER, ADIE);
	return NO_ERROR;
}

u8 ADC_U8SelectChannel(const u8 LOC_U8Channel)
{
	if (LOC_U8Channel < NUMBER_OF_CHANNELS)
	{
		/* Clear the Older Channel */
		CLEAR_CHANNELS;
		/* Select Channel */
		ADMUX_REGISTER |= LOC_U8Channel;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 ADC_U8StartConversion(void)
{
	/* Start Conversion */
	SET_BIT(ADCSRA_REGISTER, ADSC);
	return NO_ERROR;
}

u8 ADC_U8PollingOnFlag(void)
{
	/* Conversion in progress, block the system till completion */
	while ( !GET_BIT(ADCSRA_REGISTER, ADIF) );
	/* Clear Flag After Conversion */
	SET_BIT(ADCSRA_REGISTER, ADIF);
	return NO_ERROR;
}

u8 ADC_U8Read10BitDigitalValue(u16* const LOC_U16Value)
{
	if (LOC_U16Value != NULL)
	{
		/* Read Value After Conversion */
		*LOC_U16Value = ADC_REGISTER;
#if DATA_ADJUSTMENT == RIGHT_ADJUSTMENT
		/* Nothing to be done - data is ready */
#elif DATA_ADJUSTMENT == LEFT_ADJUSTMENT
		*LOC_U16Value >>= SIX_BITS;
#else
#error "Incorrect data adjustment configuration"
#endif
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 ADC_U8Read8BitDigitalValue(u8* const LOC_U8Value)
{
	if (LOC_U8Value != NULL)
	{
#if DATA_ADJUSTMENT == RIGHT_ADJUSTMENT
		*LOC_U8Value = ADCH_REGISTER;
		*LOC_U8Value <<= SIX_BITS;
		*LOC_U8Value |= ADCL_REGISTER >> TWO_BITS;
#elif DATA_ADJUSTMENT == LEFT_ADJUSTMENT
		*LOC_U8Value = ADCH_REGISTER;
#else
#error "Incorrect data adjustment configuration"
#endif
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 ADC_U8SetCallBack( void(*const LOC_VidPtrToFun)(void) )
{
	if ( LOC_VidPtrToFun != NULL )
	{
		GLOB_VidADCPtrCallBack = LOC_VidPtrToFun;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

/***********************************************************************************/
/* 							PRIVATE FUNCTIONS IMPLEMENTATION					   */
/***********************************************************************************/

void __vector_16(void)
{
	if (GLOB_VidADCPtrCallBack != NULL)
	{
		(*GLOB_VidADCPtrCallBack)();
	}
}

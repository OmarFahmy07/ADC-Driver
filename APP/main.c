/*
 * main.c
 *
 *  Created on: Sep 22, 2020
 *      Author: Omar Fahmy
 */


#include "../MCAL/ADC/ADC_Interface.h"
#include "../MCAL/Global Interrupt/GI_Interface.h"
#include "../MCAL/Timer0/Timer0_Interface.h"
#include "../MCAL/DIO/DIO_Interface.h"

u16 digitalValue;

void getDigitalValue(void);

int main (void)
{
	u8 dutyCycle;
	Timer0_U8Init();
	DIO_U8SetPinDirection(DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT);
	ADC_U8Init();
	ADC_U8EnableADC();
	ADC_U8EnableInterrupt();
	ADC_U8SetCallBack(getDigitalValue);
	ADC_U8SelectChannel(ADC_CHANNEL0);
	GI_VidEnable();
	ADC_U8StartConversion();
	Timer0_U8Start();
	Timer0_U8SetDutyCycle(254);

	while (1)
	{
		dutyCycle = 38 * digitalValue / (f32)1023 + 1;

	}

	return 0;
}

void getDigitalValue(void)
{
	ADC_U8Read10BitDigitalValue(&digitalValue);
}

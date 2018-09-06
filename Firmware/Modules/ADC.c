/*
 * ADC.c
 *
 *  Created on: 2016Äê5ÔÂ17ÈÕ
 *      Author: DBN
 */
#include <msp430.h>
#include <ADC.h>
#include <RGB.h>
#include <GeneralFunctions.h>

// Define input channel
#define IN_CHANNEL INCH_0
#define IN_CHA_BIT BIT0

// Predefined voltage battery voltage level
// HIGH_VOLT - LOW_VOLT must > 0.2
#define HIGH_VOLT 4.0
#define LOW_VOLT 3.3

// State flags
static bool High_First_Enter = yes;
static bool Low_First_Enter = yes;
static bool High_Battery_Power = no;
static bool Low_Battery_Power = no;

// ADC Control:
// Initialize ADC module
void ADC_Init()
{
	P2SEL |= IN_CHA_BIT;
	ADC10CTL0 |= SREF_1 + ADC10SHT_2 + REFON + ADC10ON + ADC10IE; //1.5V Internal Reference
	ADC10CTL1 |= IN_CHANNEL + SHS_0 + ADC10SSEL_3 + ADC10DIV_7;
	ADC10AE0 |= IN_CHA_BIT;
}

// ADC Start Conversion Signal
void Start_ADC_Conversion()
{
	ADC10CTL0 |= ENC + ADC10SC;
}

// Read the ADC result register and convert it into voltage into
// Used when the interrupt is not enabled
float Manual_ReadVolt()
{
	ADC10CTL0 &= ~ADC10IE;
	ADC10CTL0 |= ENC + ADC10SC;
	while (ADC10CTL1 & ADC10BUSY);
	ADC10CTL0 &= ~ADC10IFG;
	ADC10CTL0 |= ADC10IE;
	return (ADC10MEM * 4.5) / 1023;
}

// Read the ADC result and convert to voltage
// Used when in interrupt mode
static float Read_Volt()
{
	return (ADC10MEM * 4.5) / 1023;
}

//Battery Power Level Detection and Control
static void Analyze_Bat_Level(float Volt)
{
	if(Volt < LOW_VOLT)		//Low Power
	{
		//Indicate the Battery Power is Low
		if( Low_First_Enter == yes )
		{
			Low_First_Enter = no;
			Low_Battery_Power = yes;
		}
	}
	else if((LOW_VOLT + 0.1 < Volt)&&(Volt < HIGH_VOLT - 0.1)) //Mid Power
	{
		if((Low_First_Enter == no)||(High_First_Enter == no))
		{
			Low_First_Enter = yes;
			Low_Battery_Power = no;
			High_First_Enter = yes;
			High_Battery_Power = no;
		}
	}
	else if(HIGH_VOLT < Volt)	//High Power
	{
		if( High_First_Enter == yes )
		{
			High_First_Enter = no;
			High_Battery_Power = yes;
		}
	}
}

bool Check_High_Battery_Power()
{
	return High_Battery_Power;
}

bool Check_Low_Battery_Power()
{
	return Low_Battery_Power;
}

void Exit_High_Battery_Power_Mode()
{
	High_Battery_Power = no;
}

void Exit_Low_Battery_Power_Mode()
{
	Low_Battery_Power = no;
}

void Reset_High_Battery_First_Enter_Mark()
{
	High_First_Enter = yes;
}

/*
 * Timer interrupt is used for checking the battery voltage periodically.
 */

// Enable timer interrupt
static void Close_Timer_INT()
{
	TACCTL0 &= ~CCIE;
	TACCTL0 &= ~CCIFG;
}

// Disable timer interrupt
static void Open_Timer_INT()
{
	TACCTL0 |= CCIE;
}

//Interrupt Service Routine
#pragma vector = ADC10_VECTOR
__interrupt void ADC10_ISR()
{
	_EINT();
	Close_Timer_INT();
	float Volt = Read_Volt();
	Analyze_Bat_Level ( Volt );
	Open_Timer_INT();
}






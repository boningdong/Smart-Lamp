/*
 * Timer.c
 *
 *  Created on: 2016Äê5ÔÂ18ÈÕ
 *      Author: DBN
 */
#include <msp430.h>
#include <Timer.h>
#include <RGB.h>
#include <ADC.h>
#include <GeneralFunctions.h>

#define ADC_CONVERT_PERIOD 10
#define POWER_LEVEL_INDICATOR_PERIOD 5

unsigned int Seconds_Counter = 0;
unsigned int Power_Indicator_Counter = 0;

//Timer Control
void Timer_Init()
{
	TACCTL0 |= CCIE;
	TACCR0 = 62500; 				 //Every 1s triger the Interrupt
	TACTL |= TASSEL_2 + MC_3 + ID_3; //Divider: 8  Mode: Up and Down
}

void Stop_Timer()
{
	TACTL &= ~MC_3;
}

void Start_Timer()
{
	TACTL |= MC_3;
}

//Peripheral Devices Control
static void Power_Level_Indicator_Work()
{
	if(Power_Indicator_Counter == POWER_LEVEL_INDICATOR_PERIOD)
	{
		//Stop_Timer();
		Power_Indicator_Counter = 0;
		if(Check_High_Battery_Power())
		{
			//Flash Green Light
			High_Battery_Power_Flash();
		}
		else if (Check_Low_Battery_Power())
		{
			//Flash Red Light
			Low_Battery_Power_Flash();
		}
		//Start_Timer();
	}
}

// ADC starts converting
static void ADC_Work()
{
	if(Seconds_Counter == ADC_CONVERT_PERIOD)
	{
		//Stop_Timer();
		Seconds_Counter = 0;
		Start_ADC_Conversion(); 	//Start ADC Conversion
		//Start_Timer();
	}
}

//Interrupt Service Routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_ISR()
{
	//Timer Count
	Stop_Timer();
	Seconds_Counter ++ ;
	Power_Indicator_Counter ++ ;
	//Operations
	Power_Level_Indicator_Work();
	ADC_Work();

	Start_Timer();
}




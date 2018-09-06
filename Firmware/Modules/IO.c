/*
 * IO.c
 *
 *  Created on: 2016Äê5ÔÂ19ÈÕ
 *      Author: DBN
 */
#include <msp430.h>
#include <IO.h>
#include <RGB.h>
#include <ADC.h>

#define CHARG_SIGNAL BIT2

void IO_Init()
{
	P1DIR = 0xFF;
	P2DIR = 0xFF;
	P3DIR = 0xFF;
}

// Battery charging interrupt initialization
void Charging_Detection_Init()
{
	P1DIR &= ~CHARG_SIGNAL;
	P1IE |= CHARG_SIGNAL;
	P2IES &= CHARG_SIGNAL; //High to Low trigger
}


Socket_Status Check_Power_Status()
{
	if(!(P1IN & CHARG_SIGNAL))
	{
		return plug_in;
	}
	else
	{
		return pull_out;
	}
}

#pragma vector = PORT1_VECTOR
__interrupt void Power_Plug_In_ISR()
{
	if(P1IFG & CHARG_SIGNAL)
	{
		Power_Plug_In_Flash();
		Reset_High_Battery_First_Enter_Mark();
	}
	P1IFG &= ~CHARG_SIGNAL;
}



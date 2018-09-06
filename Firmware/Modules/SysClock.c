/*
 * Sysclock.c
 *
 *  Created on: 2016Äê4ÔÂ30ÈÕ
 *      Author: DBN
 */
#include <msp430.h>
#include <SysClock.h>

void Clock_init()
{
	DCOCTL = DCO0;
	BCSCTL1 = RSEL0 + RSEL1 + RSEL2;
}

// Output the SMCLK for debugging purpose
void SMCLK_Detectable()
{
	P1DIR |= BIT4;
	P1SEL |= BIT4;
}




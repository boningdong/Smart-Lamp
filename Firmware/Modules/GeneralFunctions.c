/*
 * GeneralFunctions.c
 *
 *  Created on: 2016Äê5ÔÂ17ÈÕ
 *      Author: DBN
 */
#include <msp430.h>
#include <GeneralFunctions.h>

void delay(unsigned int time)
{
	unsigned int x, y;
	for (x = time; x > 0; x--)
	{
		for(y = 100; y > 0; y--);
	}
}


/*
 * UART.c
 *
 *  Created on: 2016Äê5ÔÂ17ÈÕ
 *      Author: DBN
 *
 *  UART part is connected to BLE module, and used to communicate between upper machine and controller.
 */

#include <msp430.h>
#include <UART.h>
#include <RGB.h>
#include <ADC.h>

void ApplyRGB();

// The format of the communication.
unsigned char RXD_Data[17] = "R000G000B000B000";
unsigned char DataCounter = 0;
unsigned char RedData, GreenData, BlueData, BrightData;


// Serial Communication initialization
void UART_init()
{
	P3SEL |= BIT4 + BIT5;
	UCA0CTL1 |= UCSWRST;
	UCA0CTL1 |= UCSSEL_2;	//SMCLK = 1MHz
	UCA0BR0 = 104;
	UCA0BR1 = 0;
	UCA0MCTL |= UCBRS0;
	UCA0CTL1 &= ~UCSWRST;
	IE2 |= UCA0RXIE;
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIRX_SIR()
{
	if(IFG2 & UCA0RXIFG)
	{
		if(UCA0RXBUF == 'R')
		{
			DataCounter = 0;
		}

		if(DataCounter < 15)
		{
			RXD_Data[DataCounter] = UCA0RXBUF;
			DataCounter++;
		}
		else if (DataCounter == 15)
		{
			RXD_Data[DataCounter] = UCA0RXBUF;
			DataCounter++;
			RXD_Data[DataCounter] = '\0';
			DataCounter = 0;
			ApplyRGB();
		}
	}
}

void ApplyRGB()
{
    // Check if the communication format is correct.
	if(		(RXD_Data[0] == 'R')&&
			(RXD_Data[4] == 'G')&&
			(RXD_Data[8] == 'B')&&
			(RXD_Data[12] == 'B')	)
	{
		RedData = (RXD_Data[1]-48)*100 + (RXD_Data[2]-48)*10 + (RXD_Data[3]-48);
		GreenData = (RXD_Data[5]-48)*100 + (RXD_Data[6]-48)*10 + (RXD_Data[7]-48);
		BlueData = (RXD_Data[9]-48)*100 + (RXD_Data[10]-48)*10 + (RXD_Data[11]-48);
		BrightData = (RXD_Data[13]-48)*100 + (RXD_Data[14]-48)*10 + (RXD_Data[15]-48);
	}

	else
	{
		P1OUT &= ~BIT0;
	}

	if(!((RedData)||(GreenData)||(BlueData)||(BrightData)))
	{
		P1OUT &= ~BIT2;
	}
	else
	{
		SetColor(RedData, GreenData, BlueData, BrightData);
	}
}




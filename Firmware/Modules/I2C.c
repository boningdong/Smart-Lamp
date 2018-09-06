/*
 * I2C.c
 *
 *  Created on: 2016Äê4ÔÂ30ÈÕ
 *      Author: DBN
 */
#include <msp430.h>
#include <I2C.h>

unsigned char TxData[2];

// I2C module initialization
void I2C_init()
{
	//P3DIR |= BIT1 + BIT2;
	//P3OUT |= BIT1 + BIT2;
	P3SEL |= BIT1 + BIT2;                     // Assign I2C pins to USCI_B0
	UCB0CTL1 |= UCSWRST;                      // Enable SW reset
	UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
	UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
	UCB0BR0 = 25;                             // fSCL = SMCLK/20 = ~50kHz
	UCB0BR1 = 0x00;
	UCB0I2CSA = 0x62;
	UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
	//IE2 |= UCB0TXIE;                          // Enable TX interrupt
}

// Send data through i2c by writing data to transmit buffer
void SendData(unsigned char CtlReg, unsigned char data)
{
    // CtlReg: target register address
    // data: data write to the register
	int i;
	TxData[0] = CtlReg;
	TxData[1] = data;
	while (UCB0CTL1 & UCTXSTP);
	UCB0CTL1 |= UCTR + UCTXSTT; 	//Start Condition

	for (i = 0; i <= 2; i++)
	{
		while (!(IFG2 & UCB0TXIFG));
		IFG2 &= ~UCB0TXIFG;
		if(i <= 1)
		{
			UCB0TXBUF = TxData[i];
		}
		else
		{
			UCB0CTL1 |= UCTXSTP;
		}
	}
}




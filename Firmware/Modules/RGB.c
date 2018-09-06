/*
 * RGB.c
 *
 *  Created on: 2016Äê4ÔÂ30ÈÕ
 *      Author: DBN
 */

#include <msp430.h>
#include <I2C.h>
#include <RGB.h>
#include <IO.h>
#include <GeneralFunctions.h>


/*Configurated by User
 *  according to hardware design*/
#define LED_R PWM1
#define LED_G PWM2
#define LED_B PWM0

Color OldColor;
Color ColorRemember;
flashing Is_Flashing = is_not_Flashing;

//RGB Initialize and RGB Power Control
void RGB_init()
{
	SendData(MODE1,0x81);
	//SendData(MODE2,0x09);
	SendData(MODE2,0x1D);
	SendData(LEDOUT,0x3F);
	OldColor.red = 0;
	OldColor.blue = 0;
	OldColor.green = 0;
	OldColor.brightness = 0;
}

void RGB_PowEnable()
{
	P1DIR |= BIT7;
	P1OUT |= BIT7;
}

void RGB_PowDisable()
{
	P1OUT &= ~BIT7;
}


// Used for setting color
void SetColor(
		unsigned char red,
		unsigned char green,
		unsigned char blue,
		unsigned char brightness )
{
	if(	(OldColor.red == 0) 	&&
		(OldColor.green == 0) 	&&
		(OldColor.blue == 0)	&&
		(OldColor.brightness == 0))
	{
		OldColor.red = red;
		OldColor.green = green;
		OldColor.blue = blue;
		OldColor.brightness = brightness;

	}

	else
	{
		while( 	(red!=OldColor.red)		||
				(blue!=OldColor.blue)	||
				(green!=OldColor.green)	||
				(brightness!=OldColor.brightness))
		{
			OldColor.red = GetClose(red, OldColor.red);
			OldColor.green = GetClose(green, OldColor.green);
			OldColor.blue = GetClose(blue, OldColor.blue);
			OldColor.brightness = GetClose(brightness, OldColor.brightness);

			SendData(LED_R,OldColor.red);
			SendData(LED_G,OldColor.green);
			SendData(LED_B,OldColor.blue);
			SendData(GRPPWM,OldColor.brightness);
		}
	}
	SendData(LED_R,red);
	SendData(LED_G,green);
	SendData(LED_B,blue);
	SendData(GRPPWM,brightness);
}

void RGB_reset()
{
	UCB0I2CSA = 0x03;
	SendData(0xA5,0x5A);
	UCB0I2CSA = 0x62;
}

void RestoreColor()
{
	SetColor(ColorRemember.red, ColorRemember.green, ColorRemember.blue, ColorRemember.brightness);
}

void RememberColor()
{
	ColorRemember.red = GetRed();
	ColorRemember.green = GetGreen();
	ColorRemember.blue = GetBlue();
	ColorRemember.brightness = GetBright();
}


void Low_Battery_Power_Flash()
{
	int Flash_Times;
	RememberColor();
	for(Flash_Times = 2; Flash_Times > 0; Flash_Times --)
	{
		SetColor(255,130,130,200);
		delay(200);
		RestoreColor();
		delay(200);
	}
}

void High_Battery_Power_Flash()
{
	int Flash_Times;
	RememberColor();
	for(Flash_Times = 2; Flash_Times > 0; Flash_Times --)
	{
		SetColor(140,255,160,200);
		delay(200);
		RestoreColor();
		delay(200);
	}
}

void Power_Plug_In_Flash()
{
	int Flash_Times;
	RememberColor();
	delay(50);
	if(Check_Power_Status())
	{
		unsigned char P1_Status = P1OUT;
		if(!(P1_Status & BIT7))
		{
			RememberColor();
			SetColor(255,255,255,0);
			delay(20);
		}
		RGB_PowEnable();
		for(Flash_Times = 2; Flash_Times > 0; Flash_Times --)
		{
			SetColor(100,210,240,200);
			delay(200);
			if(!(P1_Status & BIT7))
			{
				SetColor(255,255,255,0);
			}
			else
			{
				RestoreColor();
			}
			delay(200);
		}
		if(!(P1_Status & BIT7))
		{
			RGB_PowDisable();
			delay(200);
			RestoreColor();
		}
	}
}

void Acknowledge_Flash()
{
	delay(20);
	RememberColor();
	SetColor(200,0,255,200);
	RestoreColor();
	delay(20);
}

//Conditions
unsigned char GetRed()
{
	return OldColor.red;
}

unsigned char GetGreen()
{
	return OldColor.green;
}

unsigned char GetBlue()
{
	return OldColor.blue;
}

unsigned char GetBright()
{
	return OldColor.brightness;
}

// Used for changing the color smoothly but not abruptly
unsigned char GetClose (unsigned char target, unsigned char old)
{
	if(old < target)
	{
		old++;
		return old;
	}

	else if(old > target)
	{
		old--;
		return old;
	}

	else
	{
		return old;
	}
}

/*
 * IO.c
 *
 *  Created on: 2016年5月17日
 *      Author: DBN
 */
#include <msp430.h>
#include <RGB.h>
#include <ADC.h>
#include <Timer.h>
#include <TouchPad.h>
#include <GeneralFunctions.h>

#define TOUCH_PAD BIT1
#define	RGB_ON	BIT7

unsigned char red;
unsigned char green;
unsigned char blue;
unsigned char bright;

unsigned char Touch_Counter = 0; //Used for Monitoring the Battery

//Touch Pad Initialize
void TouchPad_Init()
{
	P2DIR &= ~TOUCH_PAD;
	P2IE |= TOUCH_PAD;
	P2IES &= ~TOUCH_PAD;
	//P2REN |= TOUCH_PAD;
	//P2OUT &= ~TOUCH_PAD;
}

//Peripheral Devices Control
static void Long_Time_Touch_Dimming()
{
	//正常 调光功能
	red = GetRed();
	blue = GetBlue();
	green = GetGreen();
	bright = GetBright();

	if(dim_dir == down)
	{
		while((P2IN & TOUCH_PAD)&&(bright > 30))
		{
			bright--;
			SetColor(red, green, blue, bright);
			delay(2);
		}
		dim_dir = up;
		while(P2IN & TOUCH_PAD);
	}
	else if(dim_dir == up)
	{
		while((P2IN & TOUCH_PAD)&&(bright < 255))
		{
			bright++;
			SetColor(red, green, blue, bright);
			delay(2);
		}
		dim_dir = down;
		while(P2IN & TOUCH_PAD);
	}
}

static void Short_Time_Touch_Off()
{
	if (
			( Check_High_Battery_Power() ) || ( Check_Low_Battery_Power() )
	   )
	{
		Exit_High_Battery_Power_Mode();
		Exit_Low_Battery_Power_Mode();
		Acknowledge_Flash();
	}
	else
	{
		P1OUT &= ~RGB_ON;
	}
}

static void Short_Time_Touch_On()
{
	delay(200);
	P1OUT |= RGB_ON;
}

#pragma vector = PORT2_VECTOR
__interrupt void PORT2_ISR()
{
	//Touch  PAD was Touched
	if(P2IFG & TOUCH_PAD)
	{

		//If RGB is ON
		if(P1IN & RGB_ON)
		{
			delay(20); // Prevent Noise
			if(P2IN & TOUCH_PAD)
			{
				delay(200);
				if(P2IN & TOUCH_PAD)
				{
					Long_Time_Touch_Dimming();
				}
				else
				{
					Short_Time_Touch_Off();
				}
			}
		}
		//If RGB is OFF
		else
		{
			Short_Time_Touch_On();
		}
	}
	P2IFG &= ~TOUCH_PAD;
}

//显示电量功能
/*unsigned char temp_red, temp_green, temp_blue, temp_bright;
temp_red = GetRed();
temp_green = GetGreen();
temp_blue = GetBlue();
temp_bright = GetBright();
if( Manual_ReadVolt() < 3.3 )
{
	SetColor(255, 0, 0, 255);
}
else if( Manual_ReadVolt() < 3.8 )
{
	SetColor(255, 0, 0, 255);
}
else
{
	SetColor(75, 240, 255, 255);
}
while(P2IN & TOUCH_PAD);
SetColor(temp_red, temp_green, temp_blue, temp_bright);*/


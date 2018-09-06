#include <msp430.h> 
#include <I2C.h>
#include <SysClock.h>
#include <RGB.h>
#include <UART.h>
#include <ADC.h>
#include <Timer.h>
#include <stdio.h>
#include <IO.h>
#include <GeneralFunctions.h>


/*
 * main.c
 */
void TouchPad_Init();


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    //IO_Init();
    _EINT();
    //Clock
    Clock_init();
    SMCLK_Detectable();

    UART_init();
    I2C_init ();
    TouchPad_Init();
    ADC_Init();
    Charging_Detection_Init();
    Timer_Init();

    RGB_PowEnable();
    RGB_reset ();
    RGB_init ();

    SetColor (255, 255, 70, 255);   // Set default color to warm color and maximum brightness
    _BIS_SR(LPM0_bits + GIE);   // Enter low power Mode and enable global interrupt
}












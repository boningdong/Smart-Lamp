/*
 * RGB.h
 *
 *  Created on: 2016Äê4ÔÂ30ÈÕ
 *      Author: DBN
 */

#ifndef MODULES_RGB_H_
#define MODULES_RGB_H_

#define MODE1 		0x00
#define MODE2 		0x01
#define PWM0 		0x02
#define PWM1 		0x03
#define PWM2 		0x04
#define PWM3 		0x05
#define GRPPWM 		0x06
#define GRPFREQ 	0x07
#define LEDOUT		0x08
#define SUBADR1		0x09
#define SUBADR2 	0x0A
#define SUBADR3 	0x0B
#define ALLCALLAD	0x0C



unsigned char GetRed();
unsigned char GetGreen();
unsigned char GetBlue();
unsigned char GetBright();

typedef enum {
    is_not_Flashing = 0,
    is_Flashing = 1
}flashing;

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char brightness;
}Color;

unsigned char GetClose (unsigned char target, unsigned char old);
void RGB_init();
void SetColor(unsigned char, unsigned char, unsigned char, unsigned char);
void RGB_reset();
void RGB_PowEnable();
void RGB_PowDisable();
void RememberColor();
void RestoreColor();
void RememberColor2();
void RestoreColor2();
void Low_Battery_Power_Flash();
void High_Battery_Power_Flash();
void Power_Plug_In_Flash();
void Acknowledge_Flash();



#endif /* MODULES_RGB_H_ */

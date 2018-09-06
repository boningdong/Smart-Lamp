/*
 * ADC.h
 *
 *  Created on: 2016Äê5ÔÂ17ÈÕ
 *      Author: DBN
 */

#ifndef MODULES_ADC_H_
#define MODULES_ADC_H_

/*Type define*/
typedef enum{
	no  = 0,
	yes = 1
} bool;


/*Analog to Digital Converter Control*/
void ADC_Init();
void Start_ADC_Conversion();
float Manual_ReadVolt();

/*Battery Status Check and Control*/
bool Check_High_Battery_Power();
bool Check_Low_Battery_Power();
void Exit_High_Battery_Power_Mode();
void Exit_Low_Battery_Power_Mode();
void Reset_High_Battery_First_Enter_Mark();




#endif /* MODULES_ADC_H_ */

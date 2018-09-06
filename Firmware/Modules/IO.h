/*
 * IO.h
 *
 *  Created on: 2016Äê5ÔÂ19ÈÕ
 *      Author: DBN
 */

#ifndef MODULES_IO_H_
#define MODULES_IO_H_

typedef enum {
	pull_out = 0,
	plug_in = 1
} Socket_Status;

void IO_Init();
void Charging_Detection_Init();
Socket_Status Check_Power_Status();

#endif /* MODULES_IO_H_ */

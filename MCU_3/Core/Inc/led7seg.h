/*
 * led7seg.h
 *
 *  Created on: Sep 26, 2023
 *      Author: Windows
 */


#ifndef INC_LED7SEG_H_
#define INC_LED7SEG_H_
#include "main.h"
#include "software_timer.h"

extern int index_led;
extern int led_buffer[4];

void display7SEG(int num);
void clearAll_7SEG();
void updateClockBuffer_vertical(int num);
void updateClockBuffer_horizontal(int num);
void led7seg_run();
void update7SEG( int index );
#endif /* INC_LED7SEG_H_ */

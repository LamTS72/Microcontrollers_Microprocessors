/*
 * traffic_ligh.h
 *
 *  Created on: Sep 28, 2023
 *      Author: Windows
 */

#ifndef INC_TRAFFIC_LIGH_H_
#define INC_TRAFFIC_LIGH_H_

#include "main.h"
#include "led7seg.h"
#include "software_timer.h"
#include "fsm.h"
#define RED     		1
#define YELLOW  		2
#define GREEN   		3
#define RED_BLINK   	4
#define YELLOW_BLINK 	5
#define GREEN_BLINK   	6
extern int red_counter;
extern int green_counter;
extern int yellow_counter;
extern int led_hred;
extern int led_hgreen;
extern int led_hyellow;
extern int led_vred;
extern int led_vgreen;
extern int led_vyellow;
extern int red_change;
extern int green_change;
extern int yellow_change;
extern int light_hmode;
extern int light_vmode;
extern int led_hmode;
extern int led_vmode;
void traffic_light_horizontal();
void traffic_light_vertical();
void traffic_led7seg();
void led_blinked(int blinked_mod);
#endif /* INC_TRAFFIC_LIGH_H_ */

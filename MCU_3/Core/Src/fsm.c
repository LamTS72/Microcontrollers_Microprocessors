/*
 * fsm.c
 *
 *  Created on: Sep 26, 2023
 *      Author: Windows
 */

#include "fsm.h"

int state = 0;
void fsm_mode_run(){
	switch(state){
	case 0:
		state = MODE_1;
		setTimer0(10);
		break;
	case MODE_1:
		traffic_light_horizontal();
		traffic_light_vertical();
		traffic_led7seg();
		if(isMODE_Pressed() == 1){
			state = MODE_2;
			timer6_flag = 1;
			setTimer0(100);
		}
		break;
	case MODE_2:
		traffic_light_horizontal();
		traffic_light_vertical();
		traffic_led7seg();
		if(isMODE_Pressed() == 1){
			state = MODE_3;
			setTimer0(100);
		}
		if(isINC_Pressed() == 1){
			if(red_change < 99){
				red_change++;
			}
			else{
				red_change = 0;
			}
		}
		if(isSET_Pressed() == 1){
			red_counter = red_change;
			led_hred = red_counter;
			led_vred = red_counter;
			state = MODE_1;
			setTimer0(10);
		}
		break;
	case MODE_3:
		traffic_light_horizontal();
		traffic_light_vertical();
		traffic_led7seg();
		if(isMODE_Pressed() == 1){
			state = MODE_4;
			setTimer0(100);
		}
		if(isINC_Pressed() == 1){
			if(yellow_change < 99){
				yellow_change++;
			}
			else{
				yellow_change = 0;
			}
		}
		if(isSET_Pressed() == 1){
			yellow_counter = yellow_change;
			led_hyellow = yellow_counter;
			led_vyellow = yellow_counter;
			state = MODE_1;
			setTimer0(10);
		}
		break;
	case MODE_4:
		traffic_light_horizontal();
		traffic_light_vertical();
		traffic_led7seg();
		if(isMODE_Pressed() == 1){
			state = 1;
			setTimer0(100);
		}
		if(isINC_Pressed() == 1){
			if(green_change < 99){
				green_change++;
			}
			else{
				green_change = 0;
			}
		}
		if(isSET_Pressed() == 1){
			green_counter = green_change;
			led_hgreen = green_counter;
			led_vgreen = green_counter;
			state = MODE_1;
			setTimer0(10);
		}
		break;
	}
}

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
			HAL_GPIO_WritePin(GPIOA, PA1_Pin| PA2_Pin | PA3_Pin |PA4_Pin |
									PA5_Pin | PA6_Pin, SET);
			state = MODE_2;
		}
		break;
	case MODE_2:
		led_blinked(1);
		if(isMODE_Pressed() == 1){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin| PA2_Pin | PA3_Pin |PA4_Pin |
									PA5_Pin | PA6_Pin, SET);
			state = MODE_3;
			setTimer0(100);
		}
		break;
	case MODE_3:
		led_blinked(2);
		if(isMODE_Pressed() == 1){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin| PA2_Pin | PA3_Pin |PA4_Pin |
									PA5_Pin | PA6_Pin, SET);
			state = MODE_4;
			setTimer0(100);
		}
		break;
	case MODE_4:
		led_blinked(3);
		if(isMODE_Pressed() == 1){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin| PA2_Pin | PA3_Pin |PA4_Pin |
									PA5_Pin | PA6_Pin, SET);
			state = MODE_1;
			setTimer0(100);
		}
		break;
	}
}

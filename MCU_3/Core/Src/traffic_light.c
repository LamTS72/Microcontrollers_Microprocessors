/*
 * traffic_light.c
 *
 *  Created on: Sep 28, 2023
 *      Author: Windows
 */

#include "traffic_ligh.h"

const int red_counter = 5;
const int green_counter = 3;
const int yellow_counter = 2;

int led_hred = 5;
int led_hgreen = 3;
int led_hyellow = 2;
int led_vred = 5;
int led_vgreen = 3;
int led_vyellow = 2;

int light_hmode = 0;
int light_vmode = 0;
int led_hmode = 0;
int led_vmode = 0;
void traffic_light_horizontal(){
	switch (light_hmode){
	case 0:
		light_hmode = RED;
		setTimer1(red_counter*1000);
		break;
	case RED:
		HAL_GPIO_WritePin(PA1_GPIO_Port, PA1_Pin, RESET);
		HAL_GPIO_WritePin(PA2_GPIO_Port, PA2_Pin, SET);
		HAL_GPIO_WritePin(PA3_GPIO_Port, PA3_Pin, SET);
		if(timer1_flag == 1){
			light_hmode =GREEN;
			setTimer1(green_counter*1000);
		}
		break;
	case GREEN:
		//horizontal
		HAL_GPIO_WritePin(PA1_GPIO_Port, PA1_Pin, SET);
		HAL_GPIO_WritePin(PA2_GPIO_Port, PA2_Pin, SET);
		HAL_GPIO_WritePin(PA3_GPIO_Port, PA3_Pin, RESET);
		if(timer1_flag == 1){
			light_hmode = YELLOW;
			setTimer1(yellow_counter*1000);
		}
		break;
	case YELLOW:
		//horizontal
		HAL_GPIO_WritePin(PA1_GPIO_Port, PA1_Pin, SET);
		HAL_GPIO_WritePin(PA2_GPIO_Port, PA2_Pin, RESET);
		HAL_GPIO_WritePin(PA3_GPIO_Port, PA3_Pin, SET);
		if(timer1_flag == 1){
			light_hmode = RED;
			setTimer1(red_counter*1000);
		}
		break;
	}

}
void traffic_light_vertical(){
	switch (light_vmode){
	case 0:
		light_vmode = GREEN;
		setTimer2(green_counter*1000);
		break;
	case GREEN:
		//vertical
		HAL_GPIO_WritePin(PA4_GPIO_Port, PA4_Pin, SET);
		HAL_GPIO_WritePin(PA5_GPIO_Port, PA5_Pin, SET);
		HAL_GPIO_WritePin(PA6_GPIO_Port, PA6_Pin, RESET);
		if(timer2_flag == 1){
			light_vmode = YELLOW;
			setTimer2(yellow_counter*1000);
		}
		break;
		case YELLOW:
		//vertical
		HAL_GPIO_WritePin(PA4_GPIO_Port, PA4_Pin, SET);
		HAL_GPIO_WritePin(PA5_GPIO_Port, PA5_Pin, RESET);
		HAL_GPIO_WritePin(PA6_GPIO_Port, PA6_Pin, SET);
		if(timer2_flag == 1){
			light_vmode = RED;
			setTimer2(red_counter*1000);
		}
		break;
		case RED:
		//vertical
		HAL_GPIO_WritePin(PA4_GPIO_Port, PA4_Pin, RESET);
		HAL_GPIO_WritePin(PA5_GPIO_Port, PA5_Pin, SET);
		HAL_GPIO_WritePin(PA6_GPIO_Port, PA6_Pin, SET);
		if(timer2_flag == 1){
			light_vmode = GREEN;
			setTimer2(green_counter*1000);
		}
		break;
	}
}

void traffic_led7seg(){
	led7seg_run();
	switch (led_hmode){
		case 0:
			led_hmode = RED;
			timer4_flag = 1;
			break;
		case RED:
			if(timer4_flag == 1){
				updateClockBuffer_horizontal(led_hred);
				led_hred--;
				if(led_hred < 0){
					led_hred = red_counter;
					led_hmode = GREEN;
				}
				else{
					setTimer4(1000);
				}

			}
			break;
		case GREEN:
			if(timer4_flag == 1){
				updateClockBuffer_horizontal(led_hgreen);
				led_hgreen--;
				if(led_hgreen < 0){
					led_hgreen = green_counter;
					led_hmode = YELLOW;
				}
				else{
					setTimer4(1000);
				}

			}
			break;
		case YELLOW:
			if(timer4_flag == 1){
				updateClockBuffer_horizontal(led_hyellow);
				led_hyellow--;
				if(led_hyellow < 0){
					led_hyellow = yellow_counter;
					led_hmode = RED;
				}
				else{
					setTimer4(1000);
				}

			}
			break;
		default:
			break;
	}

	switch (led_vmode){
		case 0:
			led_vmode = GREEN;
			timer5_flag = 1;
			break;
		case GREEN:
			if(timer5_flag == 1){
				updateClockBuffer_vertical(led_vgreen);
				led_vgreen--;
				if(led_vgreen < 0){
					led_vgreen = green_counter;
					led_vmode = 2;
				}
				else{
					setTimer5(1000);
				}
			}
			break;
		case YELLOW:
			if(timer5_flag == 1){
				updateClockBuffer_vertical(led_vyellow);
				led_vyellow--;
				if(led_vyellow < 0){
					led_vyellow = yellow_counter;
					led_vmode = RED;
				}
				else{
					setTimer5(1000);
				}

			}
			break;
		case RED:
			if(timer5_flag == 1){
				updateClockBuffer_vertical(led_vred);
				led_vred--;
				if(led_vred < 0){
					led_vred = red_counter;
					led_vmode = GREEN;
				}
				else{
					setTimer5(1000);
				}

			}
			break;
		default:
				break;
		}
}

void led_blinked(int blinked_mode){
	HAL_GPIO_WritePin(GPIOA, PA1_Pin |PA4_Pin | PA2_Pin| PA5_Pin|PA3_Pin | PA6_Pin , SET);
	switch (blinked_mode){
	case 1:
		HAL_GPIO_TogglePin(GPIOA, PA1_Pin);
		HAL_GPIO_TogglePin(GPIOA, PA4_Pin);
		//setTimer4(20);
		break;
	case 2:
		HAL_GPIO_TogglePin(GPIOA, PA2_Pin);
		HAL_GPIO_TogglePin(GPIOA, PA5_Pin);
		//setTimer4(20);
		break;
	case 3:
		HAL_GPIO_TogglePin(GPIOA, PA3_Pin);
		HAL_GPIO_TogglePin(GPIOA, PA6_Pin);
		//setTimer4(20);
		break;
	}
}



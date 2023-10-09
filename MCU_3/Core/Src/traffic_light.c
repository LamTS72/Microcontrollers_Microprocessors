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

int counter_h = 0;
int counter_v = 0;
int light_hmode = 0;
int light_vmode = 0;
int led_hmode = 0;
int led_vmode = 0;
void traffic_light_horizontal(){
	switch (light_hmode){
	case 0:
		light_hmode = 1;
		counter_h = red_counter;
		setTimer1(red_counter*1000);
		timer4_flag = 1;
		break;
	case 1:
		HAL_GPIO_WritePin(PA1_GPIO_Port, PA1_Pin, RESET);
		HAL_GPIO_WritePin(PA2_GPIO_Port, PA2_Pin, SET);
		HAL_GPIO_WritePin(PA3_GPIO_Port, PA3_Pin, SET);
		if(timer1_flag == 1){
			light_hmode = 2;
			setTimer1(green_counter*1000);
		}
		if(timer4_flag == 1){
			updateClockBuffer_horizontal(counter_h);
			counter_h--;
			if(counter_h <= 0){
				counter_h = green_counter;
			}
			else{
				setTimer4(1000);
			}

		}
		break;
	case 2:
		//horizontal
		HAL_GPIO_WritePin(PA1_GPIO_Port, PA1_Pin, SET);
		HAL_GPIO_WritePin(PA2_GPIO_Port, PA2_Pin, SET);
		HAL_GPIO_WritePin(PA3_GPIO_Port, PA3_Pin, RESET);
		if(timer1_flag == 1){
			light_hmode = 3;
			setTimer1(yellow_counter*1000);
		}
		if(timer4_flag == 1){
			updateClockBuffer_horizontal(counter_h);
			counter_h--;
			if(counter_h <= 0){
				counter_h = yellow_counter;
			}
			else{
				setTimer4(1000);
			}

		}
		break;
	case 3:
		//horizontal
		HAL_GPIO_WritePin(PA1_GPIO_Port, PA1_Pin, SET);
		HAL_GPIO_WritePin(PA2_GPIO_Port, PA2_Pin, RESET);
		HAL_GPIO_WritePin(PA3_GPIO_Port, PA3_Pin, SET);
		if(timer1_flag == 1){
			light_hmode = 1;
			setTimer1(red_counter*1000);
		}
		if(timer4_flag == 1){
			updateClockBuffer_horizontal(counter_h);
			counter_h--;
			if(counter_h <= 0){
				counter_h = red_counter;
			}
			else{
				setTimer4(1000);
			}

		}
		break;
	}

}
void traffic_light_vertical(){
	switch (light_vmode){
	case 0:
		light_vmode = 1;
		counter_v = green_counter;
		setTimer2(green_counter*100);
		timer5_flag = 1;
		break;
	case 1:
		//vertical
		HAL_GPIO_WritePin(PA4_GPIO_Port, PA4_Pin, SET);
		HAL_GPIO_WritePin(PA5_GPIO_Port, PA5_Pin, SET);
		HAL_GPIO_WritePin(PA6_GPIO_Port, PA6_Pin, RESET);
		if(timer2_flag == 1){
			light_vmode = 2;
			setTimer2(yellow_counter*1000);
		}
		if(timer5_flag == 1){
			updateClockBuffer_vertical(counter_v);
			counter_v--;
			if(counter_v <= 0){
				counter_v = yellow_counter;
			}
			else{
				setTimer5(1000);
			}

		}
		break;
		case 2:
		//vertical
		HAL_GPIO_WritePin(PA4_GPIO_Port, PA4_Pin, SET);
		HAL_GPIO_WritePin(PA5_GPIO_Port, PA5_Pin, RESET);
		HAL_GPIO_WritePin(PA6_GPIO_Port, PA6_Pin, SET);
		if(timer2_flag == 1){
			light_vmode = 3;
			setTimer2(red_counter*1000);
		}
		if(timer5_flag == 1){
			updateClockBuffer_vertical(counter_v);
			counter_v--;
			if(counter_v <= 0){
				counter_v = red_counter;
			}
			else{
				setTimer5(1000);
			}

		}
		break;
		case 3:
		//vertical
		HAL_GPIO_WritePin(PA4_GPIO_Port, PA4_Pin, RESET);
		HAL_GPIO_WritePin(PA5_GPIO_Port, PA5_Pin, SET);
		HAL_GPIO_WritePin(PA6_GPIO_Port, PA6_Pin, SET);
		updateClockBuffer_vertical(counter_v);
		if(timer2_flag == 1){
			light_vmode = 0;
			setTimer2(green_counter*1000);
		}
		if(timer5_flag == 1){
			updateClockBuffer_vertical(counter_v);
			counter_v--;
			if(counter_v <= 0){
				counter_v = green_counter;
			}
			else{
				setTimer5(1000);
			}

		}
		break;
	}
}

void traffic_led7seg(){
	led7seg_run();
	switch (led_hmode){
		case 0:
			led_hmode = 1;
			counter_h = red_counter;
			timer4_flag = 1;
			break;
		case 1:
			if(timer4_flag == 1){
				updateClockBuffer_horizontal(counter_h);
				counter_h--;
				if(counter_h <= 0){
					counter_h = green_counter;
					led_hmode = 2;
				}
				else{
					setTimer4(1000);
				}

			}
			break;
		case 2:
			if(timer4_flag == 1){
				updateClockBuffer_horizontal(counter_h);
				counter_h--;
				if(counter_h <= 0){
					counter_h = yellow_counter;
					led_hmode = 3;
				}
				else{
					setTimer4(1000);
				}

			}
			break;
		case 3:
			if(timer4_flag == 1){
				updateClockBuffer_horizontal(counter_h);
				counter_h--;
				if(counter_h <= 0){
					counter_h = red_counter;
					led_hmode = 1;
				}
				else{
					setTimer4(1000);
				}

			}
			break;
	}

	switch (led_vmode){
	case 0:
		led_vmode = 1;
		counter_v = green_counter;
		timer5_flag = 1;
		break;
	case 1:
		if(timer5_flag == 1){
			updateClockBuffer_vertical(counter_v);
			counter_v--;
			if(counter_v <= 0){
				counter_v = yellow_counter;
				led_vmode = 2;
			}
			else{
				setTimer5(1000);
			}
		}
		break;
		case 2:
		if(timer5_flag == 1){
			updateClockBuffer_vertical(counter_v);
			counter_v--;
			if(counter_v <= 0){
				counter_v = red_counter;
				led_vmode = 3;
			}
			else{
				setTimer5(1000);
			}

		}
		break;
		case 3:
		if(timer5_flag == 1){
			updateClockBuffer_vertical(counter_v);
			counter_v--;
			if(counter_v <= 0){
				counter_v = green_counter;
				led_vmode = 1;
			}
			else{
				setTimer5(1000);
			}

		}
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



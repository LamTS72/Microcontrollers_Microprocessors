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

int counter_h = red_counter;
int counter_v = green_counter;
int light_hmode = 0;
int light_vmode = 0;
void traffic_light_horizontal(){
	if(timer1_flag == 1){
		switch (light_hmode){
		case 0:
				HAL_GPIO_WritePin(PA1_GPIO_Port, PA1_Pin, RESET);
				HAL_GPIO_WritePin(PA2_GPIO_Port, PA2_Pin, SET);
				HAL_GPIO_WritePin(PA3_GPIO_Port, PA3_Pin, SET);
				updateClockBuffer_horizontal(counter_h);
				if(counter_h <= 0 ){
					counter_h = green_counter;
					light_hmode = 1;
				}
				break;
			case 1:
				//horizontal
				HAL_GPIO_WritePin(PA1_GPIO_Port, PA1_Pin, SET);
				HAL_GPIO_WritePin(PA2_GPIO_Port, PA2_Pin, SET);
				HAL_GPIO_WritePin(PA3_GPIO_Port, PA3_Pin, RESET);
				updateClockBuffer_horizontal(counter_h);
				if(counter_h <= 0){
					counter_h = yellow_counter;
					light_hmode = 2;
				}
				break;
			case 2:
				//horizontal
				HAL_GPIO_WritePin(PA1_GPIO_Port, PA1_Pin, SET);
				HAL_GPIO_WritePin(PA2_GPIO_Port, PA2_Pin, RESET);
				HAL_GPIO_WritePin(PA3_GPIO_Port, PA3_Pin, SET);
				updateClockBuffer_horizontal(counter_h);
				if(counter_h <= 0 ){
					counter_h = red_counter;
					light_hmode = 0;
				}
				break;
		}
		counter_h--;
		setTimer1(50);
	}
}
void traffic_light_vertical(){
	if(timer2_flag == 1){
		switch (light_vmode){
		case 0:
				//vertical
				HAL_GPIO_WritePin(PA4_GPIO_Port, PA4_Pin, SET);
				HAL_GPIO_WritePin(PA5_GPIO_Port, PA5_Pin, SET);
				HAL_GPIO_WritePin(PA6_GPIO_Port, PA6_Pin, RESET);
				updateClockBuffer_vertical(counter_v);
				if(counter_v <= 0 ){
					counter_v = yellow_counter;
					light_vmode = 1;
				}
				break;
			case 1:
				//vertical
				HAL_GPIO_WritePin(PA4_GPIO_Port, PA4_Pin, SET);
				HAL_GPIO_WritePin(PA5_GPIO_Port, PA5_Pin, RESET);
				HAL_GPIO_WritePin(PA6_GPIO_Port, PA6_Pin, SET);
				updateClockBuffer_vertical(counter_v);
				if(counter_v <= 0){
					counter_v = red_counter;
					light_vmode = 2;
				}
				break;
			case 2:
				//vertical
				HAL_GPIO_WritePin(PA4_GPIO_Port, PA4_Pin, RESET);
				HAL_GPIO_WritePin(PA5_GPIO_Port, PA5_Pin, SET);
				HAL_GPIO_WritePin(PA6_GPIO_Port, PA6_Pin, SET);
				updateClockBuffer_vertical(counter_v);
				if(counter_v <= 0 ){
					counter_v = green_counter;
					light_vmode = 0;
				}
				break;
		}
		counter_v--;
		setTimer2(50);
	}
}

void time_update(){
	if(timer4_flag == 1){
			switch (light_hmode){
			case 0:
					updateClockBuffer_horizontal(counter_h);
					break;
				case 1:
					updateClockBuffer_horizontal(counter_h);
					break;
				case 2:
					updateClockBuffer_horizontal(counter_h);
					break;
			}
			switch (light_vmode){
			case 0:
					break;
				case 1:
					updateClockBuffer_vertical(counter_v);
					break;
				case 2:
					updateClockBuffer_vertical(counter_v);
					break;
			}
			setTimer4(50);
		}
}

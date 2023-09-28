/*
 * led7seg.c
 *
 *  Created on: Sep 26, 2023
 *      Author: Windows
 */


#include "led7seg.h"

int index_led = 0;
int led_buffer[4] = {0,0,0,0};

void display7SEG(int num){
	uint8_t signal[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x12, 0x82, 0xF8, 0x80, 0x90};
  	for(int i = 0; i < 7; i++ ){
  		HAL_GPIO_WritePin(GPIOB, PB0_Pin << i, (signal[num] >> i) & 0x01);
  	}
}
void clearAll_7SEG(){
	HAL_GPIO_WritePin(GPIOB, PB0_Pin |PB1_Pin|PB2_Pin|PB3_Pin|
								PB4_Pin|PB5_Pin|PB6_Pin,SET);
}
void update7SEG ( int index){
	HAL_GPIO_WritePin(GPIOA, PA7_Pin | PA8_Pin | PA9_Pin |PA10_Pin , SET);
	switch(index){
	case 0:
		HAL_GPIO_WritePin(PA7_GPIO_Port, PA7_Pin, RESET);
		display7SEG(led_buffer[index]);
		break;
	case 1:
		HAL_GPIO_WritePin(PA8_GPIO_Port, PA8_Pin, RESET);
		display7SEG(led_buffer[index]);
		break;
	case 2:
		HAL_GPIO_WritePin(PA9_GPIO_Port, PA9_Pin, RESET);
		display7SEG(led_buffer[index]);
		break;
	default:
		HAL_GPIO_WritePin(PA10_GPIO_Port, PA10_Pin, RESET);
		display7SEG(led_buffer[index]);
		break;
	}
}
void updateClockBuffer_vertical(int hours, int minutes){
	led_buffer[0] = (hours > 9)? hours/10 : 0;
	led_buffer[1] = hours%10;

}
void updateClockBuffer_horizontal(int hours, int minutes){
	led_buffer[2] = (minutes > 9)? minutes/10 : 0;
	led_buffer[3] = minutes%10;
}
void led7seg_run(){
	if(timer2_flag == 1){
	  update7SEG(index_led);
	  if(index_led >= 3){
		  index_led = 0;
	  }
	  else{
		 index_led++;
	  }
	  setTimer2(50);
	}
}



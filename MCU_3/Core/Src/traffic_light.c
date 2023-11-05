/*
 * traffic_light.c
 *
 *  Created on: Sep 28, 2023
 *      Author: Windows
 */

#include "traffic_ligh.h"

int red_counter = 5;
int green_counter = 3;
int yellow_counter = 2;
int red_change = 5;
int green_change = 3;
int yellow_change= 2;

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
			light_hmode = GREEN;
			setTimer1(green_counter*1000);
		}
		if(state == MODE_2){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin |PA4_Pin | PA2_Pin| PA5_Pin|PA3_Pin | PA6_Pin , SET);

			light_hmode = RED_BLINK;
			setTimer1(25);
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
		if(state == MODE_2){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin |PA4_Pin | PA2_Pin| PA5_Pin|PA3_Pin | PA6_Pin , SET);

			light_hmode = RED_BLINK;
			setTimer1(25);
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
		if(state == MODE_2){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin |PA4_Pin | PA2_Pin| PA5_Pin|PA3_Pin | PA6_Pin , SET);
			light_hmode = RED_BLINK;
			setTimer1(25);
		}
		break;
	case RED_BLINK:
		if (timer1_flag == 1){
			HAL_GPIO_TogglePin(GPIOA, PA1_Pin);
			setTimer1(25);
		}
		if(state == MODE_3){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin |PA4_Pin | PA2_Pin| PA5_Pin|PA3_Pin | PA6_Pin , SET);
			light_hmode = YELLOW_BLINK;
			setTimer1(25);
		}
		if(state == MODE_1){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin |PA4_Pin | PA2_Pin| PA5_Pin|PA3_Pin | PA6_Pin , SET);
			light_hmode = RED;
			setTimer1(red_counter*1000);
		}
		break;
	case YELLOW_BLINK:
		if (timer1_flag == 1){
			HAL_GPIO_TogglePin(GPIOA, PA2_Pin);
			setTimer1(25);
		}
		if(state == MODE_4){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin |PA4_Pin | PA2_Pin| PA5_Pin|PA3_Pin | PA6_Pin , SET);
			light_hmode = GREEN_BLINK;
			setTimer1(25);
		}

		if(state == MODE_1){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin |PA4_Pin | PA2_Pin| PA5_Pin|PA3_Pin | PA6_Pin , SET);
			light_hmode = RED;
			setTimer1(red_counter*1000);
		}
		break;
	case GREEN_BLINK:
		if (timer1_flag == 1){
			HAL_GPIO_TogglePin(GPIOA, PA3_Pin);
			setTimer1(25);
		}
		if(state == MODE_1){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin |PA4_Pin | PA2_Pin| PA5_Pin|PA3_Pin | PA6_Pin , SET);
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
		if(state == MODE_2){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin |PA4_Pin | PA2_Pin| PA5_Pin|PA3_Pin | PA6_Pin , SET);

			light_vmode = RED_BLINK;
			setTimer2(25);
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
		if(state == MODE_2){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin |PA4_Pin | PA2_Pin| PA5_Pin|PA3_Pin | PA6_Pin , SET);

			light_vmode = RED_BLINK;
			setTimer2(25);
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
		if(state == MODE_2){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin |PA4_Pin | PA2_Pin| PA5_Pin|PA3_Pin | PA6_Pin , SET);
			light_vmode = RED_BLINK;
			setTimer2(25);
		}
		break;
	case RED_BLINK:
		if (timer2_flag == 1){
			HAL_GPIO_TogglePin(GPIOA, PA4_Pin);
			setTimer2(25);
		}
		if(state == MODE_3){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin |PA4_Pin | PA2_Pin| PA5_Pin|PA3_Pin | PA6_Pin , SET);
			light_vmode = YELLOW_BLINK;
			setTimer2(25);
		}

		if(state == MODE_1){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin |PA4_Pin | PA2_Pin| PA5_Pin|PA3_Pin | PA6_Pin , SET);
			light_vmode = GREEN;
			setTimer2(green_counter*1000);
		}
		break;
	case YELLOW_BLINK:
		if (timer2_flag == 1){
			HAL_GPIO_TogglePin(GPIOA, PA5_Pin);
			setTimer2(25);
		}
		if(state == MODE_4){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin |PA4_Pin | PA2_Pin| PA5_Pin|PA3_Pin | PA6_Pin , SET);
			light_vmode = GREEN_BLINK;
			setTimer2(25);
		}
		if(state == MODE_1){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin |PA4_Pin | PA2_Pin| PA5_Pin|PA3_Pin | PA6_Pin , SET);
			light_vmode = GREEN;
			setTimer2(green_counter*1000);
		}
		break;
	case GREEN_BLINK:
		if (timer2_flag == 1){
			HAL_GPIO_TogglePin(GPIOA, PA6_Pin);
			setTimer2(25);
		}
		if(state == MODE_1){
			HAL_GPIO_WritePin(GPIOA, PA1_Pin |PA4_Pin | PA2_Pin| PA5_Pin|PA3_Pin | PA6_Pin , SET);
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
			if(state == MODE_2){
				led_hmode = RED_BLINK;
				setTimer4(100);
			}
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
			if(state == MODE_2){
				led_hmode = RED_BLINK;
				setTimer4(100);
			}
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
			if(state == MODE_2){
				led_hmode = RED_BLINK;
				setTimer4(100);
			}
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
		case RED_BLINK:
			if(timer4_flag == 1){
				updateClockBuffer_horizontal(2);
				setTimer4(100);
			}
			if(state == MODE_3){
				led_hmode = YELLOW_BLINK;
				setTimer4(100);
			}
			if(state == MODE_1){
				led_hmode = RED;
				timer4_flag = 1;
				led_hred = red_counter;
			}
			break;
		case YELLOW_BLINK:
			if(timer4_flag == 1){
				updateClockBuffer_horizontal(3);
				setTimer4(100);
			}
			if(state == MODE_4){
				led_hmode = GREEN_BLINK;
				setTimer4(100);
			}

			if(state == MODE_1){
				led_hmode = RED;
				timer4_flag = 1;
				led_hred = red_counter;
			}
			break;
		case GREEN_BLINK:
			if(timer4_flag == 1){
				updateClockBuffer_horizontal(4);
				setTimer4(100);
			}
			if(state == MODE_1){
				led_hmode = RED;
				timer4_flag = 1;
				led_hred = red_counter;
			}
			break;
	}

	switch (led_vmode){
		case 0:
			led_vmode = GREEN;
			timer5_flag = 1;
			break;
		case GREEN:
			if(state == MODE_2){
				led_vmode = RED_BLINK;
				setTimer5(100);
			}
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
			if(state == MODE_2){
				led_vmode = RED_BLINK;
				setTimer5(100);
			}
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
			if(state == MODE_2){
				led_vmode = RED_BLINK;
				setTimer5(100);
			}
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
		case RED_BLINK:
			if(timer5_flag == 1){
				updateClockBuffer_vertical(red_change);
				setTimer5(100);
			}
			if(state == MODE_3){
				led_vmode = YELLOW_BLINK;
				setTimer5(100);
			}

			if(state == MODE_1){
				led_vmode = GREEN;
				timer5_flag = 1;
				led_vgreen = green_counter;
			}
			break;
		case YELLOW_BLINK:
			if(timer5_flag == 1){
				updateClockBuffer_vertical(yellow_change);
				setTimer5(100);
			}
			if(state == MODE_4){
				led_vmode = GREEN_BLINK;
				setTimer5(100);
			}

			if(state == MODE_1){
				led_vmode = GREEN;
				timer5_flag = 1;
				led_vgreen = green_counter;
			}
			break;
		case GREEN_BLINK:
			if(timer5_flag == 1){
				updateClockBuffer_vertical(green_change);
				setTimer5(100);
			}
			if(state == MODE_1){
				led_vmode = GREEN;
				timer5_flag = 1;
				led_vgreen = green_counter;
			}

			break;
	}
}




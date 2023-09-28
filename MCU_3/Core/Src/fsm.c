/*
 * fsm.c
 *
 *  Created on: Sep 26, 2023
 *      Author: Windows
 */

#include "fsm.h"

int state = 1;
void fsm_mode_run(){
	switch(state){
	case 0:
		state = MODE_1;
		break;
	case MODE_1:
		traffic_light_horizontal();
		traffic_light_vertical();
		led7seg_run();

		break;
	case MODE_2:
		break;
	case MODE_3:
		break;
	case MODE_4:
		break;
	}
}

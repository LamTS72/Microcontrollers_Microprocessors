/*
 * button.c
 *
 *  Created on: Sep 26, 2023
 *      Author: Windows
 */
#include "button.h"
#include "main.h"

int KeyReg0[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg1[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg2[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg3[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};

int MODE_flag = 0;
int INC_flag = 0;
int SET_flag = 0;

int TimerForKeyPress[3] = {200, 200, 200};

int isMODE_Pressed(){
	if(MODE_flag == 1){
		MODE_flag = 0;
		return 1;
	}
	return 0;
}

int isINC_Pressed(){
	if(INC_flag == 1){
		INC_flag = 0;
		return 1;
	}
	return 0;
}
int isSET_Pressed(){
	if(SET_flag == 1){
		SET_flag = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(int i){
	if( i == 0){
		MODE_flag = 1;
	}
	if(i == 1){
		INC_flag = 1;
	}
	if(i == 2){
		SET_flag = 1;
	}
}

void getKeyInput(){
	for (int i=0; i<3; i++){
			KeyReg0[i] = KeyReg1[i];
			KeyReg1[i] = KeyReg2[i];
			KeyReg2[i] = HAL_GPIO_ReadPin(GPIOA, (uint16_t)(0x01)<<(12+i));
			if ((KeyReg0[i] == KeyReg1[i]) && (KeyReg1[i] == KeyReg2[i])) {
				if (KeyReg3[i] != KeyReg2[i]){
					KeyReg3[i] = KeyReg2[i];
					if (KeyReg2[i] == PRESSED_STATE){
						subKeyProcess(i);
						TimerForKeyPress[i] = 200;
					}
				}
				else{
					TimerForKeyPress[i]--;
					if (TimerForKeyPress[i] ==0){
						KeyReg3[i] = NORMAL_STATE;
						//TimerForKeyPress[i] = 200;
					}
				}
			}
		}
}



/*
 * button.h
 *
 *  Created on: Sep 26, 2023
 *      Author: Windows
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_
#include "main.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET

extern int MODE_flag;
extern int INC_flag;
extern int SET_flag;

int isMODE_Pressed();
int isINC_Pressed();
int isSET_Pressed();

void getKeyInput();

#endif /* INC_BUTTON_H_ */

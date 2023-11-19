/*
 * software_timer.h
 *
 *  Created on: Sep 18, 2023
 *      Author: Windows
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer0_flag;
extern int timer1_flag;
extern int timer2_flag;

void setTimer0(int duration);
void setTimer1(int duration);
void setTimer2(int duration);



void timerRun();


#endif /* INC_SOFTWARE_TIMER_H_ */

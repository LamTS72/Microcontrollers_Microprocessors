/*
 * scheduler.h
 *
 *  Created on: Nov 6, 2023
 *      Author: Windows
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

void SCH_Init();
uint32_t SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
uint8_t SCH_Delete_Task(uint32_t taskID);

#endif /* INC_SCHEDULER_H_ */

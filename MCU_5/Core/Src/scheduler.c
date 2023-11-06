/*
 * scheduler.c
 *
 *  Created on: Nov 6, 2023
 *      Author: Windows
 */


#include "main.h"
#include "scheduler.h"

typedef struct {
	// Pointer to the task (must be a ’ void ( void ) ’ function )
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
} sTask;

//initialize array task with 30 elements
#define SCH_MAX_TASKS 30
#define NO_TASK_ID 0
sTask SCH_tasks_G[SCH_MAX_TASKS];

unsigned char Error_code_G = 0;
int numberOfTask = 0;

void SCH_Init(void) {
	Error_code_G = 0;
}



uint32_t SCH_Add_Task(void (*pFunction)(), unsigned int DELAY,unsigned int PERIOD) {
	if (numberOfTask == SCH_MAX_TASKS)
		return 0; //full

	unsigned char pivot = 0;

	while (1) {
		if (pivot == numberOfTask)
			break;
		if (DELAY < SCH_tasks_G[pivot].Delay)
			break;
		DELAY -= SCH_tasks_G[pivot].Delay;
		pivot++;
	}
	for (int i = numberOfTask; i > pivot; i--) {
		SCH_tasks_G[i] = SCH_tasks_G[i - 1];
	}
	if(pivot != numberOfTask)
		SCH_tasks_G[pivot+1].Delay -= DELAY;	//update delay for elements after pivot

	SCH_tasks_G[pivot].pTask = pFunction;
	SCH_tasks_G[pivot].Delay = DELAY;
	SCH_tasks_G[pivot].Period = PERIOD;
	SCH_tasks_G[pivot].RunMe = 0;
	numberOfTask++;
	return pivot;

}

void SCH_Update(void) {
	if(numberOfTask == 0) return; //empty

	unsigned char head = 0;
	if (SCH_tasks_G[head].pTask) {
		if (SCH_tasks_G[head].Delay == 0) {
			SCH_tasks_G[head].RunMe += 1;
		}
		else {
			SCH_tasks_G[head].Delay -= 1;
		}
	}

}

uint8_t SCH_Delete_Task(uint32_t taskID) {
	if (numberOfTask == 0) return 0; //empty
	for (int i = 0; i < numberOfTask - 1; i++) { //shift left array, last elements reset
		SCH_tasks_G[i] = SCH_tasks_G[i + 1];
	}
	numberOfTask--;
	SCH_tasks_G[numberOfTask].pTask = 0x0000;
	SCH_tasks_G[numberOfTask].Delay = 0;
	SCH_tasks_G[numberOfTask].Period = 0;
	SCH_tasks_G[numberOfTask].RunMe = 0;
	return 0;
}

void SCH_Dispatch_Tasks(void) {
	unsigned char head = 0;

	if (SCH_tasks_G[head].RunMe > 0) {
		(*SCH_tasks_G[head].pTask)(); // Run the task
		SCH_tasks_G[head].RunMe -= 1; // Reset / reduce RunMe flag
		if (SCH_tasks_G[head].Period == 0) {	//one shot task
			SCH_Delete_Task(head);
		} else {
			sTask temp = SCH_tasks_G[head];		//period task
			SCH_Delete_Task(head);
			SCH_Add_Task(temp.pTask, temp.Period, temp.Period);
		}
	}

}

//
// Created by Yusuf Sherif on 10/04/2021.
//

#include "ReRunMe.h"

void ReRunMe(void (*task_ptr)(), unsigned int delay, unsigned int priority){
	if(delay){
		Task t;
		initTask(&t, delay, task_ptr, priority);
		QueDelayedTask(&delayedQueue, t);
	} else {
		QueTask(&readyQueue,task_ptr,priority);
	}
}
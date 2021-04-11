//
// Created by Yusuf Sherif on 10/04/2021.
//

#include "Header.h"

extern ReadyQueue readyQueue;
extern DelayedQueue delayedQueue;

void ReRunMe(void (*task_ptr)(), unsigned int delay, unsigned int priority){
	if(delay){
		volatile Task t;
		initTask(&t, delay, task_ptr, priority);
		QueDelayedTask(&delayedQueue, t);
	} else {
		QueTask(&readyQueue,task_ptr,priority);
	}
}
void Init(void) {

	initQueue(&readyQueue, 5);
	initDelayedQueue(&delayedQueue,10);
	
}

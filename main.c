#include <stdio.h>
#include <time.h>
#include "Header.h"

void task() {
	printf("%li\n", time(NULL));
}

void taskDelayed() {
	printf("Delayed, %li\n", time(NULL));
}

int main() {
	initQueue(&readyQueue, 3);
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 5; ++j) {
			QueTask(&readyQueue, &task, i);
		}
	}
	initDelayedQueue(&delayedQueue,10);
	for (int i = 0; i < 8; ++i) {
		Task t;
		t.priority=1;
		t.task_ptr = &taskDelayed;
		t.delay=i;
		QueDelayedTask(&delayedQueue,t);
	}

	while (1) {
		Dispatch(&readyQueue);
		DispatchDelayed(&delayedQueue,&readyQueue);
	}

//	Init(); // initialize the scheduler data structures
//	QueTask(TaskA);
//	while (TRUE) {
//		Dispatch();
//	}
	return 0;
}

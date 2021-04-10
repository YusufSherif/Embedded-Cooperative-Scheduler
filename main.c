#include <stdio.h>
#include <time.h>
#include "ReadyQueue.h"
#include "DelayedQueue.h"

void task() {
	printf("%li\n", time(NULL));
}

void taskDelayed() {
	printf("Delayed, %li\n", time(NULL));
}

int main() {
	ReadyQueue q;
	DelayedQueue dq;
	initQueue(&q, 3);
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 5; ++j) {
			QueTask(&q, &task, i);
		}
	}
	initDelayedQueue(&dq,10);
	for (int i = 0; i < 8; ++i) {
		Task t;
		t.priority=1;
		t.task_ptr = &taskDelayed;
		t.delay=i;
		QueDelayedTask(&dq,t);
	}

	while (1) {
		Dispatch(&q);
		DispatchDelayed(&dq,&q);
	}

//	Init(); // initialize the scheduler data structures
//	QueTask(TaskA);
//	while (TRUE) {
//		Dispatch();
//	}
	return 0;
}

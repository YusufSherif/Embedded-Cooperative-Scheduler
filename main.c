#include <stdio.h>
#include <time.h>
#include "Queue.h"

void task() {
	printf("%li\n", time(NULL));
}

int main() {
	Queue q;
	initQueue(&q, 5);
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 5; ++j) {
			QueTask(&q, &task, i);
		}
	}

	while (1) {
		Dispatch(&q);
	}

//	Init(); // initialize the scheduler data structures
//	QueTask(TaskA);
//	while (TRUE) {
//		Dispatch();
//	}
	return 0;
}

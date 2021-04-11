#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "Header.h"

DelayedQueue delayedQueue;
ReadyQueue readyQueue;

void task() {
	printf("Task: Ready, %li\n", time(NULL));
}

void taskDelayed() {
	printf("Task: Delayed, %li\n", time(NULL));
}

void printRQStatus(){
	printf("********************************\n");
	printf("Queue Status:\n");
	for (int i = 0; i < PRIORITY_LEVELS; ++i) {
		printf("Queue for priority %i:\n", i);
		printf("Queue capacity: %u\n",readyQueue.capacity[i]);
		printf("Queue size: %u\n",readyQueue.size[i]);
		printf("Queue front: %u\n",readyQueue.front[i]);
		printf("Queue rear: %u\n",readyQueue.rear[i]);
		printf("Queue array:\nPointers: ", i);
		for (volatile unsigned int j = 0; j < readyQueue.capacity[i]; ++j) {
			printf("%u,", readyQueue.q[i][j]);
		}
		printf("\n---------------------\n");
	}
	printf("********************************\n\n");
}

int main() {
	Init();
	printf("Queue Initial Status.\n");
	printRQStatus();
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 5; ++j) {
			QueTask(&readyQueue, &task, i);
		}
	}
	printf("Filled Queue using 5 tasks for each priority up to priority 6.\n");
	printRQStatus();

	for (int i = 0; i < 35; ++i) {
		printf("Queue Status before Dispatch");
		printRQStatus();
		Dispatch(&readyQueue);
		printf("Queue Status after Dispatch");
		printRQStatus();
	}

	printf("Testing on sub-queue 7:\n");
	printf("Testing Initial conditions:\n");
	assert(readyQueue.capacity[7]==3);
	assert(readyQueue.size[7]==0);
	assert(readyQueue.front[7]==0);
	assert(readyQueue.rear[7]==0);
	printf("Initial conditions test passed\n");
	printf("Testing on queue insertion\n");
	for (int i = 0; i < 3; ++i) {
		QueTask(&readyQueue, &task, 7);
	}
	assert(readyQueue.capacity[7]==3);
	assert(readyQueue.size[7]==3);
	assert(readyQueue.front[7]==0);
	assert(readyQueue.rear[7]==3);
	printf("Insertion to queues test passed\n");
	printf("Adding another task to test for expansion\n");

	QueTask(&readyQueue, &task, 7);
	assert(readyQueue.size[7]==4);
	assert(readyQueue.front[7]==0);
	assert(readyQueue.rear[7]==4);
	assert(readyQueue.capacity[7]==8);
	printf("Insertion to queues with expansion test passed\n");

	printf("Dispatching a task\n");
	Dispatch(&readyQueue);
	assert(readyQueue.size[7]==3);
	assert(readyQueue.front[7]==1);
	assert(readyQueue.rear[7]==4);
	assert(readyQueue.capacity[7]==8);
	printf("Dispatching test passed\n");

	printf("Adding task to queue\n");
	QueTask(&readyQueue,&task,7);
	assert(readyQueue.size[7]==4);
	assert(readyQueue.front[7]==1);
	assert(readyQueue.rear[7]==5);
	assert(readyQueue.capacity[7]==8);
	printf("Queuing test passed\n");

	printf("Filling queue to capacity\n");
	for (int i = 0; i < 4; ++i) {
		QueTask(&readyQueue,&task,7);
	}
	assert(readyQueue.size[7]==8);
	assert(readyQueue.front[7]==1);
	assert(readyQueue.rear[7]==1);
	assert(readyQueue.capacity[7]==8);
	printf("Filling test passed\n");

	printf("Adding task to queue to test for expansion\n");
	QueTask(&readyQueue,&task,7);
	assert(readyQueue.size[7]==9);
	assert(readyQueue.front[7]==6);
	assert(readyQueue.rear[7]==2);
	assert(readyQueue.capacity[7]==13);
	printf("Expansion test with non-uniform front and rear passed\n");

	printf("Filling queue to capacity\n");
	for (int i = 0; i < 4; ++i) {
		QueTask(&readyQueue,&task,7);
	}
	assert(readyQueue.size[7]==13);
	assert(readyQueue.front[7]==6);
	assert(readyQueue.rear[7]==6);
	assert(readyQueue.capacity[7]==13);
	printf("Filling test passed\n");

	printf("Emptying Queue\n");
	unsigned int size = readyQueue.size[7];
	for (int i = 0; i < size; ++i) {
		Dispatch(&readyQueue);
	}
	assert(readyQueue.size[7]==0);
	assert(readyQueue.front[7]==6);
	assert(readyQueue.rear[7]==6);
	assert(readyQueue.capacity[7]==13);
	printf("Emptying queue test passed\n");

	printf("Filling queue\n");
	for (int i = 0; i < 4; ++i) {
		QueTask(&readyQueue,&task,7);
	}
	assert(readyQueue.size[7]==4);
	assert(readyQueue.front[7]==6);
	assert(readyQueue.rear[7]==10);
	assert(readyQueue.capacity[7]==13);
	printf("Filling test passed\n");

	printf("Emptying Queue\n");
	size = readyQueue.size[7];
	for (int i = 0; i < size; ++i) {
		Dispatch(&readyQueue);
	}
	assert(readyQueue.size[7]==0);
	assert(readyQueue.front[7]==10);
	assert(readyQueue.rear[7]==10);
	assert(readyQueue.capacity[7]==13);
	printf("Emptying queue test passed\n");


	//0 1 2 3 4 5 6 7 8 9 10 11 12






//	Init(); // initialize the scheduler data structures
//	QueTask(TaskA);
//	while (TRUE) {
//		Dispatch();
//	}
	return 0;
}

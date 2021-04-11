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

void printDQStatus(){
	printf("********************************\n");
	printf("Queue Status:\n");
	printf("Queue capacity: %u\n",delayedQueue.capacity);
	printf("Queue size: %u\n",delayedQueue.size);
	printf("Queue array:\nPointers: ");
	for (volatile unsigned int j = 0; j < delayedQueue.capacity; ++j) {
		printf("%u,", readyQueue.q[j]);
	}
	printf("\n---------------------\n");
	printf("********************************\n\n");
}

int main() {
	Init();
	printf("Queue Initial Status.\n");
	printDQStatus();
	printf("Testing Initial conditions:\n");
	assert(delayedQueue.capacity==10);
	assert(delayedQueue.size==0);
	printf("Initial conditions test passed\n");
	printf("Testing Insertion:\n");
	for (int j = 0; j < 5; ++j) {
		Task t;
		t.priority=4-j;
		t.task_ptr = &taskDelayed;
		t.delay=j;
		QueDelayedTask(&delayedQueue,t);
	}
	printf("Filled Queue using 5 tasks.\n");

	for (int i = 0; i < delayedQueue.size-1; ++i) {
		assert(delayedQueue.q[i].delay>=delayedQueue.q[i+1].delay);
	}
	assert(delayedQueue.capacity==10);
	assert(delayedQueue.size==5);
	printf("Insertion test passed, checked for descending order\n");

	printf("Dispatching tasks test\n");
	unsigned int size = delayedQueue.size;
	for (int i = 0; i < size; ++i) {
		printf("Queue Status before Dispatch");
		printDQStatus();
		DispatchDelayed(&delayedQueue,&readyQueue);
		printf("Queue Status after Dispatch");
		printDQStatus();
	}
	assert(delayedQueue.capacity==10);
	assert(delayedQueue.size==0);
	printf("Dispatching tasks test passed\n");

	printf("Filling queue to capacity:\n");
	for (int j = 0, i = 0; j < 10; ++j) {
		Task t;
		if(i!=7) i++;
		t.priority=i;
		t.task_ptr = &taskDelayed;
		t.delay=j;
		QueDelayedTask(&delayedQueue,t);
	}
	printf("Filled Queue using 10 tasks.\n");
	size = delayedQueue.size;
	for (int i = 0; i < size-1; ++i) {
		assert(delayedQueue.q[i].delay>=delayedQueue.q[i+1].delay);
	}
	assert(delayedQueue.capacity==10);
	assert(delayedQueue.size==10);
	printf("Filling test passed.\n");

	printf("Adding one task for expansion:\n");
	for (int j = 0; j < 1; ++j) {
		Task t;
		t.priority=6-j;
		t.task_ptr = &taskDelayed;
		t.delay=j;
		QueDelayedTask(&delayedQueue,t);
	}
	printf("Expansion test passed.\n");

	size = delayedQueue.size;
	for (int i = 0; i < size-1; ++i) {
		assert(delayedQueue.q[i].delay>=delayedQueue.q[i+1].delay);
	}
	assert(delayedQueue.capacity==10+DELAYED_EXPANSION_SIZE);
	assert(delayedQueue.size==11);
	printf("Expansion test passed.\n");

	printf("Dispatching tasks test\n");
	size = delayedQueue.size;
	for (int i = 0; i < size; ++i) {
		DispatchDelayed(&delayedQueue,&readyQueue);
	}
	assert(delayedQueue.capacity==10+DELAYED_EXPANSION_SIZE);
	assert(delayedQueue.size==0);
	printf("Dispatching tasks test passed\n");

	printf("Filling queue:\n");
	for (int j = 0, i = 0; j < 10; ++j) {
		Task t;
		if(i!=7) i++;
		t.priority=i;
		t.task_ptr = &taskDelayed;
		t.delay=j;
		QueDelayedTask(&delayedQueue,t);
	}
	printf("Filled Queue using 10 tasks.\n");
	size = delayedQueue.size;
	for (int i = 0; i < size-1; ++i) {
		assert(delayedQueue.q[i].delay>=delayedQueue.q[i+1].delay);
	}
	assert(delayedQueue.capacity==10+DELAYED_EXPANSION_SIZE);
	assert(delayedQueue.size==10);
	printf("Filling test passed.\n");

	return 0;
}

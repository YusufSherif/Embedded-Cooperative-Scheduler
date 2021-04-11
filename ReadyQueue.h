//
// Created by Yusuf Sherif on 09/04/2021.
//

#ifndef ES_PROJECT_1__READYQUEUE_H_
#define ES_PROJECT_1__READYQUEUE_H_
#include <stdlib.h>

#define READY_EXPANSION_SIZE 5
#define PRIORITY_LEVELS 8

typedef struct ReadyQueue {
	void (**q[PRIORITY_LEVELS])();
	volatile unsigned int capacity[PRIORITY_LEVELS];
	volatile unsigned int size[PRIORITY_LEVELS];
	volatile unsigned int front[PRIORITY_LEVELS];
	volatile unsigned int rear[PRIORITY_LEVELS];
} ReadyQueue;

void initQueue(ReadyQueue* q, unsigned int size);
unsigned int expandQueue(ReadyQueue* q, unsigned int priority);
unsigned int QueTask(ReadyQueue* q, void (*task_ptr)(), unsigned int priority);
void Dispatch(ReadyQueue* q);
unsigned int isQueueFull(ReadyQueue* q, unsigned int priority);
void destructQueue(ReadyQueue* q);

#endif //ES_PROJECT_1__READYQUEUE_H_

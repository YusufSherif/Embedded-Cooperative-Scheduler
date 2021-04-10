//
// Created by Yusuf Sherif on 09/04/2021.
//

#ifndef ES_PROJECT_1__READYQUEUE_H_
#define ES_PROJECT_1__READYQUEUE_H_
#include <stdlib.h>

#define READY_EXPANSION_SIZE 2
#define PRIORITY_LEVELS 8

typedef struct ReadyQueue {
	void (**q[PRIORITY_LEVELS])();
	unsigned int capacity[PRIORITY_LEVELS];
	unsigned int size[PRIORITY_LEVELS];
	unsigned int front[PRIORITY_LEVELS];
	unsigned int rear[PRIORITY_LEVELS];
} ReadyQueue;

void initQueue(ReadyQueue* q, unsigned int size);
unsigned int expandQueue(ReadyQueue* q, unsigned int priority);
unsigned int QueTask(ReadyQueue* q, void (*task_ptr)(), unsigned int priority);
void Dispatch(ReadyQueue* q);
unsigned int isQueueFull(ReadyQueue* q, unsigned int priority);
void destructQueue(ReadyQueue* q);

ReadyQueue readyQueue;

#endif //ES_PROJECT_1__READYQUEUE_H_

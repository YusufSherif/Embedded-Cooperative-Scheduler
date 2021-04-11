//
// Created by Yusuf Sherif on 09/04/2021.
//

#ifndef ES_PROJECT_1__DELAYEDQUEUE_H_
#define ES_PROJECT_1__DELAYEDQUEUE_H_
#include "Task.h"
#include <stdlib.h>
#include "ReadyQueue.h"

#define DELAYED_EXPANSION_SIZE 2

typedef struct DelayedQueue {
	Task *q;
	volatile unsigned int capacity;
	volatile unsigned int size;
} DelayedQueue;

void initDelayedQueue(DelayedQueue* q, unsigned int size);
unsigned int expandDelayedQueue(DelayedQueue* q);
unsigned int QueDelayedTask(DelayedQueue* q, volatile Task task);
void DispatchDelayed(DelayedQueue* q, ReadyQueue* rq);
unsigned int isDelayedQueueFull(DelayedQueue* q);
void destructDelayedQueue(DelayedQueue* q);

#endif //ES_PROJECT_1__DELAYEDQUEUE_H_

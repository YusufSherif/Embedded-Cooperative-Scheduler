//
// Created by Yusuf Sherif on 09/04/2021.
//

#ifndef ES_PROJECT_1__QUEUE_H_
#define ES_PROJECT_1__QUEUE_H_

#define EXPANSION_SIZE 5
#define PRIORITY_LEVELS 8

typedef struct Queue {
	void (**q[PRIORITY_LEVELS])();
	unsigned int sizes[PRIORITY_LEVELS];
	unsigned int lengths[PRIORITY_LEVELS];
} Queue;

void initQueue(Queue* q, unsigned int size);
unsigned int expandQueue(Queue* q, unsigned int priority);
unsigned QueTask(Queue* q, void (*task_ptr)(), unsigned int priority);
void Dispatch(Queue* q);
void destructQueue(Queue* q);
#endif //ES_PROJECT_1__QUEUE_H_

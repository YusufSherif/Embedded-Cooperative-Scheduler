//
// Created by Yusuf Sherif on 09/04/2021.
//

#include "DelayedQueue.h"

void initDelayedQueue(DelayedQueue *q, unsigned int size) {
	q->q = calloc(size, sizeof(Task));
	q->capacity = size;
	q->size = 0;
}

unsigned int expandDelayedQueue(DelayedQueue *q) {
	unsigned int expanded_size = q->capacity + DELAYED_EXPANSION_SIZE;
	Task* temp = realloc(q->q, sizeof(q->q[0]) * expanded_size);
	if (temp) {
		q->q = temp;
		q->capacity = expanded_size;
		return 1;
	}
	return 0;
}

unsigned int QueDelayedTask(DelayedQueue *q, Task task) {
	if (isDelayedQueueFull(q)) {
		if (!expandDelayedQueue(q))
			return 0;
	}

	int insertIndex = 0;
	for (insertIndex = 0; insertIndex < q->size; ++insertIndex) {
		if(q->q[insertIndex].delay<task.delay){
			break;
		}
	}
	if(insertIndex!=q->size) {
		for (unsigned int i = q->size; i > insertIndex; i--) {
			q->q[i] = q->q[i-1];
		}
		//memcpy(&(q->q[insertIndex + 1]), &(q->q[insertIndex]), q->size - insertIndex);
	}
	q->q[insertIndex] = task;
	q->size++;

	return 1;
}

void DispatchDelayed(DelayedQueue *q, ReadyQueue *rq) {
	if (q->size > 0) {
		for (int i = q->size-1; i >= 0; i--) {
			volatile Task *tsk = &q->q[i];
			if(!(tsk->delay)){
				QueTask(rq,tsk->task_ptr,tsk->priority);
				q->size--;
			}
			tsk->delay--;
		}
	}
}

unsigned int isDelayedQueueFull(DelayedQueue *q) {
	return q->size == q->capacity;
}

void destructDelayedQueue(DelayedQueue *q) {
	free(q->q);
}

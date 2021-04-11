//
// Created by Yusuf Sherif on 09/04/2021.
//

#include "ReadyQueue.h"

void initQueue(ReadyQueue* q, volatile unsigned int size){
	void (*task_ptr)();
	for (int i = 0; i < PRIORITY_LEVELS; ++i) {
		q->q[i] = calloc(size, sizeof(task_ptr));
		q->capacity[i] = size;
		q->size[i] = 0;
		q->front[i] = 0;
		q->rear[i] = 0;
	}
}

unsigned int expandQueue(ReadyQueue* q, volatile unsigned int priority){
	volatile unsigned int expanded_size = q->capacity[priority]+READY_EXPANSION_SIZE;
	void (**temp)() = realloc(q->q[priority],sizeof(q->q[priority][0])*expanded_size);
	if(temp) {
		q->q[priority] = temp;

		if(q->rear[priority]<=q->front[priority]) {
//			unsigned end = q->rear[priority]<READY_EXPANSION_SIZE ? q->rear[priority] : READY_EXPANSION_SIZE;
//			for (unsigned i = 0, j = q->capacity[priority]; i < end; ++i, j++) {
//				q->q[priority][j] = q->q[priority][i];
//				q->q[priority][i] = 0;
//			}

//			int newRear = (int)(q->rear[priority])-(READY_EXPANSION_SIZE);
//			if(newRear<0) newRear = (int)(q->capacity[priority])+READY_EXPANSION_SIZE+newRear;

//			for (unsigned i = READY_EXPANSION_SIZE, j=0; i < q->rear[priority]; ++i, j++) {
//				q->q[priority][j] = q->q[priority][i];
//				q->q[priority][i] = 0;
//			}
//			q->rear[priority] = newRear;
			for (unsigned int i = expanded_size - 1, j = q->front[priority]+q->capacity[priority]-q->rear[priority]-1; /*i >= q->capacity[priority] &&*/ j >= q->front[priority]; i--, j--){
				q->q[priority][i] = q->q[priority][j];
				q->q[priority][j] = 0;
			}
			q->front[priority]+=READY_EXPANSION_SIZE;

		}

		q->capacity[priority] = expanded_size;

		return 1;
	}
	return 0;
}

unsigned int QueTask(ReadyQueue* q, volatile void (*task_ptr)(), volatile unsigned int priority){
	if(isQueueFull(q,priority)){
		if(!expandQueue(q,priority))
			return 0;
	}

	if(q->rear[priority]!=q->capacity[priority]){
		q->q[priority][q->rear[priority]]= task_ptr;
	} else {
		q->rear[priority] = 0;
		q->q[priority][q->rear[priority]]= task_ptr;
	}
		q->size[priority]++;
		q->rear[priority]++;
	return  1;
}

void Dispatch(ReadyQueue* q) {
	for (int i = 0; i < PRIORITY_LEVELS; ++i) {
		if(q->size[i]>0) {
			void (*function) ();
			function = q->q[i][q->front[i]];
			function();
			q->q[i][q->front[i]] = 0;
			q->front[i]++;
			if(q->front[i]==q->capacity[i]) q->front[i] = 0;
			q->size[i]--;
			break;
		}
	}
}

unsigned int isQueueFull(ReadyQueue* q, volatile unsigned int priority) {
	return q->size[priority]==q->capacity[priority];
}

void destructQueue(ReadyQueue* q) {
	for (int i = 0; i < PRIORITY_LEVELS; ++i) {
		free(q->q[i]);
	}
}

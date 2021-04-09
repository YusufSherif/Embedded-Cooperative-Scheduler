//
// Created by Yusuf Sherif on 09/04/2021.
//

#include <stdlib.h>
#include "Queue.h"
#include "Task.h"

void initQueue(Queue* q, unsigned int size){
	void (*task_ptr)();
	for (int i = 0; i < PRIORITY_LEVELS; ++i) {
		q->q[i] = calloc(size, sizeof(task_ptr));
		q->sizes[i] = size;
		q->lengths[i] = 0;
	}
}

unsigned int expandQueue(Queue* q, unsigned int priority){
	unsigned int expanded_size = q->sizes[priority]+EXPANSION_SIZE;
	void (**temp)() = realloc(q->q[priority],expanded_size);
	if(temp) {
		q->q[priority] = temp;
		q->sizes[priority] = expanded_size;
		return 1;
	}
	return 0;
}

unsigned QueTask(Queue* q, void (*task_ptr)(), unsigned int priority){
	if(q->lengths[priority]==q->sizes[priority]){
		if(!expandQueue(q,priority))
			return 0;
	}

	q->q[priority][q->lengths[priority]]= task_ptr;
	q->lengths[priority]++;
	return  1;
}

void Dispatch(Queue* q){
	for (int i = 0; i < PRIORITY_LEVELS; ++i) {
		if(q->lengths[i]>0) {
			void (*function) ();
			function = q->q[i][0];
			function();
			for (int j = 1; j < q->lengths[i]-1; ++j) {
				q->q[i][j-1] = q->q[i][j];
			}
			q->q[i][q->lengths[i]-1] = 0;
			q->lengths[i]--;
			break;
		}
	}
}

void destructQueue(Queue* q){
	for (int i = 0; i < PRIORITY_LEVELS; ++i) {
		free(q->q[i]);
	}
}
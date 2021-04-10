//
// Created by Yusuf Sherif on 09/04/2021.
//

#ifndef ES_PROJECT_1__TASK_H_
#define ES_PROJECT_1__TASK_H_

typedef struct Task {
	void (*task_ptr)();
	unsigned int delay;
	unsigned int priority;
} Task;

void initTask(Task* task, unsigned int delay, void (*p_task_ptr)(), unsigned int p_priority);

#endif //ES_PROJECT_1__TASK_H_

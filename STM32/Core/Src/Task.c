//
// Created by Yusuf Sherif on 09/04/2021.
//

#include "Task.h"

void initTask(Task* task, unsigned int delay, void (*p_task_ptr)(), unsigned int p_priority){
	task->task_ptr = p_task_ptr;
	task->delay = delay;
	task->priority = p_priority;
}
//
// Created by Yusuf Sherif on 10/04/2021.
//

#ifndef ES_PROJECT_1__HEADER_H_
#define ES_PROJECT_1__HEADER_H_
#include "Task.h"
#include "DelayedQueue.h"
#include "ReadyQueue.h"

void ReRunMe(void (*task_ptr)(), unsigned int delay, unsigned int priority);
void Init(void);
#endif //ES_PROJECT_1__HEADER_H_

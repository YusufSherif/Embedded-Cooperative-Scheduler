# Embedded-Cooperative-Scheduler

This project features a simple cooperative scheduler running on an STM32L432KC chip with 2 demo programs. This cooperative scheduler supports 8 priorities. For the purposes of a quick overview, the cooperative scheduler does not preempt processes, rather each task releases the CPU after finishing execution and the scheduler decides which one to run. The Scheduler is implemented through two main classes ReadyQueue & DelayedQueue. ReadyQueue is the queue holding all ready tasks, the delayed queue holds all tasks that are yet to be ready. Implementation details are described below.

## ReadyQueue:

The ready queue is internally implemented as a 2D array where each row represents the array of queued tasks for a certain priority. Each of these arrays is implemented as a circular queue to optimize operations during insertion and dequeuing. Described below are the APIs to interact with this data structure.

* void initQueue(ReadyQueue* q, volatile unsigned int size); -> Initializes the queue; sets all struct members to zeros and dynamically allocates the priority arrays.
* unsigned int expandQueue(ReadyQueue* q, volatile unsigned int priority); -> Expands the array with the index of the priority passed to the function. Only called when attempting to enqueue a task into the queue.
* unsigned int QueTask(ReadyQueue* q, volatile void (*task_ptr)(), volatile unsigned int priority); -> Queues a task with a certain priority.
* void Dispatch(ReadyQueue* q); -> Runs and dequeues the task with the highest priority and has arrived the earliest if more than one task with the same priorities exists. If the queue is empty, no action is taken.
* unsigned int isQueueFull(ReadyQueue* q, volatile unsigned int priority); -> Checks if the queue at a certain priority is full. Called to determine whether to expand the queue or not.
* void destructQueue(ReadyQueue* q); -> Cleans up all dynamically allocated arrays created in the initQueue function.


## DelayedQueue:

The DelayedQueue data structure is implemented as a sorted 1D array. During insertion the array is resorted to maintain the order. Tasks with lower delays will always be at the head of the queue to be dispatched when the dispatch function is called. The dispatch function dequeues the first task with no delay left and enqueues it into the ready queue. Described below are the APIs to interact with this data structure.

* void initDelayedQueue(DelayedQueue* q, unsigned int size); -> Initializes the queue; sets all struct members to zeros and dynamically allocates the array holding the queued tasks.
* unsigned int expandDelayedQueue(DelayedQueue* q); -> Expands the array. Only called when attempting to enqueue a task into the queue.
* unsigned int QueDelayedTask(DelayedQueue* q, volatile Task task); -> Queues task into the array. If a task is to be enqueued while an already existing task has the same delay at the time of insertion, the older task takes priority. This function maintains descending order of tasks based on the delay value.
* void DispatchDelayed(DelayedQueue* q, ReadyQueue* rq); -> Dispatches tasks with zero delay to the ready queue and decrements the delays of all tasks remaining in the queue by 1.
* unsigned int isDelayedQueueFull(DelayedQueue* q); -> Checks if the queue is full. Called to determine whether to expand the queue or not.
* void destructDelayedQueue(DelayedQueue* q); -> Cleans up the dynamically allocated array created in the initQueue function.

## Sample applications:

* Ambient temperature monitor: For that sample application we have found that we do not have an actual temperature sensor in our toolkit, which is why we had to improvise. We have decided that we will use a potentiometer as a temperature sensor simulator. In other words, if the potentiometer passes a voltage value that is higher than a certain threshold that we have set beforehand, it will trigger an alarm to go off. The setup to this system is that we connected the middle pin of our potentiometer to a gpio input pin on our nucleoboard, the microcontroller evaluates the value received and takes an action based upon that. If the value exceeds a certain threshold, the gpio output pin is set to 1, thus toggling an LED. We have named that task as taskB and the interval between everytime the temperature is read can be set inside the reRunMe function. 

* Parking sensor: For that sample application we used the active beeper and the ultrasonic monitor. For that experiment, we connected a GPIO output pin to the sensor to send a trigger wave to signal the start of the detection signal. We then connected a GPIO input pin to the ECHO pin to receive the signal. The difficult part here was that the ECHO pin transmits a wave not a value. Which is why we needed to calculate the time in which the ECHO pin was set to 1, then making other calculations to turn the time signal into a distance. We can also note that the sensor is not that accurate, meaning that it sometimes starts echoing before setting the trigger pin to 0 and that it does not calculate the distance precisely. 
  * Pictures of the experiment: https://drive.google.com/file/d/1lO_Seca9FWIK4PvMzzLz6ITA9YR9HDtq/view?usp=sharing 
    https://drive.google.com/file/d/1lBRZIcHpf6pCezvhPyBe5lHdr7O20G2Y/view?usp=sharing 
  * Video: https://drive.google.com/file/d/1IGHnN6GUlTuvRhSzse0y4LGea4aO8wAy/view?usp=sharing 

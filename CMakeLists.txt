cmake_minimum_required(VERSION 3.17)
project(ES_Project_1 C)

set(CMAKE_C_STANDARD 99)

add_executable(ES_Project_1 main.c ReadyQueue.c DelayedQueue.c DelayedQueue.h ReadyQueue.h Task.c Task.h Header.c Header.h)
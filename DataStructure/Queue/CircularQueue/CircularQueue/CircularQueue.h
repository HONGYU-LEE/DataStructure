#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int DataType;
typedef struct {
	DataType* queue;
	int front;
	int rear;
	int length;
} CircularQueue;

CircularQueue* CircularQueueCreate(int k);
//循环队列初始化
bool CircularQueueEnQueue(CircularQueue* obj, DataType value);
//循环队列入队
bool myCircularQueueDeQueue(CircularQueue* obj);
//循环队列出队
DataType CircularQueueFront(CircularQueue* obj);
//获取循环队列队首
DataType CircularQueueRear(CircularQueue* obj);
//获取循环队列队尾
int CircularQueueSize(CircularQueue* obj);
//循环队列长度
bool CircularQueueIsEmpty(CircularQueue* obj);
//判断循环队列是否为空
bool CircularQueueIsFull(CircularQueue* obj);
//判断循环队列是否已满
void CircularQueueFree(CircularQueue* obj);
//销毁循环队列
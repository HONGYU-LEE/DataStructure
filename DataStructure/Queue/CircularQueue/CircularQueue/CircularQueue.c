#include "CircularQueue.h"

CircularQueue* CircularQueueCreate(int k) 
{

	CircularQueue* cq = (CircularQueue*)malloc(sizeof(CircularQueue));
	cq->queue = (DataType*)malloc((k + 1) * sizeof(DataType));
	cq->front = 0;
	cq->rear = 0;
	cq->length = k + 1;
	return cq;
}

bool CircularQueueEnQueue(CircularQueue* obj, DataType value) 
{
	if ((obj->rear + 1) % obj->length == obj->front)
		return false;
	obj->queue[obj->rear++] = value;
	if (obj->rear == obj->length)
		obj->rear = 0;

	return true;
}

bool myCircularQueueDeQueue(CircularQueue* obj) 
{
	if (obj->front == obj->rear)
		return false;;

	++obj->front;
	if (obj->front == obj->length)
		obj->front = 0;
	return true;
}

DataType CircularQueueFront(CircularQueue* obj) 
{
	if (obj->front == obj->rear)
		return -1;
	else
		return obj->queue[obj->front];
}

DataType CircularQueueRear(CircularQueue* obj) 
{
	if (obj->front == obj->rear)
		return -1;
	else if (obj->rear == 0)
		return obj->queue[obj->length - 1];
	else
		return obj->queue[obj->rear - 1];
}

int CircularQueueSize(CircularQueue* obj)
{
	return (obj->rear - obj -> front + obj->length) % obj->length;
}

bool CircularQueueIsEmpty(CircularQueue* obj) 
{
	if (obj->rear == obj->front)
		return true;
	else
		return false;
}

bool CircularQueueIsFull(CircularQueue* obj) 
{
	if ((obj->rear + 1) % obj->length == obj->front)
		return true;
	else
		return false;
}

void CircularQueueFree(CircularQueue* obj) 
{
	free(obj->queue);
	obj->queue = NULL;
	free(obj);
	obj = NULL;
}
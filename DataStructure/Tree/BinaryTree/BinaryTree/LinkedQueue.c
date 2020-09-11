#include "BinaryTree.h"
#include "LinkedQueue.h"

void QueueInit(Queue* q)
{
	q->front = q->rear = NULL;
}

DataType QueueFront(Queue* q)
{
	assert(q);
	return q->front->val;
}

DataType QueueBack(Queue* q)
{
	assert(q);
	return q->rear->val;
}

int QueueEmpty(Queue* q)
{
	return q->front ? 0 : 1;
}


int QueueSize(Queue* q)
{
	assert(q);

	QNode* cur = q->front;
	int count = 0;

	while (cur)
	{
		count++;
		cur = cur->next;
	}

	return count;
}

void QueuePush(Queue* q, DataType val)
{
	assert(q);

	QNode* node = (QNode*)malloc(sizeof(QNode));
	node->val = val;
	node->next = NULL;

	if (q->rear)
	{
		q->rear->next = node;
		q->rear = node;
	}
	else
	{
		q->front = q->rear = node;
	}

} 

void QueuePop(Queue* q)
{
	assert(q);

	if (NULL == q->front->next)
	{
		free(q->front);
		q->front = q->rear = NULL;
	}
	else
	{
		QNode* next = q->front->next;
		free(q->front);
		q->front = next;
	}
}

void QueueDestroy(Queue* q)
{
	assert(q);

	QNode* cur = q->front;
	while (cur)
	{
		QNode* next = cur->next;
		free(cur);
		cur = next;
	}

	q->front = q->rear = NULL;
}

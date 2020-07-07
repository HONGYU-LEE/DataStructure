#pragma once
#include"LinkedQueue.h"

test()
{
	Queue q;
	QueueInit(&q);

	QueuePush(&q, 1);
	printf("%d ", QueueBack(&q));
	QueuePush(&q, 2);
	printf("%d ", QueueBack(&q));
	QueuePush(&q, 3);
	printf("%d ", QueueBack(&q));
	QueuePush(&q, 4);
	printf("%d\n ", QueueBack(&q));

	printf("队列元素数量为：%d", QueueSize(&q));
}

int main()
{
	test();
	return 0;
}
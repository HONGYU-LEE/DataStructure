#include "CircularQueue.h"


int main()
{
	CircularQueue *cq = CircularQueueCreate(30);
	CircularQueueEnQueue(cq, 1);
	CircularQueueEnQueue(cq, 2);
	printf("%d %d", CircularQueueFront(cq), CircularQueueRear(cq));
	printf("%d", CircularQueueSize(cq));
	return 0;
}
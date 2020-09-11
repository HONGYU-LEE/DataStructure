#include "Heap.h"

void Swap(DataType* a, DataType* b)
{
	DataType temp = *a;
	*a = *b;
	*b = temp;
}

void AdjustDown(DataType* data, int size, int root)
{
	assert(data);

	int parent = root;
	int child = root * 2 + 1;

	while (child < size)
	{
		if (child + 1 < size && data[child + 1] < data[child])
		{
			++child;
		}

		if (data[child] < data[parent])
		{
			Swap(&data[child], &data[parent]);
		}
		else
			break;

		parent = child;
		child = parent * 2 + 1;
	}
}

void AdjustUp(DataType* data, int child)
{
	int parent = (child - 1) / 2;
	
	while (child > 0)
	{
		if (data[child] < data[parent])
		{
			Swap(&data[child], &data[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
			break;
	}
}

void HeapCreate(Heap* hp, DataType* data, int size)
{

	hp->data = (DataType*)malloc(size * sizeof(DataType));
	memcpy(hp->data, data, size * sizeof(DataType));
	hp->size = size;
	hp->capacity = size;

	for (int i = (size - 2) / 2; i >= 0; i--)
	{
		AdjustDown(hp->data, hp->size, i);
	}
}

void HeapPush(Heap* hp, DataType x)
{
	if (hp->size == hp->capacity)
	{
		hp->capacity *= 2;
		hp->data = (DataType*)realloc(hp->data, hp->capacity * sizeof(DataType));
	}

	hp->data[hp->size++] = x;

	AdjustUp(hp->data, hp->size - 1);
}

void HeapPop(Heap* hp)
{
	Swap(&hp->data[hp->size - 1], &hp->data[0]);
	hp->size--;

	AdjustDown(hp->data, hp->size, 0);
}

int HeapEmpty(Heap* hp)
{
	return hp->size ? 0 : 1;
}

DataType HeapTop(Heap* hp)
{
	return hp->data[0];
}

int HeapSize(Heap* hp)
{
	return hp->size;
}

void HeapPrint(Heap* hp)
{
	int i = 0;

	for (i = 0; i < hp->size; i++)
	{
		printf("%d ", hp->data[i]);
	}
}

void HeapDestory(Heap* hp)
{
	free(hp->data);
	hp->data = NULL;
	hp->capacity = hp->size = 0;
	free(hp);
	hp = NULL;
}

void TopK(int* arr, int size, int k)
{
	Heap hp;
	HeapCreate(&hp, arr, k);

	for (int i = k; i < size; i++)
	{
		if (HeapTop(&hp) < arr[i])
		{
			HeapPop(&hp);
			HeapPush(&hp, arr[i]);
		}
	}

	HeapPrint(&hp);
}

//void TopK(int* arr, int size, int k)
//{
//	int *a = (int*)malloc(k * sizeof(int));
//	memcpy(a, arr, k * sizeof(int));
//
//	for (int i = (k - 2) / 2; i >= 0; i--)
//	{
//		AdjustDown(a, k, i);
//	}
//
//	for (int i = 0; i < size; i++)
//	{
//		if (a[0] < arr[i])
//		{
//			Swap(&a[0], &a[k - 1]);
//			AdjustDown(a, k - 1, 0);
//			a[k - 1] = arr[i];
//			AdjustUp(a, k - 1);
//		}
//	}
//	for (int i = 0; i < k; i++)
//	{
//		printf("%d  ", a[i]);
//	}
//}

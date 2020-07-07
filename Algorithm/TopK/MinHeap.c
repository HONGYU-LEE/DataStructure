#include<stdlib.h>
#include<string.h> 
#include<stdio.h>
#include<assert.h> 
typedef int DataType;

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

void TopK(int* arr, int size, int k)
{
	int *a = (int*)malloc(k * sizeof(int));
	int i;
	memcpy(a, arr, k * sizeof(int));

	for (i = (k - 2) / 2; i >= 0; i--)
	{
		AdjustDown(a, k, i);
	}

	for (i = 0; i < size; i++)
	{
		if (a[0] < arr[i])
		{
			Swap(&a[0], &a[k - 1]);
			AdjustDown(a, k - 1, 0);
			a[k - 1] = arr[i];
			AdjustUp(a, k - 1);
		}
	}
	for (i = 0; i < k; i++)
	{
		printf("%d  ", a[i]);
	}
}

/*
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
*/

void testTopK()
{
	srand((unsigned)time(0));
	int size = 100000, i;
	int* arr = (int*)malloc(sizeof(int) * size);
	for (i = 0; i < size; i++)
	{
		arr[i] = rand() % size;
	}

	arr[50] = size + 1;
	arr[21] = size + 2;
	arr[5001] = size + 3;
	arr[42] = size + 4;
	arr[123] = size + 5;
	arr[57] = size + 6;
	arr[1] = size + 7;
	arr[50061] = size + 8;
	arr[477] = size + 9;
	
	TopK(arr, size, 10);
}

int main()
{
	testTopK();
	return 0;
}

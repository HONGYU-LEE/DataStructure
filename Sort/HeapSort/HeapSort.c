#include<stdio.h>

void AdjustDown(int *arr, int size, int root)
{
	int parent = root;
	int child = parent * 2 + 1;
	
	while(child < size)
	{
		if(child + 1 < size && arr[child] < arr[child + 1])
		{
			++child;
		}
		
		if(arr[child] > arr[parent])
		{
			int temp = arr[parent];
			arr[parent] = arr[child];
			arr[child] = temp;
		}
		else
			break;

		
		parent = child;		
		child = parent * 2 + 1;
	}
}

void HeapSort(int *arr, int size)
{
	int i = 0;
	for(i = (size - 2) / 2 ; i >= 0; i--)
	{
		AdjustDown(arr, size, i);
	}

	for(i = size - 1; i > 0; i--)
	{		
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		AdjustDown(arr, i, 0);
	}
 
}

int main()
{
	int arr[] = {46, 74, 53, 14, 26, 36, 86, 65, 27, 34};
//	int arr[] = {34, 53, 36, 46, 726, 14, 86, 65, 27, 4};
	int length = sizeof(arr) / sizeof(arr[0]);
	int i = 0;
	HeapSort(arr, length);
	for(i = 0; i < length; i++)  
	{
		printf("%d ", arr[i]);
	}
	return 0;
} 

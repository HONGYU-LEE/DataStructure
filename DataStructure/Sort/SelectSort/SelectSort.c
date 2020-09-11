#include<stdio.h>

void printArray(int *arr, int size)
{
	int i;
	for(i = 0; i < size; i++)  
	{
		printf("%d ", arr[i]);
	}
	printf("\n"); 
} 

void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
} 

void SelectSort(int *arr, int n)
{
	int i, j, mini;
	for(i = 0; i < n - 1; ++i)
	{
		mini = i;
		for(j = i + 1; j <= n - 1; ++j)
		{
			if(arr[j] < arr[mini])
				mini = j; 
		}
		
		if(mini != i)
			swap(&arr[i], &arr[mini]);
		printArray(arr, n);
	}
}

int main()
{
	int arr[] = {46, 74, 53, 14, 26, 36, 86, 65, 27, 34};
//	int arr[] = {34, 53, 36, 46, 726, 14, 86, 65, 27, 4};
	int length = sizeof(arr) / sizeof(arr[0]);
	int i = 0;
	printArray(arr, length);
	SelectSort(arr, length);
	printArray(arr, length);
	return 0;
} 

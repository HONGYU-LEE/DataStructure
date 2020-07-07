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

/* 
void InsertSort(int* arr, int n)
{
	int i, j, temp;
	for (i = 1; i < n; i++)
	{
		if (arr[i] < arr[i - 1])
		{
			temp = arr[i];
			for (j = i - 1; arr[j] > temp; j--)
			{
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = temp;
		} 
	}
}
*/

void InsertSort(int* arr, int n)
{
	int i, end, temp;
	for(i = 0; i < n - 1; i++)
	{
		end = i;
		temp = arr[end + 1];
		
		while(end >= 0)
		{
			if(arr[end] > temp)
			{
				arr[end + 1] = arr[end];
				end--;
			}
			else
				break;
		}
		
		arr[end + 1] = temp;
		printArray(arr, n);
	} 
}

 
int main()
{
	int arr[10] = {46, 74, 53, 14, 26, 36, 86, 65, 27, 34};
	int length = sizeof(arr) / sizeof(arr[0]);
	int i = 0;
	printArray(arr, length);
	InsertSort(arr, length); 
	return 0;
}

#include<stdio.h>

void BubbleSort(int* arr, int n)
{
	int i, j, temp, flag = 1;
	
	for (i = 0; flag && i < n - 1; i++)
	{
		flag = 0;
		for (j = n - 1; j > i; j--)
		{
			if (arr[j - 1] > arr[j])
			{
				temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
				flag = 1;
			}
		}
	}
} 

int main()
{
	int arr[10] = {46, 74, 53, 14, 26, 36, 86, 65, 27, 34};
	int length = sizeof(arr) / sizeof(arr[0]);
	int i = 0;
	BubbleSort(arr, length); 
	for (i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}

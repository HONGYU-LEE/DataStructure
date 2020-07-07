#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void CountSort(int* arr, int n)
{
	int i, j =0, min = arr[0], max = arr[0];
	
	for (i = 0; i < n; i++)
	{
		if (arr[i] < min)
			min = arr[i];

		if (arr[i] > max)
			max = arr[i];
	}

	int range = max - min + 1;
	int* count = (int*)malloc(sizeof(int) * range);
	memset(count, 0, sizeof(int) * range);

	for (i = 0; i < n; i++)
	{
		count[arr[i] - min]++;
	}

	for (i = 0; i < range; i++)
	{
		while (count[i]--) 
		{
			arr[j++] = i + min;
		}
	}
}




int main()
{
	int arr[] = { 46, 74, 53, 14, 26, 36, 86, 65, 27, 34 };
	//	int arr[] = {34, 53, 36, 46, 726, 14, 86, 65, 27, 4};
	int length = sizeof(arr) / sizeof(arr[0]);
	int i = 0;
	CountSort(arr, length);
	for (i = 0; i < length; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}
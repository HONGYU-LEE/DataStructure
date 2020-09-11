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
void ShellSort(int* arr, int n)
{
	int i, j, temp;
	int gap = n;
	do
	{
		gap = gap / 3 + 1;
		//设置增量 
		for (i = gap; i < n; i++)
		{
			if (arr[i] < arr[i - gap])
			{
				temp = arr[i];
				
				for (j = i - gap; j >= 0 && arr[j] > temp; j -= gap)
				{
					arr[j + gap] = arr[j];
				}
				
				arr[j + gap] = temp;
			} 
		}
				
	} while (gap > 1);
}
*/
void ShellSort(int* arr, int n)
{
	int gap = n, i;
	while(gap > 1)
	{
		gap = gap / 3 + 1;
				printf("当前gap：%d\n", gap); 
		for(i = 0; i < n - gap; ++i)
		{
			int end = i;
			int temp = arr[end + gap];	
			
			while(end >= 0)
			{
				if(arr[end] > temp)
				{	
					arr[end + gap] = arr[end];			
					end -= gap;
				}
				else
					break;	
			} 
			arr[end + gap] = temp;
			printArray(arr, n);
		}

		
	}
}

int main()
{
	int arr[] = {46, 53, 74, 14, 26, 36, 86, 65, 27, 34};
	int length = sizeof(arr) / sizeof(arr[0]);
	int i = 0;

	ShellSort(arr, length); 

	return 0;
}

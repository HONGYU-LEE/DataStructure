#include"Search and Sort.h"

void Swap(int* i, int* j)
{
	int temp;
	temp = *i;
	*i = *j;
	*j = temp;
}

void Qsort(int* arr, int low, int high)
{
	int pivot;
	if (low < high)
	{
		pivot = Partition(arr, low, high);

		Qsort(arr, low, pivot - 1);
		Qsort(arr, pivot + 1, high);
	}
}



int Partition(int* arr, int low, int high)
{
	int pivotkey;
	pivotkey = arr[low];

	while (low < high)
	{
		while (low < high && arr[high] >= pivotkey)
		{
			high--;
		}
		Swap(&arr[low], &arr[high]);

		while (low < high && arr[low] <= pivotkey)
		{
			low++;
		}
		Swap(&arr[low], &arr[high]);
	}

	return low;
}

void QuickSort(int* arr, int length)
{
	Qsort(arr, 0, length - 1);
}

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

int InsertSearch(int right, int key, int* a)
{
	int left = 0, mid;
	while (left <= right)
	{
		mid = left + (key - a[left]) * (right - left) / (a[right] - a[left]);
		if (key > a[mid])
		{
			left = mid + 1;
		}
		else if (key < a[mid])
		{
			right = mid - 1;
		}
		else if (key == a[mid])
		{
				return mid;
		}
	}

	if (left > right)
	{
		return -1;
	}
}

int BinarySearch(int right, int n, int* arr)
{
	int left = 0, mid;
	while (left <= right)
	{
		mid = (right + left) / 2;
		if (n > arr[mid])
		{
			left = mid + 1;
		}
		else if (n < arr[mid])
		{
			right = mid - 1;
		}
		else if (n == arr[mid])
		{
			return mid;
		}
	}

	if (left > right)
	{
		return -1;
	}
}

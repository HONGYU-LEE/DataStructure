#include"Stack.h"

//交换
void Swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

//三数取中，优化枢轴, 保证中间值在end的位置
void chancePovit(int* arr, int begin, int end)
{
	int mid = ((end - begin) >> 1) + begin;

	if (arr[begin] > arr[end])
	{
		Swap(&arr[begin], &arr[end]);
	}

	if (arr[mid] < arr[begin])
	{
		Swap(&arr[mid], &arr[begin]);
	}

	if (arr[end] > arr[mid])
	{
		Swap(&arr[end], &arr[mid]);
	}
}

void printArr(int* arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}

	printf("\n");
}

// Hoare法
int Hoare(int* arr, int begin, int end)
{
	chancePovit(arr, begin, end);
	int pivot = arr[end];
	int pivot_index = end;
	while (begin < end)
	{
		while (begin < end && arr[begin] <= pivot)
		{
			++begin;
		}

		while (begin < end && arr[end] >= pivot)
		{
			--end;
		}

		Swap(&arr[begin], &arr[end]);
	}

	Swap(&arr[begin], &arr[pivot_index]);
	return begin;
}


//挖坑法
int DigHole(int* arr, int begin, int end)
{
	chancePovit(arr, begin, end);
	int pivot = arr[end];
	while (begin < end)
	{
		while (begin < end && arr[begin] <= pivot)
		{
			++begin;
		}

		arr[end] = arr[begin];
		while (begin < end && arr[end] >= pivot)
		{
			--end;
		}

		arr[begin] = arr[end];
	}

	arr[begin] = pivot;
	return begin;
}


//双指针法
int PrevCurMethod(int* arr, int begin, int end)
{
	int cur = begin, prev = begin - 1;
	chancePovit(arr, begin, end);
	int pivot = arr[end];
	while (cur < end)
	{
		if (arr[cur] < pivot && ++prev != cur)
		{
			Swap(&arr[cur], &arr[prev]);
		}
		++cur;
	}
	++prev;
	Swap(&arr[cur], &arr[prev]);

	return prev;
}


//递归多趟
void QuickSort(int* arr, int begin, int end)
{
	if (begin < end)
	{
		int pivot = PrevCurMethod(arr, begin, end);
		
		QuickSort(arr, begin, pivot - 1);
		QuickSort(arr, pivot + 1, end);
	}
}

void QuickSort_Plus(int* arr, int begin, int end)
{
	while (begin < end)
	{
		int pivot = PrevCurMethod(arr, begin, end);

		QuickSort(arr, begin, pivot - 1);
		begin = pivot + 1;
	}
}

//非递归
void noRecursive(int* arr, int begin, int end)
{
	Stack s;
	StackInit(&s);
	StackPush(&s, begin);
	StackPush(&s, end);

	while (!StackEmpty(&s))
	{
		//因为入栈时先入左子树再入右子树，所以先出的应该是右子树再到左子树
		int right = StackTop(&s);
		StackPop(&s);

		int left = StackTop(&s);
		StackPop(&s);

		int povit = DigHole(arr, left, right);
		//划分区间[left][povit - 1] [povit + 1][right]
		if (left < povit)
		{
			StackPush(&s, left);
			StackPush(&s, povit - 1);
		}

		if (right > povit)
		{
			StackPush(&s, povit + 1);
			StackPush(&s, right);
		}
	}

	StackDestroy(&s);
}


int Hoare1(int* arr, int begin, int end)
{
	//chancePovit(arr, begin, end);
	int pivot = arr[begin];
	int pivot_index = begin;
	while (begin < end)
	{
		while (begin < end && arr[begin] <= pivot)
		{
			++begin;
		}

		while (begin < end && arr[end] >= pivot)
		{
			--end;
		}

		Swap(&arr[begin], &arr[end]);
	}

	//Swap(&arr[begin], &arr[pivot_index]);
	return end;
}

int main()
{
	int arr[7] = { 30,15,40,28,50,10,70 };
	int length = sizeof(arr) / sizeof(arr[0]) - 1;
	int i = 0;
	Hoare1(arr, 0, length);
	//QuickSort(arr, 0, length);
	for (i = 0; i < 7; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}
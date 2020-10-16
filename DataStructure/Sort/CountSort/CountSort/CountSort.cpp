#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<vector>

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

void countSort(vector<int>& arr)
{
    int max = arr[0], min = arr[0];
    
    //找出最大值和最小值，缩减范围
    for(int i = 1; i < arr.size(); i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
        }
        if(arr[i] < min)
        {
            min = arr[i];
        }
    }

    int range = max - min + 1;
    vector<int> count(range, 0);    //统计数组
    //统计每种数字出现的次数
    for(int i = 0; i < arr.size(); i++)
    {
        count[arr[i] - min]++;
    }

    //保证计数排序稳定，对数组变形，统计数组的每一个位置的值为前面所有数字的数量合
    //变形后每个位置的值即为该数据的排序的序号
    int sum = 0;
    for(int i = 0; i < range; i++)
    {
        sum += count[i];
        count[i] = sum;
    }

    //按照原数组的数据的位置，倒序将数据放回原位，确保稳定性
    vector<int> temp(arr.size(), 0);
    for(int i = arr.size() - 1; i >= 0; i--)
    {
        //序号-1才是下标位置
        temp[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }

    arr = temp; //将临时数据拷贝回原数组
}

int main()
{
	vector<int> arr = { 46, 74, 53, 14, 26, 36, 86, 65, 27, 34 };

	countSort(arr);
	
    for(auto i : arr)
    {
        cout << i << ends;
    }
	return 0;
}


/*
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
}*/
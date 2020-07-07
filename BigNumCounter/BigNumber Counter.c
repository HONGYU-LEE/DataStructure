#include "BigNumber Counter.h"


void InitBigNum(BigNum *s1, char* str)
{
	assert(s1 && str);
	int i, j;
	j = strlen(str);
	for (i = 0; i < j; i++)
	{
		s1->data[i] = 0;
		s1->data[i] = str[i];
	}
	s1->data[i] = '\0';
	s1->length = j;
}

int* reverse(int* arr, int head, int tail)
{
	while (head < tail)
	{
		int temp = arr[head];
		arr[head] = arr[tail];
		arr[tail] = temp;
		head++;
		tail--;
	}
	return arr;
}

void AddBigNum(BigNum* src1, BigNum* src2, BigNum* dst)
{
	int arr1[NUMSIZE], arr2[NUMSIZE], ret[NUMSIZE] = {0};
	char str[NUMSIZE];
	int i, j, k = 0;
	int temp, next = 0;
	int len1 = src1->length, len2 = src2->length;
	k = len1 > len2 ? len2 : len1;

	for (i = 0; i < len1; i++)
	{
		arr1[i] = src1->data[i] - '0';
	}
	reverse(arr1, 0, i - 1);

	for (i = 0; i < len2; i++)
	{
		arr2[i] = src2->data[i] - '0';
	}
	reverse(arr2, 0, i - 1);
	//将字符串逆序导入数组

	for(i = 0; i < k; i++)
	{
		temp = arr1[i] + arr2[i] + next;
		next = temp / 10;
		ret[i] = temp % 10;
	}
	//先计算最短长度，再计算多出来的那一部分
	while (i < len1)
	{
		temp = arr1[i] + next;
		next = temp / 10;
		ret[i++] = temp % 10;
	}

	while (i < len2)
	{
		temp = arr2[i] + next;
		next = temp / 10;
		ret[i++] = temp % 10;
	}

	if (next > 0)
		ret[i++] = next;

	reverse(ret, 0, i - 1);

	for (j = 0; j < i; j++)
	{
		str[j] = ret[j] + '0';
	}
	str[j] = '\0';

	InitBigNum(dst, str);
}

void MinusBigNum(BigNum* src1, BigNum* src2, BigNum* dst)
{
	int arr1[NUMSIZE], arr2[NUMSIZE], ret[NUMSIZE] = { 0 };
	char str[NUMSIZE];
	int i, j, k = 0;
	int flag, next = 0;
	int len1 = src1->length, len2 = src2->length, big, small;
	

	for (i = 0; i < src1->length; i++)
	{
		arr1[i] = src1->data[i] - '0';
	}
	reverse(arr1, 0, i - 1);

	for (i = 0; i < src2->length; i++)
	{
		arr2[i] = src2->data[i] - '0';
	}
	reverse(arr2, 0, i - 1);

	if (len1 > len2)
	{
		big = len1;
		small = len2;
	}
	else
	{
		big = len2;
		small = len1;
	}
	//将长度大的放到big里，短的长度放到small

	if (0 == strcmp(src1->data, src2->data))
	{
		InitBigNum(dst, "0");
		return;
	}
	//当两个相同的时候直接初始化为0
	else
	{
		if (strcmp(src1->data, src2->data) >= 0)
			//flag为符号位，这里是判断正负,按照被减数大减数小来导入数据
		{
			flag = 1;

			for (i = 0; i < len1; i++)
			{
				arr1[i] = src1->data[i] - '0';
			}
			reverse(arr1, 0, i - 1);

			for (i = 0; i < len2; i++)
			{
				arr2[i] = src2->data[i] - '0';
			}
			reverse(arr2, 0, i - 1);
		}
		else
		{
			flag = -1;
			for (i = 0; i < len2; i++)
			{
				arr1[i] = src2->data[i] - '0';
			}
			reverse(arr1, 0, i - 1);

			for (i = 0; i < len1; i++)
			{
				arr2[i] = src1->data[i] - '0';
			}
			reverse(arr2, 0, i - 1);
		}

		for (i = 0; i < small; i++)
		{
			if (arr1[i] >= arr2[i])
			{
				ret[i] = arr1[i] - arr2[i];
			}
			else
			{
				ret[i] = arr1[i] - arr2[i] + 10;
				arr1[i++]--;
			}
		}
		//计算较短长度那部分的差值,因为高位的那部分除了前面借位的部分 其他的可以不用计算

		while (i < big)
		{
			if (arr1[i] >= 0)
			{
				ret[i] = arr1[i];
			}
			else 
			{
				ret[1] = arr1[i] + 10;
				arr1[i + 1]--;
			}
			i++;
		}
		//计算长的数组多出来那部分，小于零的结尾，大于零的直接复制
	}

	while (0 == ret[i - 1])
		i--;
	reverse(ret, 0, i - 1);
	//去掉多余位
	j = 0;
	if (flag == -1)
		str[j++] = '-';
	//将符号位放到首位


	while(j < i)
	{
		str[j] = ret[j] + '0';
		j++;
	}
	str[j] = '\0';

	InitBigNum(dst, str);
}


void DivideBigNum(BigNum* src1, BigNum* src2, BigNum* dst)
{
	char result_tmp[NUMSIZE];
	char final[NUMSIZE];
	int i, j, k;
	int len1 = src1->length, len2 = src2->length;
	char* result;
	k = 0;
	while (1)
	{                        //死循环只有当len1和len2相等时跳出循环，因为会不断的在src2->data数组前加0所以该数组的长度，                                          //会不断的变化当两者相等时说明已经无法在作减法。
		result_tmp[k] = 0;
		while (strcmp(src1->data, src2->data) >= 0)
		{ 
			int i = 0, j;                  //如果相等则向后移动一位一旦发现不等则立即返回忽略后面的所有数据。
			while (1)
			{
				if (src1->data[i] == '0')
					i++;//去除src1->data高位前面的0
				else
				{
					j = i;              //去除src2->data高位填充的0
					break;
				}
			}
			for (; i < len2; i++)            //作减法
				src1->data[i] = src1->data[i] - src2->data[i] + '0';
			for (i = len2 - 1; i > j; i--)       //每作一组减法就整理数组，这种整理数组在前几篇中都有使用。
				if (src1->data[i] < '0')
				{              //不过在这里不是整理结果数组而是src1->data数组，结果保存在ａ数组中不用整理
					src1->data[i] += 10;;
					src1->data[i - 1]--;
				}
			result_tmp[k]++;
		}
		k++;
		if (len1 == len2)
			break;
		for (i = len2 - 1; i >= 0; i--)   //将src2->data中的元素先后移位，同时扩大src2->data长度并且在src2->data前端补一位0。
			src2->data[i + 1] = src2->data[i];
		src2->data[0] = '0';               //由于数组后移所以src2->data[0]每次移动后都为空，所以每次用0补齐。
		len2++;
		src2->data[len2] = '\0';           //在结尾加上字符串的结束标记。
	}
	i = 0;j = 0;
	while (result_tmp[i] == 0)
		i++;
	for (; i < k; i++)
	{
		final[j++] = result_tmp[i] + '0';

	}
	final[j] = '\0';
	result = final;
	InitBigNum(dst, result);
	
}

void MuliplyBigNum(BigNum* src1, BigNum* src2, BigNum* dst)
{
	int arr1[NUMSIZE], arr2[NUMSIZE], ret[NUMSIZE] = { 0 };
	int i, j, k;
	int temp, next = 0;
	int len1 = src1->length, len2 = src2->length;


	InitBigNum(dst, "0");

	for (i = 0; i < len1; i++)
	{
		arr1[i] = src1->data[i] - '0';
	}
	reverse(arr1, 0, i - 1);

	for (i = 0; i < len2; i++)
	{
		arr2[i] = src2->data[i] - '0';
	}
	reverse(arr2, 0, i - 1);

	for (i = 0; i < len2; i++)
	{
		next = 0;
		for (j = 0;j < len1;j++) {
			temp = arr1[j] * arr2[i] + next;
			ret[j] = temp % 10;
			next = temp / 10;
		}

		if (next > 0)
		{
			ret[j++] = next;
		}

		while (0 == ret[j - 1])
			j--;

		char str[NUMSIZE];

		reverse(ret, 0, j - 1);

		for (k = 0;k < j;k++)
			str[k] = ret[k] + '0';

		for (j = 0;j < i;j++)
			str[k++] = '0';

		str[k] = '\0';

		BigNum* t;
		t = (BigNum*)malloc(sizeof(BigNum));
		InitBigNum(t, str);
		AddBigNum(dst, t, dst);
	}
}



#include<stdio.h>
int Search(int right,int key,int a[])
{
	int left =0,mid;
	while(left <= right)
	{
		mid = left +  (key - a[left]) * (right - left) / (a[right] - a[left]);
		if( key > a[mid] )
		{
			left = mid + 1; 
		} 
		else if( key < a[mid])
		{
			right = mid - 1;
		}
		else if( key == a[mid])
		{
			return mid;
		}
	}
	
	if(left > right)
	{
		return -1;
	}
}
int main()
{
	int a[] ={1,3,5,7,9,11,13,15,17,19};
	int key,i,right,left,mid;
	right = sizeof(a)/sizeof(a[0])-1;
	left =0;
	
	printf("请输入要查找的数据:");
	scanf("%d",&key);
	mid = Search(right,key,a);
	
	if( -1 == mid )
	{
		printf("查找失败 ");	 
	}
	else
	{
		printf("下标为：%d",mid);
	}
	return 0;
}

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define StackSize 100 //假定预分配的栈空间最多为100个元素
typedef char DataType;//假定栈元素的数据类型为字符

typedef struct
{
	DataType data[StackSize];
	int top;
}SeqStack;

void Init(SeqStack *&s)
{
    s=(SeqStack *)malloc(sizeof(SeqStack));
    s->top=-1;
}
//初始化栈
void push(SeqStack *s,DataType e)
{
	if( s->top == StackSize )
	{
		printf("栈满\n");
	}
	else
	{
		s->top++;
        s->data[s->top]=e;
	}
}
//入栈 
DataType pop(SeqStack *s)
{
	if( s->top == -1 )
	{
		printf("栈空\n");
		return  '\0';
	}	
	return (s->data[s->top--]);
}
//出栈 
int main()
{
	SeqStack *s;
	int i=0,length,mid,flag=1;
	char str[StackSize],y,z;
	printf("请输入需要判断回文的字符串：\n");
	gets(str);
	length = strlen(str);
	mid = length/2-1;
//mid为字符串中间字符的下标
	Init(s);
	
	for( i=0; i<length/2; i++)
	{
		push(s,str[i]);
	}
//入栈	
	if( length%2 != 0 )
		mid += 1;
//判断字符串长度是奇数还是偶数，当为奇数时从中间下一个开始比较 
	for( i=1; i<=length/2; i++)
	{
		if( str[mid+i] == pop(s) )
		{
			flag = 1;
		}
		else
		{
			flag = 0;
			break;
		}
	} 
	if( flag == 1 )
		printf("该字符串为回文\n"); 
	else
		printf("该字符串不是回文");

	return 0;
}

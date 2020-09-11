#include"Stack.h"

void ChackCapacity(Stack* ps)
{
	if (ps->top >= ps->capacity)
	{
		ps->capacity *= 2;
		ps->data = (DataType*)realloc(ps->data, ps->capacity * sizeof(DataType));

	}
}
void StackInit(Stack* ps)
{
	ps->data = (DataType*)malloc(STACKSIZE * sizeof(DataType));
	ps->top = 0;
	ps->capacity = STACKSIZE;
}

// 入栈 
void StackPush(Stack* ps, DataType data)
{
	ChackCapacity(ps);
	ps->data[ps->top++] = data;
}

// 出栈 
void StackPop(Stack* ps)
{
	if (0 == ps->top)
		return;
	ps->top--;
}

// 获取栈顶元素 
DataType StackTop(Stack* ps)
{
	if (0 == ps->top)
		return (DataType)0;
	return ps->data[ps->top - 1];
}

// 获取栈中有效元素个数 
int StackSize(Stack* ps)
{
	return ps->top;
}

// 检测栈是否为空，如果为空返回非零(1)，如果不为空返回0 
int StackEmpty(Stack* ps)
{
	return ps->top == 0;
}

// 销毁栈 
void StackDestroy(Stack* ps)
{
	free(ps->data);
	ps->data = NULL;
	ps->top = 0;
	ps->capacity = 0;
}
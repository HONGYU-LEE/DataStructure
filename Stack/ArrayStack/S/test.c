#include"Stack.h"

void test()
{
	Stack stack ;
	StackInit(&stack);
	StackPush(&stack, 1);
	printf("%d ", StackTop(&stack));
	StackPush(&stack, 2);
	printf("%d ", StackTop(&stack));
	StackPush(&stack, 3);
	printf("%d ", StackTop(&stack));
	StackPush(&stack, 4);
	printf("%d ", StackTop(&stack));
	printf("\n");
	printf("元素个数为%d\n", StackSize(&stack));
	printf("栈是否为空:%d\n", StackEmpty(&stack));

	printf("%d ", StackTop(&stack));
	StackPop(&stack);
	printf("%d ", StackTop(&stack));
	StackPop(&stack);
	printf("%d ", StackTop(&stack));
	StackPop(&stack);
	printf("%d ", StackTop(&stack));
	StackPop(&stack);

	printf("\n");

	printf("元素个数为%d\n", StackSize(&stack));
	printf("栈是否为空:%d\n", StackEmpty(&stack));
}


int main()
{
	test();
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include"couter.h"
int main()
{
	char s1[MaxSize];			
	char s2[MaxSize];			
	printf("请输入表达式:");
	scanf("%s", s1);

	Trans(s1, s2);				

	printf("计算结果为: %f", Calculate(s2));	


	return 0;
}


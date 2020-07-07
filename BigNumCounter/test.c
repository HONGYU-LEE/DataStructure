
#include "BigNumber Counter.h"

void Menu()
{
	printf("************************************************\n");
	printf("**    1.大数加法          2.大数减法          **\n");
	printf("**    3.大数乘法          4.大数除法          **\n");
	printf("**               0.退出                       **\n");
	printf("************************************************\n");
}

void test()
{
	void (*Counter[4])(BigNum * s1, BigNum * s2, BigNum * s3) =
	{
		AddBigNum,
		MinusBigNum,
		MuliplyBigNum,
		DivideBigNum,
	};
	//函数指针数组简化代码
	int input = 0;
	BigNum s1, s2, s3;


	char str1[NUMSIZE];
	char str2[NUMSIZE];

	printf("请输入第一个操作数：");
	scanf("%s",str1);
	InitBigNum(&s1, str1);

	printf("请输入第二个操作数：");
	scanf("%s", str2);
	InitBigNum(&s2, str2);

	do
	{
		Menu();
		printf("请输入要进行的操作：");
		scanf("%d", &input);
		InitBigNum(&s3, "0");
		if ((input <= 4 && input > 0))
		{
			(*Counter[input - 1])(&s1, &s2, &s3);
			printf("计算结果：%s\n\n", s3.data);
		}
		else if(0 == input)
		{
			printf("程序退出；\n");
			exit(0);
		}
		else
		{
			printf("输出错误：\n");
		}
	} while (input);
}
int main()
{
	
	test();
	return 0;
}
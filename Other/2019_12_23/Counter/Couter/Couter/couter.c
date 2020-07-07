#define _CRT_SECURE_NO_WARNINGS
#include"couter.h"
//初始化 
void Initc(cStack* s1)
{
	s1->top = -1;
}

//字符栈压栈 
int Pushc(cStack* c1, char op)
{
	if (c1->top < MaxSize)
	{
		c1->data[++c1->top] = op;
		return 1;
	}
	else return 0;
}

//GET栈顶元素 
char Gettopc(cStack* c1)
{
	return c1->data[c1->top];
}

//字符栈出栈 
char Popc(cStack* c1)
{
	return c1->data[c1->top--];
}

//初始化数据栈 
void Initd(dStack* d1)
{
	d1->top = -1;
}

//数据栈压栈 
int Pushd(dStack* d1, double data)
{
	if (d1->top < MaxSize)
	{
		d1->data[++d1->top] = data;
		return 1;
	}
	else return 0;
}

//数据栈出栈 
double Popd(dStack* d1)
{
	return d1->data[d1->top--];
}

int Isop(char op)		//当前扫描运算符优先级
{
	switch (op)
	{
	case '(': return 6;
	case '+': case '-': return 2;
	case '*': case '/': return 4;
	}
}
int Inop(char op)		//当前扫描运算符优先级
{
	switch (op)
	{
	case '(': return 1;
	case '+': case '-': return 3;
	case '*': case '/': return 5;
	}
}

void Trans(char* s1, char* s2)
{
	int i = 0;
	int j = 0;
	int flag1 = -1;				
	int flag2 = -1; 				
	cStack st1;				
	Initc(&st1);

	while (s1[i] != '\0')		
	{
		if (s1[0] == '-')			
		{
			j = strlen(s1);
			while (j > 0)
			{
				s1[j + 5] = s1[j];
				j--;
			}
			s1[j++] = '(';
			s1[j++] = '0';
			s1[j++] = '-';
			s1[j++] = '1';
			s1[j++] = ')';
			s1[j] = '*';

		}
		if (s1[i] == '(' && s1[i + 1] == '-')	
		{
			j = strlen(s1);
			while (j > i + 1)
			{
				s1[j + 5] = s1[j];
				j--;
			}
			s1[j++] = '(';
			s1[j++] = '0';
			s1[j++] = '-';
			s1[j++] = '1';
			s1[j++] = ')';
			s1[j] = '*';
			i = i + 5;
		}
		i++;
	}

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		if (flag1 == 0 && flag2 == 1)		
		{
			s2[j++] = ' ';
			flag1 = 1;
		}
		if (s1[i] >= '0' && s1[i] <= '9' || s1[i] == '.')
		{
			s2[j++] = s1[i];
			flag2 = 0;
			flag1 = 0;
		}
		else if (s1[i] == '+' || s1[i] == '-' || s1[i] == '*' || s1[i] == '/' || s1[i] == '(')
		{
			flag2 = 1;
			if (st1.top<0 || Isop(s1[i])>Inop(Gettopc(&st1)))
			{
				Pushc(&st1, s1[i]);
			}
			else
			{
				while (st1.top >= 0 && Isop(s1[i]) < Inop(Gettopc(&st1)))		
				{
					s2[j++] = Popc(&st1);
					flag1 = 1;
				}
				if (st1.top<0 || Isop(s1[i])>Inop(Gettopc(&st1)))			
				{
					Pushc(&st1, s1[i]);
				}

			}
		}
		else if (s1[i] == ')')
		{
			flag2 = 1;
			if (Gettopc(&st1) != '(')		
			{
				flag1 = 1;
			}
			while (Gettopc(&st1) != '(')
			{
				s2[j++] = Popc(&st1);
			}
			Popc(&st1);		
		}
		i++;
	}
	while (st1.top >= 0)		
	{
		s2[j++] = Popc(&st1);
	}
	s2[j] = '\0';
}


double Calculate(char* s1)
{
	int i = 0;
	int flag;				
	double data1, data2;
	double sum;
	dStack ds1;
	Initd(&ds1);
	while (s1[i] != '\0')
	{
		if (s1[i] == '+' || s1[i] == '-' || s1[i] == '*' || s1[i] == '/')			
		{
			data1 = Popd(&ds1);
			data2 = Popd(&ds1);
			if (s1[i] == '+') Pushd(&ds1, data2 + data1);
			else if (s1[i] == '-') Pushd(&ds1, data2 - data1);
			else if (s1[i] == '*') Pushd(&ds1, data2 * data1);
			else if (s1[i] == '/') Pushd(&ds1, data2 / data1);
		}
		else							
		{
			flag = 0;					
			sum = 0;
			double divider = 1;
			while (s1[i] != ' ' && s1[i] != '+' && s1[i] != '-' && s1[i] != '*' && s1[i] != '/')
			{
				if (s1[i] == '.')		
				{
					flag = 1;
					i++;
					continue;
				}
				if (flag == 0)
				{
					sum = sum * 10 + (double)(s1[i] - '0');
				}
				else
				{
					divider = divider * 10;
					sum = sum + ((double)(s1[i] - '0')) / divider;
				}
				i++;
			}
			if (s1[i] == '+' || s1[i] == '-' || s1[i] == '*' || s1[i] == '/') i--;	
			Pushd(&ds1, sum);
		}
		i++;		
	}
	return Popd(&ds1);
}
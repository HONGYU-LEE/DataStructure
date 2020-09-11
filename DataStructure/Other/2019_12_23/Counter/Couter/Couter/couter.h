#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#define MaxSize 100 

typedef struct CharStack
{
	char data[MaxSize];
	int top;
}cStack;

typedef struct DoubleStack
{
	double data[MaxSize];
	int top;
}dStack;

int Isop(char);
int Inop(char);
void Initc(cStack*);
int Pushc(cStack*, char);
char Gettopc(cStack*);
char Popc(cStack*);
void Initd(dStack*);
int Pushd(dStack*, double);
double Popd(dStack*);
void Trans(char* s1, char* s2);
double Calculate(char* s2);
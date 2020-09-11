#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
#define NUMSIZE 1000

typedef struct BigNum
{
	char data[NUMSIZE];
	int length;
}BigNum;

void InitBigNum(BigNum* s1, char* str);
void AddBigNum(BigNum* s1, BigNum* s2, BigNum* s3);
void MinusBigNum(BigNum* s1, BigNum* s2, BigNum* s3);
void DivideBigNum(BigNum* s1, BigNum* s2, BigNum* s3);
void MuliplyBigNum(BigNum* s1, BigNum* s2, BigNum* s3);
int* reverse(int* arr, int head, int tail);



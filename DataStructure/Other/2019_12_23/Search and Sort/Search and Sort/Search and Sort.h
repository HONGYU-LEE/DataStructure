#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define datasize 100

void Swap(int* i, int* j);
void BubbleSort(int* arr, int n);
void QuickSort(int* arr, int length);
int Search(int right, int key, int* arr);
int BinarySearch(int right, int n, int* arr);
int InsertSearch(int right, int key, int* a);
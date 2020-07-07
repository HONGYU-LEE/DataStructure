#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
typedef int DataType;

typedef struct Heap
{
	DataType *data;
	int size;
	int capacity;
}Heap;

void Swap(DataType* a, DataType* b);
void AdjustDown(DataType* data, int size, int root);
//向下调整算法
void AdjustUp(DataType* data, int child);
//向上调整算法
void HeapCreate(Heap* hp, DataType* data, int size);
//创建堆
void HeapDestory(Heap* hp);
//销毁堆
void HeapPush(Heap* hp, DataType x);
//入堆
void HeapPop(Heap* hp);
//出堆
int HeapSize(Heap* hp);
//堆的数据个数
int HeapEmpty(Heap* hp);
//判断堆是否为空
void HeapPrint(Heap* hp);
//显示堆
DataType HeapTop(Heap* hp);
//取堆顶数据
void TopK(int* arr, size_t size, int k);
//TopK算法

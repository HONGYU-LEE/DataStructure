
#include "Heap.h"


void testTopK()
{
	srand((unsigned)time(0));
	int size = 100000;
	int* arr = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % size;
	}

	arr[50] = size + 1;
	arr[21] = size + 2;
	arr[5001] = size + 3;
	arr[42] = size + 4;
	arr[123] = size + 5;
	arr[57] = size + 6;
	arr[1] = size + 7;
	arr[50061] = size + 8;
	arr[477] = size + 9;
	arr[153] = size + 10;
	TopK(arr, size, 10);
}
int main()
{
	/*int arr[] = { 34, 53, 36, 46, 726, 14, 86, 65, 27, 4 };
	Heap hp;
	HeapCreate(&hp, arr, 10);
	HeapPrint(&hp);
	HeapPush(&hp, 1);
	printf("\n");
	HeapPrint(&hp);*/
	//printf("%d ", HeapEmpty(&hp));
	//printf("%d \n", HeapTop(&hp));
	//printf("%d \n", HeapSize(&hp));
	//HeapPop(&hp);
	//HeapPush(&hp, 45);
	//printf("\n");
	//HeapPrint(&hp);
	//HeapPush(&hp, 425);
	//HeapPush(&hp, 415);
	//HeapPush(&hp, 4);
	testTopK();
	return 0;
}

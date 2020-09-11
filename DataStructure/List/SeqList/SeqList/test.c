#include "SeqList.h"

int main()
{
	SeqList list ;
	SeqListInit(&list, LISTSIZE);
	SeqListPushBack(&list, 1);
	SeqListPushBack(&list, 2);

	SeqListPushFront(&list, 3);
	SeqListPushFront(&list, 8);
	SeqListPrint(&list);

	/*SeqListFind(&list, 4);
	SeqListFind(&list, 5);
	*/
	/*SeqListPopBack(&list);
	SeqListPopFront(&list);
	SeqListPrint(&list);
	*/
	//SeqListErase(&list, 3);

	SeqListInsert(&list, 3, 5);
	SeqListPrint(&list);
	return 0;
}
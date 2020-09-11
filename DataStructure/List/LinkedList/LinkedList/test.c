#include "LinkList.h"

void test()
{
	ListNode* list = NULL;
	ListPushFront(&list, 1);
	ListPushFront(&list, 2);
	ListPushFront(&list, 3);
	ListPushFront(&list, 4);
	ListPrint(list);
	ListInsert(&(list + 3), 5);

	//ListPopBack(&list);
	//ListPushBack(&list, 1);
	//ListPushBack(&list, 2);
	//ListPushBack(&list, 3);
	//ListPushBack(&list, 4);
	ListPrint(list);

}

int main()
{
	test();
	return 0;
}
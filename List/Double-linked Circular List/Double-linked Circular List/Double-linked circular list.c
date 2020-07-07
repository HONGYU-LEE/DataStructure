#include "Double-linked circular list.h"

ListNode* ListCreate()
{
	ListNode* head = (ListNode*)malloc(sizeof(ListNode));
	head->data = 0;
	head->next = head;
	head->prev = head;
	return head;
}

void ListPrint(ListNode* list)
{
	assert(list);
	ListNode* cur = list->next;
	while (cur != list)
	{
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}

void ListPushBack(ListNode* list, DATATYPE x)
{
	assert(list);

	ListNode* head = list;
	ListNode* tail = head->prev;
	ListNode* cur = (ListNode*)malloc(sizeof(ListNode));
	cur->data = x;

	cur->prev = tail;
	cur->next = head;
	tail->next = cur;
	head->prev = cur;

	//ListInsert(list, x);
}

void ListPushFront(ListNode* list, DATATYPE x)
{
	assert(list);

	ListNode* head = list;
	ListNode* tail = head->prev;
	ListNode* cur = (ListNode*)malloc(sizeof(ListNode));
	cur->data = x;

	cur->next = head->next;
	head->next->prev = cur;
	
	head->next = cur;
	cur->prev = head;
	
	//ListInsert(list->next, x);
}

void ListDestory(ListNode* list)
{
	assert(list);
	
	ListNode* head = list;
	ListNode* cur = list->next;

	while (cur != head)
	{
		ListNode* next = cur->next;
		free(cur);
		cur = next;
	}

	free(head);
	head = NULL;

}

ListNode* ListFind(ListNode* list, DATATYPE x)
{
	assert(list);
	ListNode* cur = list->next;

	while (cur != list)
	{
		if (cur->data == x)
			return cur;
		else
			cur = cur->next;
	}

	return NULL;
}

void ListInsert(ListNode* pos, DATATYPE x)
{
	assert(pos);

	ListNode* cur = (ListNode*)malloc(sizeof(ListNode));
	cur->data = x;

	pos->prev->next = cur;
	cur->prev = pos->prev;
	cur->next = pos;
	pos->prev = cur;

	
}

void ListErase(ListNode* pos)
{
	assert(pos);

	pos->next->prev = pos->prev;
	pos->prev->next = pos->next;
	free(pos);
}

void ListPopBack(ListNode* list)
{
	assert(list);
	ListNode* head = list;
	ListNode* tail = list->prev;

	head->prev = tail->prev;
	tail->prev->next = head;
	free(tail);
	//ListErase(list->prev);
}

void ListPopFront(ListNode* list)
{
	assert(list);
	ListNode* head = list;
	ListNode* next = head->next;
	next->next->prev = head;
	head->next = next->next;
	free(next);
	//ListErase(list->next);
}
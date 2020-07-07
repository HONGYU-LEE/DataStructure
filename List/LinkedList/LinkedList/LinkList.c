#include "LinkList.h"

void ListPrint(ListNode* list)
{
	if (list == NULL)
	{
		printf("БэПе\n");
		return;
	}
	ListNode* cur = list;

	while (cur)
	{
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}

void ListPushBack(ListNode** list, DATATYPE x)
{
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));

	newnode->data = x;
	newnode->next = NULL;

	if (*list == NULL)
	{
		*list = newnode;
	}

	else
	{
		ListNode* tail = *list;

		while (tail->next)
		{
			tail = tail->next;
		}

		tail->next = newnode;
	}
}

void ListPushFront(ListNode** list, DATATYPE x)
{
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
	newnode->data = x;
	newnode->next = NULL;

	newnode->next = *list;
	*list = newnode;
}

void ListPopBack(ListNode** list)
{
	if (NULL == *list)
	{
		printf("БэПе\n");
		return;
	}
	else if ((*list)->next == NULL)
	{
		free(*list);
		*list = NULL;
	}
	else
	{
		ListNode* prev = NULL, * tail = *list;
		while (tail->next)
		{
			prev = tail;
			tail = tail->next;
		}
		free(tail);
		if (prev)
			prev->next = NULL;
	}
}


void ListPopFront(ListNode** list)
{
	if (NULL == *list)
		return;
	ListNode* next = (*list)->next;
	free(*list);
	(*list) = next;
	
}

ListNode* ListFind(ListNode** list, DATATYPE x)
{	
	ListNode* cur = *list;

	while (cur)
	{
		if (cur->data == x)
		{
			return cur;
		}
		else
		{
			cur = cur->next;
		}
	}
	
	return NULL;
}

void ListDestory(ListNode** list)
{
	ListNode* cur = *list;

	while (cur)
	{
		ListNode* next = cur->next;
		free(cur);
		cur = next;
	}
	*list = NULL;
}

void ListInsert(ListNode** pos, DATATYPE x)
{
	if (NULL == (*pos))
		return;

	ListNode* cur = (ListNode*)malloc(sizeof(ListNode));
	cur->data = x;

	cur->next = (*pos)->next;
	(*pos)->next = cur;
}

void ListErase(ListNode** pos)
{
	if (NULL == (*pos) || NULL == (*pos)->next)
		return;

	ListNode* next = (*pos)->next;
	(*pos)->next = next->next;
	free(next);
	next = NULL;
}
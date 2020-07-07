#pragma once

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define LISTSIZE 10

typedef int DATATYPE;
typedef struct ListNode
{
	DATATYPE data;
	struct ListNode* next;
}ListNode;

void ListPrint(ListNode* list);
void ListPushBack(ListNode** list, DATATYPE x);
void ListPushFront(ListNode** list, DATATYPE x);
void ListPopBack(ListNode** list);
void ListPopFront(ListNode** list);
void ListInsert(ListNode** pos, DATATYPE x);
void ListErase(ListNode** pos);
void ListDestory(ListNode** list);
ListNode* ListFind(ListNode** list, DATATYPE x);


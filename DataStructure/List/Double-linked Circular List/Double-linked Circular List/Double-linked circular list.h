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
	struct ListNode* prev;
}ListNode;

// 创建返回链表的头结点.
ListNode* ListCreate();
// 双向链表销毁
void ListDestory(ListNode* list);
// 双向链表打印
void ListPrint(ListNode* list);
// 双向链表尾插
void ListPushBack(ListNode* list, DATATYPE x);
// 双向链表尾删
void ListPopBack(ListNode* list);
// 双向链表头插
void ListPushFront(ListNode* list, DATATYPE x);
// 双向链表头删
void ListPopFront(ListNode* list);
// 双向链表查找
ListNode* ListFind(ListNode* list, DATATYPE x);
// 双向链表在pos的前面进行插入
void ListInsert(ListNode* pos, DATATYPE x);
// 双向链表删除pos位置的节点
void ListErase(ListNode* pos);
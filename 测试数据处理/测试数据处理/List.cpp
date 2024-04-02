#define _CRT_SECURE_NO_WARNINGS
//实现链表头文件的接口

#include "List.h"

//初始化链表
void InitList(Node* pList)
{
	//断言
	assert(pList != NULL);
	pList->data = NULL;
	pList->next = NULL;
}
//销毁链表
void DestroyList(Node* pList)
{
	//断言
	assert(pList != NULL);
	Node* p = pList->next;
	Node* q = NULL;
	while (p != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
	pList->next = NULL;
}

//获取链表长度
int GetLength(Node* pList)
{
	//断言
	assert(pList != NULL);
	int n = 0;
	Node* p = pList->next;
	while (p != NULL)
	{
		n++;
		p = p->next;
	}
	return n;
}

//头部/尾部插入
void PushFront(Node* pList, ListDataType* data)
{
	//断言
	assert(pList != NULL);
	Node* pNew = (Node*)malloc(sizeof(Node));
	if (pNew == NULL)
	{
		exit(EXIT_FAILURE);
	}
	pNew->data = data;
	pNew->next = pList->next;
	pList->next = pNew;
}
void PushBack(Node* pList, ListDataType* data)
{
	//断言
	assert(pList != NULL);
	Node* p = pList;
	while (p->next != NULL)
	{
		p = p->next;
	}
	Node* pNew = (Node*)malloc(sizeof(Node));
	if (pNew == NULL)
	{
		exit(EXIT_FAILURE);
	}
	pNew->data = data;
	pNew->next = NULL;
	p->next = pNew;
}
//头部/尾部删除
void PopFront(Node* pList)
{
	//断言
	assert(pList != NULL);
	Node* p = pList->next;
	if (p != NULL)
	{
		pList->next = p->next;
		free(p);
	}
}
void PopBack(Node* pList)
{
	//断言
	assert(pList != NULL);
	Node* p = pList;
	while (p->next->next != NULL)
	{
		p = p->next;
	}
	Node* q = p->next;
	p->next = NULL;
	free(q);
}
//任意位置插入/删除
void Insert(Node* pList, int pos, ListDataType* data)
{
	//断言
	assert(pList != NULL);
	Node* p = pList;
	int i = 0;
	while (p != NULL && i < pos)
	{
		p = p->next;
		i++;
	}
	if (p != NULL)
	{
		Node* pNew = (Node*)malloc(sizeof(Node));
		if (pNew == NULL)
		{
			exit(EXIT_FAILURE);
		}
		pNew->data = data;
		pNew->next = p->next;
		p->next = pNew;
	}
}
void Erase(Node* pList, int pos)
{
	//断言
	assert(pList != NULL);
	Node* p = pList;
	int i = 0;
	while (p != NULL && i < pos)
	{
		p = p->next;
		i++;
	}
	if (p != NULL && p->next != NULL)
	{
		Node* q = p->next;
		p->next = q->next;
		free(q);
	}
}
#pragma once
//定义链表头文件

#include <assert.h>
#include <stdlib.h>
#include "DataStruct.h"

//链表保存的数据类型
typedef Student ListDataType;

//定义链表结构体
typedef struct Node
{
	ListDataType *data;
	struct Node *next;
} Node;

//初始化链表
void InitList(Node* pList);
//销毁链表
void DestroyList(Node* pList);

//获取链表长度
int GetLength(Node* pList);

//头部/尾部插入
void PushFront(Node* pList, ListDataType* data);
void PushBack(Node* pList, ListDataType* data);
//头部/尾部删除
void PopFront(Node* pList);
void PopBack(Node* pList);
//任意位置插入/删除
void Insert(Node* pList, int pos, ListDataType* data);
void Erase(Node* pList, int pos);
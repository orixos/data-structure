/*
*****************************************************************************
*  @file    1_2_LinkList.c
*  @brief   单链表的C语言实现
*  @author  Orixos
*  @version Beta
*****************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
typedef struct node
{
	ElemType data;
	struct node *next;
} Node;

// 初始化
Node* initList()
{
	Node *head = (Node*)malloc(sizeof(Node));
	head->data = 0;
	head->next = NULL;
	return head;
}

// 创建链表并逆序插入多个元素 
Node* createList(int n)
{
	Node *L = initList();
	for (int i = 0; i < n; i++)
	{
		Node *p = (Node*)malloc(sizeof(Node));
		scanf("%d", &p->data);
		p->next = L->next;
		L->next = p;
	}
	return L;
}

// 头插 
int insertHead(Node *L, ElemType e)
{
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->next = L->next;
	L->next = p;
	return 1;
}

// 尾插 
int insertTail(Node *L, ElemType e)
{
	// 找到尾节点tail
	Node *tail = L;
	while (tail->next != NULL)
	{
		tail = tail->next; 
	}
	// 创建结点
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->next = NULL;
	tail->next = p;
	return 1;
}

// 任意位置插入 
int insertNode(Node *L, int pos, ElemType e)
{
	// 找到插入位置的前驱结点p
	Node *p = L;
	int i = 0;
	while (p && i < pos - 1)
	{
		p = p->next;
		i++;
	}
	if (!p || i > pos - 1)
	{
		printf("元素不存在\n");
		return 0; 
	} 
	// 创建结点
	Node *q = (Node*)malloc(sizeof(Node));
	q->data = e;
	q->next = p->next;
	p->next = q;
	return 1; 
}

// 遍历 
int printList(Node *L)
{
	Node *p = L->next;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
	return 1;
}

// 获取元素 
int getElem(Node *L, int pos, ElemType *e)
{
	Node *p = L->next;
	int i = 1;
	while (p && i < pos)
	{
		p = p->next;
		i++;
	}
	if (!p || i > pos)
	{
		printf("元素不存在\n");
		return 0;
	}
	*e = p->data;
	return 1;
}

// 删除 
int deleteNode(Node *L, int pos, ElemType *e)
{
	// 找到删除位置的前驱结点 
	Node *p = L;
	int i = 0;
	while (p->next && i < pos - 1)
	{
		p = p->next;
		i++;
	}
	if (!p->next || i > pos - 1)
	{
		printf("删除位置错误\n");
		return 0;
	}

	// 记录要删除的节点 
	Node *q = p->next;
	*e = q->data; 
	
	// 要删除节点的前驱节点指向删除节点的后继节点 
	p->next = q->next;
	
	// 释放要删除节点的空间 
	free(q);
	
	// 返回删除元素的数据 
	return 1;
}

// 获取长度 
int getLength(Node *L)
{
	Node *p = L;
	int len = 0;
	while (p != NULL)
	{
		p = p->next;
		len++;
	}
	return len;
}

// 释放 
void freeList(Node *L) 
{
	Node *p = L->next;
	Node *q;
	while (p != NULL) // 链表非空时 
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
}

// 合并 
int mergeList(Node *La, Node *Lb, Node *L)
{
	Node *pa = La->next;
	Node *pb = Lb->next;
	while (pa && pb)
	{
		if (pa->data < pb->data)
		{
			insertTail(L, pa->data);
			pa = pa->next;
		}
		else if (pa->data > pb->data)
		{
			insertTail(L, pb->data);
			pb = pb->next;
		}
		else
		{
			insertTail(L, pa->data);
			pa = pa->next;
			pb = pb->next;
		}
	}
	if (!pa)
	{
		while (pb)
		{
			insertTail(L, pb->data);
			pb = pb->next;
		}
	}
	else if (!pb)
	{
		while (pa)
		{
			insertTail(L, pa->data);
			pa = pa->next;
		}
	}
	
	return 1;
}

int main()
{
	printf("链表基本操作:\n");
	Node *list = initList();
	printf("头插法插入20:\n"); 
	insertHead(list, 20);
	insertHead(list, 10);
	printList(list);
	printf("尾插法插入40:\n"); 
	insertTail(list, 40);
	printList(list);
	printf("在第3个位置插入30:\n");
	insertNode(list, 3, 30);
	printList(list);
	printf("删除第2个位置的元素:\n");
	ElemType e1;
	deleteNode(list, 2, &e1); 
	printList(list);
	printf("获取第2个位置的元素:\n");
	ElemType e2;
	getElem(list, 2, &e2);
	printf("%d\n", e2);
	
	printf("\n");
	
	printf("合并两个顺序排列的链表:\n");
	Node *list1 = initList();
	Node *list2 = initList();
	Node *list0 = initList();
	insertTail(list1, 1);
	insertTail(list1, 3);
	insertTail(list1, 5);
	insertTail(list1, 7);
	insertTail(list1, 9);
	insertTail(list1, 12);
	insertTail(list1, 14);
	insertTail(list2, 2);
	insertTail(list2, 4);
	insertTail(list2, 5);
	insertTail(list2, 6);
	insertTail(list2, 7);
	insertTail(list2, 10);
	printf("第一个链表:\n");
	printList(list1);
	printf("第二个链表:\n");
	printList(list2);
	printf("合并链表:\n");
	mergeList(list1, list2, list0);
	printList(list0);
	
	printf("\n");
	
	printf("逆序创建链表:\n");
	printf("逆序输入5个元素:\n");
	Node *list3 = createList(5);
	printList(list3);
	
	freeList(list);
	freeList(list1);
	freeList(list2);
	freeList(list3); 
	
	return 0;
}

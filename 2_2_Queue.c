/*
*****************************************************************************
*  @file    2_2_Queue.c
*  @brief   队列的C语言实现
*  @author  Orixos
*  @version Beta
*****************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;

typedef struct QueueNode 
{
	ElemType data;
	struct QueueNode *next;
} QueueNode;

typedef struct
{
	QueueNode *front;
	QueueNode *rear;
} Queue;

// 初始化
Queue* initQueue()
{
	Queue *q = (Queue*)malloc(sizeof(Queue));
	QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
	if (!node)
	{
		exit(0);
	}
	node->data = 0;
	node->next = NULL;
	q->front = node;
	q->rear = node;
	return q;
}

// 判空
int isEmpty(Queue *q)
{
	if (q->front == q->rear)
	{
		return 1;
	}
	return 0;
} 

// 入队 
int enqueue(Queue *q, ElemType e)
{
	QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
	if (!node)
	{
		exit(0);
	}
	node->data = e;
	node->next = NULL;
	q->rear->next = node;
	q->rear = node;
	return 1;
}

// 出队
int dequeue(Queue *q, ElemType *e)
{
	if (isEmpty(q))
	{
		printf("队空\n");
		return 0;
	}
	QueueNode *node = q->front->next;
	*e = node->data;
	q->front->next = node->next;
	
	// 如果队列中头结点后面只有一个结点，则该结点被删除，需要重新调整rear的指向，否则会指向node
	// 如果队列中不止一个结点，则出队过程不影响rear的指向 
	if (q->rear == node)
	{
		q->rear = q->front;
	}
	
	free(node);
	return 1;
}

// 销毁队列
int destroyQueue(Queue *q)
{
	while (q->front)
	{
		q->rear = q->front->next;
		free(q->front);
		q->front = q->rear;
	}
	return 1;
}
/* 
int destroyQueue(Queue *q)
{
	QueueNode *node; // 由于没有用到rear，node可以由rear替代，避免创建新的变量 
	while (q->front)
	{
		node = q->front->next;
		free(q->front);
		q->front = node;
	}
	return 1;
}
*/

// 清空队列
int clearQueue(Queue *q)
{
	ElemType e_tmp;
	while (q->front != q->rear)
	{
		dequeue(q, &e_tmp);
	}
	return 1;
} 

// 获取长度 
int getLength(Queue *q)
{
	int length = 0;
	QueueNode *node = q->front; 
	while (node != q->rear)
	{
		length++;
		node = node->next;
	}
	return length;
}

// 获取队头元素
int getHead(Queue *q, ElemType *e)
{
	if (isEmpty(q))
	{
		printf("队空\n");
		return 0;
	}
	*e = q->front->next->data;
	return 1;
}

// 遍历队列
int traverseQueue(Queue *q)
{
	QueueNode *node = q->front->next;
	while (node)
	{
		printf("%d ", node->data);
		node = node->next;
	}
	printf("\n");
	return 1;
} 

int main()
{
	Queue *q = initQueue();
	
	printf("入队10, 20, 30:\n");
	enqueue(q, 10);
	enqueue(q, 20);
	enqueue(q, 30);
	printf("队列长度为%d\n", getLength(q));
	ElemType e;
	getHead(q, &e);
	printf("队头为%d\n", e);
	printf("\n");
	
	dequeue(q, &e);
	printf("出队, 元素为%d\n", e);
	getHead(q, &e);
	printf("队头为%d\n", e);
	printf("遍历队列:\n");
	traverseQueue(q);
	printf("\n");
	
	printf("清空队列:\n");
	clearQueue(q);
	printf("队列长度为%d\n", getLength(q));
	printf("入队40, 50:\n");
	enqueue(q, 40);
	enqueue(q, 50);
	printf("队列长度为%d\n", getLength(q));
	getHead(q, &e);
	printf("队头为%d\n", e);
	printf("\n");
	
	destroyQueue(q);
	
	return 0;
}

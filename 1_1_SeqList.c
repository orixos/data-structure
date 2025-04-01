#include <stdio.h>
#define LIST_INCREMENT 10 
typedef int ElemType;
typedef struct
{
	ElemType *data;
	int length;
	int maxSize;
} SeqList;

// 初始化顺序表 
SeqList* initList(int size)
{
	SeqList *L = (SeqList*)malloc(sizeof(SeqList));
	L->data = (ElemType*)malloc(sizeof(ElemType) * L->maxSize);
	if (!L->data)
	{
		printf("分配空间失败\n");
		return;
	}
	L->length = 0;
	L->maxSize = size;
	return L;
} 

// 判断顺序表是否为空 
int isEmpty(SeqList *L)
{
	if (L->length == 0)
	{
		return 1;
	}
	return 0;
}

// 清空顺序表 
int clearList(SeqList *L)
{
	L->length = 0;
	return 1;
}

// 销毁顺序表 
int destroyList(SeqList *L)
{
	free(L->data);
	free(L);
	return 1; 
}

// 获取顺序表长度 
int getLength(SeqList *L)
{
	return L->length;
}

// 获取元素
ElemType getElem(SeqList *L, int pos)
{
	return L->data[pos - 1]; 
} 

// 向末尾添加元素 
int appendElem(SeqList *L, ElemType e)
{
	if (L->length >= L->maxSize)
	{
		printf("顺序表已满\n");
		return 0;
	}
	L->data[L->length] = e;
	L->length++;
	return 1;
}

// 遍历顺序表 
int printList(SeqList *L)
{
	for (int i = 0; i < L->length; i++)
	{
		printf("%d ", L->data[i]);
	}
	printf("\n");
	return 1;
}

// 插入元素
int insertElem(SeqList *L, int pos, ElemType e) // pos范围为1 ~ L->length 
{
	if (pos < 1 || pos > L->length)
	{
		printf("插入位置不合法\n");
		return 1;
	}
	if (L->length >= L->maxSize)
	{
		printf("顺序表已满，重新分配空间\n");
		ElemType *newBase = (ElemType*)realloc(L->data, (L->maxSize + LIST_INCREMENT) * sizeof(ElemType));
		if (!newBase)
		{
			printf("分配空间失败\n");
			return 0;
		}
		L->data = newBase;
		L->maxSize += LIST_INCREMENT;
	}
	if (pos <= L->length)
	{
		for (int i = L->length - 1; i >= pos - 1; i--)
		{
			L->data[i + 1] = L->data[i];
		}
		L->data[pos - 1] = e;
		L->length++;
	}
	return 1;
}

// 删除元素
int deleteElem(SeqList *L, int pos, ElemType *e) 
{
	if (isEmpty(L))
	{
		printf("空表\n");
		return 0;
	}
	if (pos < 1 || pos > L->length)
	{
		printf("删除位置不合法\n");
		return 0;
	}
	*e = L->data[pos - 1];
	if (pos < L->length) // 如果pos==L->length，则跳过下面的if，直接执行L->length--
	{
		for (int i = pos; i < L->length; i++)
		{
			L->data[i - 1] = L->data[i];
		}
	}
	L->length--;
	return 1;
} 

// 查找元素
int locateElem(SeqList *L, ElemType e)
{
	if (isEmpty(L))
	{
		printf("空表\n");
		return 0;
	}
	
	int i = 1;
	ElemType *p = L->data;
	while (i <= L->length && *(p++) != e)
	{
		i++;
	}
	if (i <= L->length)
	{
		return i;
	}
	else
	{
		return 0;
	}

	/*
	for (int i = 0; i < L->length; i++)
	{
		if (L->data[i] == e)
		{
			return i + 1;
		}
	}
	*/
	
	return 0;
}

int main()
{
	// 构造顺序表 
	printf("构造顺序表: \n");
	SeqList *list = initList(4);
	appendElem(list, 1);
	appendElem(list, 2);
	appendElem(list, 4);
	printList(list);
	printf("\n");
	
	// 插入元素 
	printf("在位置3插入元素3:\n");
	insertElem(list, 3, 3);
	printList(list);
	printf("\n");
	
	printf("在位置3插入元素10:\n");
	insertElem(list, 3, 10);
	printList(list);
	printf("\n");
	
	// 删除元素 
	ElemType e;
	printf("删除第2个元素:\n");
	deleteElem(list, 2, &e);
	printf("删除元素数据为: %d\n", e);
	printList(list);
	printf("\n");
	
	// 查找元素
	printf("元素3的位置为: %d\n", locateElem(list, 3));
	printf("元素2的位置为: %d\n", locateElem(list, 2));
	printf("第2个位置的元素为: %d\n", getElem(list, 2));
	
	destroyList(list);
	
	return 0;
}

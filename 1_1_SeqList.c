/*
*****************************************************************************
*  @file    1_1_SeqList.c
*  @brief   顺序表的C语言实现
*  @author  Orixos
*  @version Beta
*****************************************************************************
*/

#include <stdio.h>
#include <stdlib.h> 
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
	L->maxSize = size;
	L->data = (ElemType*)malloc(sizeof(ElemType) * L->maxSize);
	if (!L->data)
	{
		printf("分配空间失败\n");
		exit(0);
	}
	L->length = 0;
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

// 获取顺序表最大长度
int getMaxLength(SeqList *L)
{
	return L->maxSize;
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
		printf("顺序表为空\n");
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

// 获取元素
int getElem(SeqList *L, int pos, ElemType *e)
{
	if (pos > L->length)
	{
		return 0;
	}
	*e = L->data[pos - 1];
	return 1;
} 
 
// 查找元素
int locateElem(SeqList *L, ElemType e)
{
	if (isEmpty(L))
	{
		printf("顺序表为空\n");
		return -1;
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
}

// 对顺序表元素从小到大排序
int sortList(SeqList *L)
{
	for (int i = 0; i < L->length - 1; i++)
	{
		for (int j = 0; j < L->length - 1; j++)
		{
			if (L->data[j] > L->data[j + 1])
			{
				ElemType tmp;
				tmp = L->data[j];
				L->data[j] = L->data[j + 1];
				L->data[j + 1] = tmp;
			}
		}
	}
	return 1;
} 

// 合并两个顺序表
int mergeList(SeqList *list1, SeqList *list2, SeqList *list)
{
	// 顺序排列 
	sortList(list1);
	sortList(list2); 
	
	// 合并 
	int pos1 = 0;
	int pos2 = 0;
	ElemType p1 = list1->data[pos1];
	ElemType p2 = list2->data[pos2];
	
	while (1)
	{
		if (p1 < p2)
		{
			appendElem(list, p1);
			pos1++;
		}
		else if (p1 > p2)
		{
			appendElem(list, p2);
			pos2++;
		}
		else
		{
			appendElem(list, p1);
			pos1++;
			pos2++;
		}
		p1 = list1->data[pos1];
		p2 = list2->data[pos2];
		
		if (pos1 >= list1->length)
		{
			for (int i = pos2; i < list2->length; i++)
			{
				appendElem(list, list2->data[i]);
			}
			break;
		}
		else if (pos2 >= list2->length)
		{
			for (int i = pos1; i < list1->length; i++)
			{
				appendElem(list, list1->data[i]);
			}
			break;
		}
	}
	
	return 1;
}

int main()
{
	printf("1: 顺序表基本操作\n\n");
	
	// 构造顺序表 
	printf("构造顺序表，插入元素1、2、4: \n");
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
	printf("当前顺序表最大长度为: %d\n", getMaxLength(list));
	printf("\n");
	
	// 删除元素 
	ElemType deletedElem;
	printf("删除第2个元素:\n");
	deleteElem(list, 2, &deletedElem);
	printf("删除元素数据为: %d\n", deletedElem);
	printList(list);
	printf("\n");
	
	// 查找元素
	printf("元素3的位置为: %d\n", locateElem(list, 3));
	printf("元素2的位置为: %d\n", locateElem(list, 2));
	
	// 获取元素 
	ElemType pointedElem;
	getElem(list, 2, &pointedElem);
	printf("第2个位置的元素为: %d\n", pointedElem);
	printf("\n");
	
	// 清空和获取长度 
	printf("清空顺序表后插入元素6:\n");
	clearList(list);
	appendElem(list, 6);
	printList(list);
	printf("当前顺序表长度为: %d\n", getLength(list));
	printf("\n");
	
	// 销毁顺序表
	destroyList(list);
	
	printf("\n");
	
	// 合并顺序表 
	printf("2: 合并顺序表:\n\n");
	SeqList *mergedList = initList(100);
	SeqList *list1 = initList(100);
	SeqList *list2 = initList(100);
	appendElem(list1, 5);
	appendElem(list1, 3);
	appendElem(list1, 1);
	appendElem(list2, 3);
	appendElem(list2, 2);
	appendElem(list2, 6);
	printf("第1个顺序表:\n");
	printList(list1);
	printf("第2个顺序表:\n");
	printList(list2);
	mergeList(list1, list2, mergedList);
	printf("合并后顺序表:\n");
	printList(mergedList);
	
	destroyList(list1);
	destroyList(list2);
	destroyList(mergedList);
	
	return 0;
}

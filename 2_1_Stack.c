/*
*****************************************************************************
*  @file    2_1_Stack.c
*  @brief   栈的C语言实现
*  @author  Orixos
*  @version Beta
*****************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#define INIT_SIZE 5
#define INCREMENT_SIZE 10
typedef int ElemType;
typedef struct
{
	ElemType *base; // 栈底地址 
	ElemType *top; // 栈顶 
	int stacksize;
} Stack;

// 初始化
Stack* initStack()
{
	Stack *s = (Stack*)malloc(sizeof(Stack));
	s->base = (ElemType*)malloc(INIT_SIZE * sizeof(ElemType) + 1); // 如果不写+1，可能在栈满重新分配空间时丢失栈顶元素 
	s->top = s->base;
	s->stacksize = INIT_SIZE;
	return s;
}

// 判空 
int isEmpty(Stack *s)
{
	if (s->top == s->base)
	{
		return 1;
	}
	return 0;
}

// 获取栈顶元素
int getTop(Stack *s)
{
	if (isEmpty(s))
	{
		printf("栈空\n");
		return 0;
	}
	printf("栈顶: %d\n", *(s->top));
	return 1;
}
/*
int getTop(Stack *s, ElemType *e)
{
	*e = *(s->top);
}
*/

// 获取长度
int getLength(Stack *s)
{
	printf("长度: %d\n", (s->top - s->base));
	return 1;
}
/*
int getLength(Stack *s)
{
	return (s->top - s->base);
}
*/

// 入栈
int push(Stack *s, ElemType e)
{
	if (s->top - s->base >= s->stacksize) // 栈满 
	{
		printf("栈满，重新分配空间\n");
		s->base = (ElemType*)realloc(s->base, (s->stacksize + INCREMENT_SIZE) * sizeof(ElemType));
		if (!s->base)
		{
			printf("分配空间失败\n");
			exit(0);
		}
		s->top = s->base + s->stacksize; 
		s->stacksize += INCREMENT_SIZE;
	}
	s->top++;
	*(s->top) = e; // 写为 s->top = &e 不可行 
	return 1;
} 

// 出栈
int pop(Stack *s, ElemType *e)
{
	if (isEmpty(s))
	{
		printf("栈空\n");
		return 0;
	} 
	*e = *(s->top);
	s->top--;
	return 1;
} 

// 销毁
int destroyStack(Stack *s)
{
	free(s->base);
	free(s);
	return 1; 
}

// 清空
int clearStack(Stack *s)
{
	ElemType e_tmp;
	while (!isEmpty(s))
	{
		pop(s, &e_tmp);
	}
	return 1;
}

// 遍历
int traverseStack(Stack *s)
{
	if (isEmpty(s))
	{
		printf("栈空\n");
		return 0;
	}
	for (int i = 1; i <= (s->top - s->base); i++)
	{
		printf("%d ", *(s->base + i));
	}
	printf("\n");
	return 1;
}
/*
int traverseStack(Stack *s) // 用于调试 
{
	printf("遍历:\n");
	if (isEmpty(s))
	{
		printf("栈空\n");
		return 0;
	}
	for (int i = 1; i <= (s->top - s->base); i++)
	{
		printf("%d, %zu\n", *(s->base + i), (s->base + i));
		// printf("%d ", *(s->base + i));
	}
	// printf("\n");
	return 1;
} 
*/

int main()
{
	Stack *s = initStack();
	
	printf("依次入栈1, 2, 3:\n");
	push(s, 1);
	getTop(s);
	push(s, 2);
	getTop(s);
	push(s, 3);
	getTop(s);
	getLength(s);
	traverseStack(s);
	printf("\n");

	printf("出栈:\n");
	ElemType e1;
	pop(s, &e1);
	printf("出栈元素为: %d\n", e1);
	getTop(s);
	printf("\n");
	
	printf("清空栈:\n");
	clearStack(s);
	getTop(s);
	getLength(s);
	printf("\n");
	
	printf("依次入栈1, 2, 3, 4, 5, 6:\n");
	push(s, 1);
	getTop(s);
	push(s, 2);
	getTop(s);
	push(s, 3);
	getTop(s);
	push(s, 4);
	getTop(s);
	push(s, 5);
	getTop(s);
	// traverseStack(s);
	push(s, 6);
	getTop(s);
	printf("当前栈最大长度为: %d\n", s->stacksize);
	traverseStack(s);
	
	destroyStack(s);
	return 0;
}

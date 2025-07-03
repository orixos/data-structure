/*
 *****************************************************************************
 * @file    Example_1_Polynomial.c
 * @brief   利用单链表进行多项式运算
 * @author  Orixos
 * @version Beta
 ********************************************************************************************************************
 * @attention
 * 1. 程序功能: 利用单链表实现多项式的加、减、乘和求值运算。
 * 2. 输入格式: 第1行为多项式1，第2行为多项式2，第3行为自变量x（用于求值）。多项式的每一项按照系数和指数的括号-逗号有序数对输入，不同项之间用逗号分隔。支持输入多个自变量，每个自变量之间用逗号分隔。
 * 3. 示例输入:
 *    (1,1),(2,2),(-1,2),(1,0),(0,4)
 *    (1,1),(2,0) 
 *    1,-1,0,2 
 * 4. 注: 链表存储采用升幂排列。程序中所有%.0f用于将系数输出为整数，将0改为正整数可实现输出小数。
 ********************************************************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
typedef struct term
{
	float coef; // 系数 
	int expn; // 指数 
	struct term *next; // 后继 
} Term;

/* 初始化多项式链表 */ 
Term* initPol()
{
	Term* A = (Term*)malloc(sizeof(Term));
	A->coef = -97.5; // 防止第一项为常数项时出现错误 
	A->expn = -97;
	A->next = NULL;
	return A;
} 

/* 将多项式的一项插入链表 */ 
int insert(Term *A, float c, int e)
{
	if (c == 0) // 如果系数为0则不插入 
	{
		return 0;
	}
	
	Term *p = A;
	int flag = 0; // 是否到达末尾都没有找到更大的指数 
	
	while (p->next)
	{
		if (p->next->expn > e) // 若下一项指数大于要插入的指数，则在当前项后面插入 
		{
			flag = 1;
			break;
		}
		else
		{
			p = p->next;
		}
	}
	
	if (flag == 0) // 如果到达末尾都没有找到更大的指数，则将p设为末尾，在末尾后面插入 
	{
		p = A;
		while (p->next)
		{
			p = p->next;
		}
	}
	
	if (p->expn == e) // 如果指数已经存在
	{
		float tmp_c = p->coef + c;
		if (tmp_c == 0) // 如果累加后和为0，则删去该项 
		{
			Term *q = A;
			while (q->next != p)
			{
				q = q->next;
			}
			q->next = p->next;
			free(p);
		}
		else // 否则合并 
		{
			p->coef = tmp_c;
		}
		return 1;
	}
	else // 如果指数不存在，则创建新项
	{
		Term *newTerm = (Term*)malloc(sizeof(Term)); 
		newTerm->coef = c;
		newTerm->expn = e;
		newTerm->next = p->next;
		p->next = newTerm;
		return 1;		
	}
}

/* 将用户输入转化为多项式 */
// 用户输入格式：(c1,e1),(c2,e2)
int input(Term* A, char str[])
{
	char *p = str;
	int num1 = 0, num2 = 0;
	int state = 0; // 0为中间状态，1为提取第1个数，2为提取第2个数 
	int symbol1 = 1, symbol2 = 1; // -1为取相反数 
	
	while (*p != '\0')
	{
		char ch = *p;
		if (ch == '(') // 检测到左括号准备提取第1个数 
		{
			state = 1;
		}
		else if (ch == ',') // 检测到逗号准备提取第2个数 
		{
			state = 2; // 检测到中间逗号后state=2，接着检测到左括号state=1，故无影响 
		}
		else if (ch == ')') // 检测到右括号结束提取 
		{
			insert(A, num1 * symbol1, num2 * symbol2);
			num1 = 0; num2 = 0;
			state = 0;
			symbol1 = 1; symbol2 = 1;
		}
		else if (ch == '-') // 检测到负号对当前数取相反数 
		{
			if (state == 1) symbol1 = -1;
			else if (state == 2) symbol2 = -1;
		}
		else
		{
			if (state == 1)
			{
				num1 = num1 * 10 + (ch - '0'); // 提取第1个数
			}
			else if (state == 2)
			{
				num2 = num2 * 10 + (ch - '0'); // 提取第2个数
			}
		}
		
		p++;
	}
	
	return 1;
} 

/* 输出多项式 */
int output(Term *A)
{
	Term *p = A->next;
	
	if (p == NULL)
	{
		printf("0");
	}
	
	while (p)
	{
		if (p->coef > 0) // 系数大于0，分情况考虑输出+ 
		{
			if (p == A->next) // 如果是第一项且为正，不输出+ 
			{
				if (p->expn == 0) // 指数为0输出常数项 
				{
					printf("%.0f", p->coef);
				}
				else if (p->expn == 1) // 指数为1不输出指数符号 
				{
					if (p->coef == 1.0) printf("x");
					else printf("%.0fx", p->coef);
				}
				else
				{
					if (p->coef == 1.0) printf("x^%d", p->expn);
					else printf("%.0fx^%d", p->coef, p->expn);
				}
			}
			else 
			{
				if (p->expn == 0) // 指数为0输出常数项 
				{
					printf("+%.0f", p->coef);
				}
				else if (p->expn == 1) // 指数为1不输出指数符号 
				{
					if (p->coef == 1.0) printf("+x");
					else printf("+%.0fx", p->coef);
				}
				else
				{
					if (p->coef == 1.0) printf("+x^%d", p->expn);
					else printf("+%.0fx^%d", p->coef, p->expn);
				}
			}
		}
		else if (p->coef < 0) // 系数小于0，分情况考虑输出- 
		{
			if (p->expn == 0) // 指数为0输出常数项 
			{
				printf("%.0f", p->coef);
			} 
			else if (p->expn == 1) // 指数为1不输出指数符号 
			{
				if (p->coef == -1.0) printf("-x");
				else printf("%.0fx", p->coef);
			}
			else
			{
				if (p->coef == -1.0) printf("-x^%d", p->expn);
				else printf("%.0fx^%d", p->coef, p->expn);
			}
		}
		
		p = p->next;
	}
	
	printf("\n");
	return 1; 
}

/* 多项式求值 */ 
float calc(Term *A, float x)
{
	Term *p = A->next;
	float value = 0.0;
	while (p)
	{
		value += pow(x, p->expn) * p->coef;
		p = p->next;
	}
	return value;
}

/* 相加 */ 
int add(Term *A, Term *B, Term *C)
{
	Term *r = C;
	Term *p = A->next, *q = B->next;
	Term *newTerm;
	while (p && q)
	{
		if (p->expn == q->expn) // 指数相等
		{
			float tmp = p->coef + q->coef;
			if (tmp != 0) // 相加后系数不为0 
			{
				newTerm = (Term*)malloc(sizeof(Term));
				r->next = newTerm; r = r->next;
				r->coef = tmp; r->expn = p->expn;
			}
			p = p->next; q = q->next;
		}
		else // 指数不相等 
		{
			newTerm = (Term*)malloc(sizeof(Term));
			r->next = newTerm; r = r->next;
			if (p->expn < q->expn) // p指数小 
			{
				r->coef = p->coef; r->expn = p->expn;
				p = p->next;
			} 
			else // q指数小 
			{
				r->coef = q->coef; r->expn = q->expn;
				q = q->next;
			}
		}
	}
	p = p ? p : q; // p指向剩余部分 
	while (p)
	{
		newTerm = (Term*)malloc(sizeof(Term));
		r->next = newTerm; r = r->next;
		r->coef = p->coef; r->expn = p->expn;
		p = p->next;
	}
	r->next = NULL;
	return 1;
}

/* 相减 */ 
int sub(Term *A, Term *B, Term *C)
{
	Term *r = C;
	Term *p = A->next, *q = B->next;
	Term *newTerm;
	while (p && q)
	{
		if (p->expn == q->expn) // 指数相等
		{
			float tmp = p->coef - q->coef;
			if (tmp != 0) // 相减后系数不为0 
			{
				newTerm = (Term*)malloc(sizeof(Term));
				r->next = newTerm; r = r->next;
				r->coef = tmp; r->expn = p->expn;
			}
			p = p->next; q = q->next;
		}
		else // 指数不相等 
		{
			newTerm = (Term*)malloc(sizeof(Term));
			r->next = newTerm; r = r->next;
			if (p->expn < q->expn) // p指数小 
			{
				r->coef = p->coef; r->expn = p->expn;
				p = p->next;
			} 
			else // q指数小 
			{
				r->coef = -(q->coef); r->expn = q->expn;
				q = q->next;
			} 
		}
	}
	
	int leftFlag = 1; // 剩余部分为p则为1，为q则为-1 
	if (q) // 剩余部分为q
	{
		leftFlag = -1;
		p = q;
	}
	
	while (p)
	{
		newTerm = (Term*)malloc(sizeof(Term));
		r->next = newTerm; r = r->next;
		r->coef = leftFlag * (p->coef); // 剩余部分若为q则乘leftFlag=-1取相反数
		r->expn = p->expn;
		p = p->next;
	}

	r->next = NULL;
	return 1;
}

/* 相乘 */ 
int mul(Term *A, Term *B, Term *C)
{
	Term *p, *q, *r, *pr, *newTerm;
	for (p = A->next; p; p = p->next)
	{
		for (q = B->next; q; q = q->next)
		{
			double tmp_c = p->coef * q->coef;
			int tmp_e = p->expn + q->expn;
			// 在C中查找插入位置
			pr = C; r = C->next;
			while (r && r->expn < tmp_e)
			{
				pr = r; r = r->next;
			}
			if (r && r->expn == tmp_e) // 有与新项指数相等的项 
			{
				if (r->coef + tmp_c != 0) // 合并后系数不为0则合并 
				{
					r->coef += tmp_c;
				}
				else // 否则删除 
				{
					pr->next = r->next;
					free(r);
				}
			}
			else // 无与新项指数相等的项则创建新项 
			{
				newTerm = (Term*)malloc(sizeof(Term));
				newTerm->expn = tmp_e; newTerm->coef = tmp_c;
				pr->next = newTerm; newTerm->next = r;
			}
		}
	}
	return 1; 
}

/* 解析用户输入的x并求值输出 */
// 用户输入格式：x1,x2,x3 
int getAllValue(Term *PolAdd, Term *PolSub, Term *PolMul, char str[])
{
	char *p = str; 
	int num = 0, state = 1; 
	int symbol = 1;
	
	while (1)
	{
		if (state == 0)
		{
			state = 1;
			p++;
			continue;
		}
		else
		{
			if ((*p) == '-') // 如果读取到负号，则symbol变为-1，求值时乘-1取相反数 
			{
				symbol = -1;
				p++; 
				continue;
			}
			num = num * 10 + ((*p) - '0');
			p++;
			if ((*p) == ',') // 若下一个字符为逗号，则将当前的num求值并清空num/state/symbol 
			{
				printf("x = %d时，和为%.0f\n", symbol * num, calc(PolAdd, symbol * num));
				printf("x = %d时，差为%.0f\n", symbol * num, calc(PolSub, symbol * num));
				printf("x = %d时，积为%.0f\n", symbol * num, calc(PolMul, symbol * num));
				num = 0;
				symbol = 1;
				state = 0;
			}
			else if ((*p) == '\0') // 若检测到结尾，则将当前的num求值并结束 
			{
				printf("x = %d时，和为%.0f\n", symbol * num, calc(PolAdd, symbol * num));
				printf("x = %d时，差为%.0f\n", symbol * num, calc(PolSub, symbol * num));
				printf("x = %d时，积为%.0f\n", symbol * num, calc(PolMul, symbol * num));
				break;
			}
		}
	}
	return 1;
}

int main()
{	 
	/* 用户输入 */ 
	char Pol_A[81]; // 指定字符串长度 
	char Pol_B[81];
	char x[81];
	
	printf("请输入多项式1: ");
	scanf("%80s", Pol_A); // %80s用于限制输入长度以避免溢出 
	printf("请输入多项式2: "); 
	scanf("%80s", Pol_B);
	printf("请输入自变量x: ");
	scanf("%80s", x);
	
	/* 处理用户输入，构造多项式链表 */ 
	Term *A = initPol();
	Term *B = initPol();
	
	input(A, Pol_A);
	input(B, Pol_B); 
	
	printf("\n");
	
	/* 输出多项式 */ 
	printf("多项式1: "); output(A);
	printf("多项式2: "); output(B);
	
	/* 输出和多项式 */ 
	Term *PolAdd = initPol();
	add(A, B, PolAdd);
	printf("和多项式: "); output(PolAdd);

	/* 输出差多项式 */ 
	Term *PolSub = initPol();
	sub(A, B, PolSub);
	printf("差多项式: "); output(PolSub);
	
	/* 输出积多项式 */ 
	Term *PolMul = initPol();
	mul(A, B, PolMul);
	printf("积多项式: "); output(PolMul);
	
	/* 输出求值结果 */ 
	getAllValue(PolAdd, PolSub, PolMul, x);
	
	/*
  //以下内容用于测试
	insert(A, 1, 1);
	insert(A, 3, 2);
	insert(A, 1, 0);
	//insert(A, -5, 3);
	//insert(A, -5, 10); 
	insert(B, 1, 1);
	insert(B, -3, 2);
	insert(B, -6, 3);
	insert(B, -1, 0);
	//insert(B, -5, 4);
	//insert(B, 9, 11);
	*/
	
	return 0;
}

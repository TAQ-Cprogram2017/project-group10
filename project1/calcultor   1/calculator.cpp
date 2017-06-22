#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include"function.h"
int main(void)
{
	char a[100];
	double x;
	OPTR_STACK * point_OPTR;//创建符号栈的结构体指针
	point_OPTR = NEW_OPTR;//指针初始化
	OPND_STACK * point_OPND;//创建数字栈的结构体指针
	point_OPND = NEW_OPND;//指针初始化
	InitOPTR_Stack(point_OPTR);//创建符号栈
	InitOPND_Stack(point_OPND);//创建数字栈

	while (1)
	{
		int b = 1;
		printf("请选择计算模式");
		scanf("%d", &b);

		if (b == 1)
		{
			printf("请输入函数以及变量x的数值\t");
			scanf("%s", &a);
			printf("x=");
			scanf("%lf", &x);
			read(x, point_OPTR, point_OPND,a);
			int n = OPND_StackLength(point_OPND);
			if (n == 1)
				printf("%lf\n", GetTop_OPND(point_OPND));
			else
			{
				printf("Error!\n");
			}
			system("pause");
		}
		if (b == 2)
		{
			int  a, b, c, d, m, n;
			printf("请输入要转换的数：\n");
			scanf("%d", &c);
			printf("请输入要转换数的进制数：\n");
			scanf("%d", &d);
			n = b_TranceDec(c, d);
			printf("%d\n", n);
			printf("请输入要转换的数：\n");
			scanf("%d", &a);
			printf("请输进制数：\n");
			scanf("%d", &b);
			m = DecTrance_b(a, b);
			printf("%d\n", m);
		}
		if (b == 3)
		{
			printf("请输入要分解的数字");
		}

		ClearOPTR_Stack(point_OPTR);
		ClearOPND_Stack(point_OPND);
	}

	return 0;
}
int round(int a, int b)//form a function that can tell you the largest integer smaller than business
{//a:dividend,b:divisor,
	int c, i;
	c = a - b;//calculate the difference value between 'a' and 'b' , put a 'b' out of an 'a'
	if (c<0)//a<b,the business is 0
		i = 0;
	else//a>b
	{
		i = 0;//count how many times does the subtraction do
		while (c >= 0)//loop until a<b
		{
			i++;
			c = c - b;
		}
	}
	return i;//the answer of the largest integer smaller than business 
}
int pow(int a, int b)//calculate a^b
{
	int i, c, d = 1;
	if (b == 0)//if the index is 0 , the answer is 1
		c = 1;
	else
	{
		for (i = 1; i <= b; i++)//when index more than one
		{
			c = a * d;
			d = c;
		}
	}
	return c;
}
int DecTrance_b(int a, int b)
{
	int c, d = a, h = 0, i = 0;
	while (d >= 1)
	{
		c = d%b;
		d = round(d, b);
		h = h + (c*pow(10, i));
		i = i + 1;
	}

	return h;
}
int b_TranceDec(int a, int b)
{
	int c = a, d, h = 0, i = 0;
	while (c > 0)
	{
		d = c % 10;
		c = (c - d) / 10;
		h = h + d*pow(b, i);
		i++;
	}
	return h;
}
int InitOPTR_Stack(OPTR_STACK *S)
{
	S->base = (OPTR_TYPE *)malloc(STACK_INIT_SIZE * sizeof(OPTR_TYPE));

	if (S->base == NULL)
	{
		printf("Error.\n");
		return Error;
	}

	S->top = S->base;
	S->stackSize = STACK_INIT_SIZE;

	return OK;
}
int InitOPND_Stack(OPND_STACK *S)
{
	S->base = (OPND_TYPE *)malloc(STACK_INIT_SIZE * sizeof(OPND_TYPE));

	if (S->base == NULL)
	{
		printf("Error.\n");
		return Error;
	}

	S->top = S->base;
	S->stackSize = STACK_INIT_SIZE;

	return OK;
}
void DestroyOPTR_Stack(OPTR_STACK *S)
{
	free(S->base);
	S->base = NULL;
	S->stackSize = 0;
	S->top = NULL;
}
void DestroyOPND_Stack(OPND_STACK *S)
{
	free(S->base);
	S->base = NULL;
	S->stackSize = 0;
	S->top = NULL;
}
void ClearOPTR_Stack(OPTR_STACK *S)
{
	S->top = S->base;
}
void ClearOPND_Stack(OPND_STACK *S)
{
	S->top = S->base;
}
int OPTR_StackEmpty(OPTR_STACK *S)
{
	if (S->top == S->base)
		return True;
	else
		return False;
}
int OPND_StackEmpty(OPND_STACK *S)
{
	if (S->top == S->base)
		return True;
	else
		return False;
}
int OPTR_StackLength(OPTR_STACK *S)
{
	return S->top - S->base;
}
int OPND_StackLength(OPND_STACK *S)
{
	return S->top - S->base;
}
bool Push_OPTR(OPTR_STACK *S, OPTR_TYPE d)
{
	if (OPTR_StackLength(S) >= S->stackSize)
	{
		S->base = (OPTR_TYPE *)realloc(S->base, (STACK_INIT_SIZE + STACK_INCREMENT) * sizeof(OPTR_TYPE));
		if (!S->base)
			return Error;

		S->stackSize += STACK_INCREMENT;
	}

	*S->top = d;
	S->top++;

	return OK;
}
bool Push_OPND(OPND_STACK *S, OPND_TYPE d)
{
	if (OPND_StackLength(S) >= S->stackSize)
	{
		S->base = (OPND_TYPE *)realloc
		(S->base, (STACK_INIT_SIZE + STACK_INCREMENT) * sizeof(OPND_TYPE));

		if (!S->base)
			return Error;

		S->stackSize += STACK_INCREMENT;
	}

	*S->top = d;
	S->top++;

	return OK;
}
bool Pop_OPTR(OPTR_STACK *S, OPTR_TYPE *d)
{

	if (OPTR_StackEmpty(S))
	{
		printf("This Stack is Empty.\n");
		return Error;
	}
	else
	{
		*d = *(--S->top);
		return OK;
	}
}
bool Pop_OPND(OPND_STACK *S, OPND_TYPE *d)
{
	if (OPND_StackEmpty(S))
	{
		printf("This Stack is Empty.\n");
		return Error;
	}
	else
	{
		*d = *(--S->top);
		return OK;
	}
}
char GetTop_OPTR(OPTR_STACK *S)
{
	OPTR_TYPE *d = S->top;

	if (OPTR_StackEmpty(S))
	{
		printf("This Stack is Empty.\n");
		return Error;
	}
	else
	{
		*d = *(S->top - 1);
		return *d;
	}
}
double GetTop_OPND(OPND_STACK *S)
{
	OPND_TYPE *d = S->top;

	if (OPND_StackEmpty(S))
	{
		printf("This Stack is Empty.\n");
		return Error;
	}
	else
	{
		*d = *(S->top - 1);
		return *d;
	}
}
double change (int i,char a[])
{
	double num=0;
	int q = -1;
	int j = i;
	while (a[i] >= '0'&&a[i] <= '9')
	{
		num = num * 10 + (int)a[i] - 48;
		j++;
	}
	if (a[i] == '.')
	{
		j++;
		while (a[i] >= '0'&&a[i] <= '9')
		{
			num = num + ((int)a[i] - 48)*pow(10, q--);
			j++;
		}
	}return num;
}
char priority(char pre, char *c)
{
	switch (pre)
	{
	case '+':
		switch (*c)
		{
		case '+':	return '>';	break;
		case '-':	return '>';	break;
		case '*':	return '<';	break;
		case '^':	return '<';	break;
		case '/':	return '<';	break;
		case '(':	return '<';	break;
		case ')':	return '>';	break;
		case '#':	return '>';	break;
		case 's':	return '<';	break;
		case 'c':	return '<';	break;
		case 't':	return '<';	break;
		case 'n':	return '<';	break;
		case 'g':	return '<';	break;
		default:break;
		}
	case '-':
		switch (*c)
		{
		case '+':	return '>';	break;
		case '-':	return '>';	break;
		case '*':	return '<';	break;
		case '^':	return '<';	break;
		case '/':	return '<';	break;
		case '(':	return '<';	break;
		case ')':	return '>';	break;
		case '#':	return '>';	break;
		case 's':	return '<';	break;
		case 'c':	return '<';	break;
		case 't':	return '<';	break;
		case 'n':	return '<';	break;
		case 'g':	return '<';	break;
		default:break;
		}
	case '*':
		switch (*c)
		{
		case '+':	return '>';	break;
		case '-':	return '>';	break;
		case '*':	return '>';	break;
		case '^':	return '<';	break;
		case '/':	return '>';	break;
		case '(':	return '<';	break;
		case ')':	return '>';	break;
		case '#':	return '>';	break;
		case 's':	return '<';	break;
		case 'c':	return '<';	break;
		case 't':	return '<';	break;
		case 'n':	return '<';	break;
		case 'g':	return '<';	break;
		default:break;
		}
	case '/':
		switch (*c)
		{
		case '+':	return '>';	break;
		case '-':	return '>';	break;
		case '*':	return '>';	break;
		case '^':	return '<';	break;
		case '/':	return '>';	break;
		case '(':	return '<';	break;
		case ')':	return '>';	break;
		case '#':	return '>';	break;
		case 's':	return '<';	break;
		case 'c':	return '<';	break;
		case 't':	return '<';	break;
		case 'n':	return '<';	break;
		case 'g':	return '<';	break;
		default:break;
		}
	case '(':
		switch (*c)
		{
		case '+':	return '<';	break;
		case '-':	return '<';	break;
		case '*':	return '<';	break;
		case '/':	return '<';	break;
		case '(':	return '<';	break;
		case ')':	return '=';	break;
		case '#':	return 'e';	break;
		case 's':	return '<';	break;
		case 'c':	return '<';	break;
		case 't':	return '<';	break;
		case 'n':	return '<';	break;
		case '^':	return '<';	break;
		case 'g':	return '<';	break;
		default:break;
		}
	case ')':
		switch (*c)
		{
		case '+':	return '>';	break;
		case '-':	return '>';	break;
		case '*':	return '>';	break;
		case '/':	return '>';	break;
		case '(':	return 'e';	break;
		case ')':	return '>';	break;
		case '#':	return '>';	break;
		case 's':	return '>';	break;
		case 'c':	return '>';	break;
		case 't':	return '>';	break;
		case 'n':	return '>';	break;
		case '^':	return '>';	break;
		case 'g':	return '>';	break;
		default:break;
		}
	case '#':
		switch (*c)
		{
		case '+':	return '<';	break;
		case '-':	return '<';	break;
		case '*':	return '<';	break;
		case '/':	return '<';	break;
		case '(':	return '<';	break;
		case ')':	return 'e';	break;
		case '#':	return '=';	break;
		case 's':	return '<';	break;
		case 'c':	return '<';	break;
		case 't':	return '<';	break;
		case 'n':	return '<';	break;
		case '^':	return '<';	break;
		case 'g':	return '<';	break;
		default:break;
		}
	case 's':
		switch (*c)
		{
		case '+':	return '>';	break;
		case '-':	return '>';	break;
		case '*':	return '>';	break;
		case '/':	return '>';	break;
		case '(':	return '<';	break;
		case ')':	return '>';	break;
		case '#':	return '>';	break;
		case 's':	return '>';	break;
		case 'c':	return '>';	break;
		case 't':	return '>';	break;
		case 'n':	return '>';	break;
		case '^':	return '<';	break;
		case 'g':	return '>';	break;//改优先级
		default:break;
		}
	case 'c':
		switch (*c)
		{
		case '+':	return '>';	break;
		case '-':	return '>';	break;
		case '*':	return '>';	break;
		case '/':	return '>';	break;
		case '(':	return '<';	break;
		case ')':	return '>';	break;
		case '#':	return '>';	break;
		case 's':	return '>';	break;
		case 'c':	return '>';	break;
		case 't':	return '>';	break;
		case 'n':	return '>';	break;
		case '^':	return '<';	break;
		case 'g':	return '>';	break;
		default:break;
		}
	case 't':
		switch (*c)
		{
		case '+':	return '>';	break;
		case '-':	return '>';	break;
		case '*':	return '>';	break;
		case '/':	return '>';	break;
		case '(':	return '<';	break;
		case ')':	return '>';	break;
		case '#':	return '>';	break;
		case 's':	return '>';	break;
		case 'c':	return '>';	break;
		case 't':	return '>';	break;
		case 'n':	return '>';	break;
		case '^':	return '<';	break;
		case 'g':	return '>';	break;
		default:break;
		}
	case 'n':
		switch (*c)
		{
		case '+':	return '>';	break;
		case '-':	return '>';	break;
		case '*':	return '>';	break;
		case '/':	return '>';	break;
		case '(':	return '<';	break;
		case ')':	return '>';	break;
		case '#':	return '>';	break;
		case 's':	return '>';	break;
		case 'c':	return '>';	break;
		case 't':	return '>';	break;
		case 'n':	return '>';	break;
		case '^':	return '<';	break;
		case 'g':	return '>';	break;
		default:break;
		}
	case 'g':
		switch (*c)
		{
		case '+':	return '>';	break;
		case '-':	return '>';	break;
		case '*':	return '>';	break;
		case '/':	return '>';	break;
		case '(':	return '<';	break;
		case ')':	return '>';	break;
		case '#':	return '>';	break;
		case 's':	return '>';	break;
		case 'c':	return '>';	break;
		case 't':	return '>';	break;
		case 'n':	return '>';	break;
		case '^':	return '<';	break;
		case 'g':	return '>';	break;
		default:break;
		}
	case '^':
		switch (*c)
		{
		case '+':	return '>';	break;
		case '-':	return '>';	break;
		case '*':	return '>';	break;
		case '/':	return '>';	break;
		case '(':	return '<';	break;
		case ')':	return '>';	break;
		case '#':	return '>';	break;
		case 's':	return '<';	break;
		case 'c':	return '<';	break;
		case 't':	return '<';	break;
		case 'n':	return '<';	break;
		case '^':	return '<';	break;
		case 'g':	return '<';	break;
		default:break;
		}
	default:break;
	}

	return NULL;
}
void calculate(OPND_STACK*S, OPTR_STACK*S1)
{
	double res, bac, pre;
	double *a = &bac;
	double *b = &pre;
	res = 0;
	char c;
	c = GetTop_OPTR(S1);
	switch (c)
	{
	case'+':
		Pop_OPND(S, a);
		Pop_OPND(S, b);
		res = *a + *b;
		Push_OPND(S, res); break;
	case'-':
		Pop_OPND(S, a);
		Pop_OPND(S, b);
		res = *a - *b;
		Push_OPND(S, res); break;
	case'*':
		Pop_OPND(S, a);
		Pop_OPND(S, b);
		res = (*a) *(*b);
		Push_OPND(S, res); break;
	case'/':
		Pop_OPND(S, a);
		Pop_OPND(S, b);
		res = (*a) / (*b);
		Push_OPND(S, res); break;
	case'^':
		Pop_OPND(S, a);
		Pop_OPND(S, b);
		res = pow(*a, *b);
		Push_OPND(S, res); break;
	case's':
		Pop_OPND(S, a);
		res = sin(*a);
		Push_OPND(S, res); break;
	case'c':
		Pop_OPND(S, a);
		res = cos(*a);
		Push_OPND(S, res); break;
	case't':
		Pop_OPND(S, a);
		res = tan(*a);
		Push_OPND(S, res); break;
	case'n':
		Pop_OPND(S, a);
		res = log(*a);
		Push_OPND(S, res); break;
	case'g':
		Pop_OPND(S, a);
		res = log10(*a);
		Push_OPND(S, res); break;

	}
}
void judjment(char c, OPND_STACK*S, OPTR_STACK*S1)
{
	char *c1, d;
	c1 = (char*)malloc(sizeof(char));
	*c1 = GetTop_OPTR(S1);

	char pre = *c1;
	char *bac = &c;
	d = priority(pre, bac);

	switch (d)
	{
	case '>':
		calculate(S, S1);
		Pop_OPTR(S1, c1);			//需要从符号栈中推出
		Push_OPTR(S1, c);
		break;
	case '<':
		Push_OPTR(S1, c);
		break;
	case '=':
		Pop_OPTR(S1, c1);
		break;
	default:break;
	}
}
void read(double x, OPTR_STACK *S1, OPND_STACK *S,char a[])//需加入由char型转换成double型的过程
{
	int n = strlen(a), i = 0;
	a[n] = '#';
	char c;
	c = a[i];
	for (i = 0; i <= n; i++)
	{
		c = a[i];
		if (c == 'x')
		{
			double y0;
			y0 = x;
			Push_OPND(S, y0);
		}

		if (c >= '0'&&c <= '9')
		{
			double k;
			k = change(i,a);
			Push_OPND(S, k);
		}
		if (c == 's')
		{
			if (a[i + 1] == 'i'&&a[i + 2] == 'n'&&a[i + 3] == 'x')
			{
				OPND_TYPE y1;
				y1 = sin(x);
				Push_OPND(S, y1);
				i = i + 3;
			}
			else if (a[i + 3] == '(')
			{
				if (OPTR_StackEmpty(S1) == 1)
				{
					Push_OPTR(S1, c);
					i = i + 4;
				}
				else
				{
					judjment(c, S, S1);
					i = i + 3;
				}
			}
		}//sinx的处理

		else if (c == 'c')
		{
			if (a[i + 1] == 'o'&&a[i + 2] == 's'&&a[i + 3] == 'x')
			{
				OPND_TYPE y2;
				y2 = cos(x);
				Push_OPND(S, y2);
				i = i + 4;
			}
			else if (a[i + 3] == '(')
			{
				if (OPTR_StackEmpty(S1) == 1)
				{
					Push_OPTR(S1, c);
					i = i + 3;
				}
				else
				{
					judjment(c, S, S1);
					i = i + 3;
				}
			}
		}//cosx的处理
		else if (c == 't')
		{
			if (a[i + 1] == 'a'&&a[i + 2] == 'n'&&a[i + 3] == 'x')
			{
				OPND_TYPE y3;
				y3 = tan(x);
				Push_OPND(S, y3);
				i = i + 4;
			}
			else if (a[i + 3] == '(')
			{
				if (OPTR_StackEmpty(S1) == 1)
				{
					Push_OPTR(S1, c);
					i = i + 3;
				}
				else
				{
					judjment(c, S, S1);
					i = i + 3;
				}
			}
		}//tanx的处理
		else if (c == 'l')
		{
			if (a[i + 1] == 'n'&&a[i + 2] == 'x')
			{
				OPND_TYPE y4;
				y4 = log(x);
				Push_OPND(S, y4);
				i = i + 3;
			}
			else
			{
				if (OPTR_StackEmpty(S1) == 1)
				{
					Push_OPTR(S1, c);
					i = i + 2;
				}
				else
				{
					judjment(c, S, S1);
					i = i + 2;
				}
			}
		}//lnx的处理
		else if (c == 'l')
		{
			if (a[i + 1] == 'o'&&a[i + 2] == 'g'&&a[i + 3] == 'x')
			{
				OPND_TYPE y5;
				y5 = log10(x);
				Push_OPND(S, y5);
				i = i + 4;
			}
			else
			{
				if (OPTR_StackEmpty(S1) == 1)
				{
					Push_OPTR(S1, c);
					i = i + 3;
				}
				else
				{
					judjment(c, S, S1);
					i = i + 3;
				}
			}
		}//logx的处理
		c = a[i];
		//字符的入栈
		if (c == '+' || c == '-' || c == '*' || c == '/'||c=='^' || c == '(' || c == ')')
		{
			if (OPTR_StackEmpty(S1) == 1)
			{
				Push_OPTR(S1, c);
			}
			else
			{
				judjment(c, S, S1);
			}
		}
		else if (c == '#')
		{
			while (!OPTR_StackEmpty(S1))
			{
				judjment(c, S, S1);
			}
		}
	}
}
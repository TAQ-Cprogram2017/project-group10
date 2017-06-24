#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>

#define scanf scanf_s

#define QUEUE_TYPE char					//队列
#define QUEUE_INIT_SIZE 100
#define QUEUE_INCREMENT 50
#define NEW_QUEUE (struct QueueRecord *)malloc(sizeof(struct QueueRecord))

#define STACK_INIT_SIZE 100				//栈
#define STACK_INCREMENT 50
#define OPTR_TYPE char
#define OPND_TYPE double
#define NEW_OPTR (struct OPTR *)malloc(sizeof(struct OPTR))
#define NEW_OPND (struct OPND *)malloc(sizeof(struct OPND))

#define True 1
#define False 0
#define Error 1
#define OK 0

/*
////Struct
*/

struct QueueRecord
{
	int Size;
	int Capacity;
	QUEUE_TYPE *Front;
	QUEUE_TYPE *Rear;
	QUEUE_TYPE *Array;
};

struct OPTR
{
	OPTR_TYPE *base;
	OPTR_TYPE *top;
	int stackSize;
};

struct OPND
{
	OPND_TYPE *base;
	OPND_TYPE *top;
	int stackSize;
};

typedef struct QueueRecord QUEUE;
typedef struct OPTR OPTR_STACK;
typedef struct OPND OPND_STACK;

/*
////Subfunctions of Stack
*/

int CreateQueue(QUEUE *Q);
int DestoryQueue(QUEUE *Q);
int ClearQueue(QUEUE *Q);
int QUEUE_EMPTY(QUEUE *Q);
int EnQueue(QUEUE *Q, QUEUE_TYPE e);
int DeQueue(QUEUE *Q, QUEUE_TYPE *e);

int InitOPTR_Stack(OPTR_STACK *S);
int InitOPND_Stack(OPND_STACK *S);
int DestroyOPTR_Stack(OPTR_STACK *S);
int DestroyOPND_Stack(OPND_STACK *S);
int ClearOPTR_Stack(OPTR_STACK *S);
int ClearOPND_Stack(OPND_STACK *S);
int OPTR_StackEmpty(OPTR_STACK *S);
int OPND_StackEmpty(OPND_STACK *S);
int OPTR_StackLength(OPTR_STACK *S);
int OPND_StackLength(OPND_STACK *S);
int Push_OPTR(OPTR_STACK *S, OPTR_TYPE e);
int Push_OPND(OPND_STACK *S, OPND_TYPE e);
int Pop_OPTR(OPTR_STACK *S, OPTR_TYPE *e);
int Pop_OPND(OPND_STACK *S, OPND_TYPE *e);
char GetTop_OPTR(OPTR_STACK *S);
double GetTop_OPND(OPND_STACK *S);

/*
////Test
*/

void test_OPTR(OPTR_STACK *S);
void test_OPND(OPND_STACK *S);

/*
////Subfunctions of Calculater
*/

QUEUE_TYPE ReQueue(QUEUE *Q);								//获取队列中第一个元素

bool calculate();											//计算器
double conversion(QUEUE *Q, char *c);						//char->double
char isFunction(QUEUE *Q, char *c);							//判断是否为函数
char priority(char pre, char *c);							//优先级
int Operate(OPTR_STACK *S_OPTR, OPND_STACK *S_OPND);		//运算

/*
////Functions
*/

int main()
{
	while (1)
		calculate();

	system("pause");
	return 0;
}

//build

int CreateQueue(QUEUE *Q)
{
	Q->Array = (QUEUE_TYPE *)malloc(QUEUE_INIT_SIZE * sizeof(QUEUE_TYPE));

	if (Q->Array == NULL)
	{
		printf("Error.\n");
		return Error;
	}

	Q->Front = Q->Array;
	Q->Rear = Q->Array;

	Q->Size = QUEUE_INIT_SIZE;
	Q->Capacity = Q->Rear - Q->Front;

	return OK;
}

int DestoryQueue(QUEUE *Q)
{
	free(Q->Array);
	Q->Front = NULL;
	Q->Rear = NULL;
	Q->Size = 0;
	Q->Capacity = 0;

	return OK;
}

int ClearQueue(QUEUE *Q)
{
	Q->Front = Q->Array;
	Q->Rear = Q->Array;

	Q->Size = QUEUE_INIT_SIZE;
	Q->Capacity = Q->Rear - Q->Front;

	return OK;
}

int QUEUE_EMPTY(QUEUE *Q)
{
	return Q->Size == 0;
}

int EnQueue(QUEUE *Q, QUEUE_TYPE e)
{
	if (Q->Capacity >= Q->Size)
	{
		Q->Array = (QUEUE_TYPE *)realloc
		(Q->Array, (Q->Size + QUEUE_INCREMENT) * sizeof(QUEUE_TYPE));

		if (!Q->Array)
			return Error;

		Q->Size += QUEUE_INCREMENT;
	}

	*Q->Rear = e;
	Q->Rear++;
	Q->Capacity = Q->Rear - Q->Front;

	return OK;
}

int DeQueue(QUEUE *Q, QUEUE_TYPE *e)
{
	if (Q->Capacity == 0)
	{
		printf("This Queue is Empty.\n");
		return Error;
	}
	else
	{
		*e = *(Q->Front++);
		Q->Capacity = Q->Rear - Q->Front;
	}

	return OK;
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

int DestroyOPTR_Stack(OPTR_STACK *S)
{
	free(S->base);
	S->base = NULL;
	S->top = NULL;
	S->stackSize = 0;

	return OK;
}

int DestroyOPND_Stack(OPND_STACK *S)
{
	free(S->base);
	S->base = NULL;
	S->top = NULL;
	S->stackSize = 0;

	return OK;
}

int ClearOPTR_Stack(OPTR_STACK *S)
{
	S->top = S->base;

	return OK;
}

int ClearOPND_Stack(OPND_STACK *S)
{
	S->top = S->base;

	return OK;
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

int Push_OPTR(OPTR_STACK *S, OPTR_TYPE e)
{
	if (OPTR_StackLength(S) >= S->stackSize)
	{
		S->base = (OPTR_TYPE *)realloc
		(S->base, (S->stackSize + STACK_INCREMENT) * sizeof(OPTR_TYPE));

		if (!S->base)
			return Error;

		S->stackSize += STACK_INCREMENT;
	}

	*S->top = e;
	S->top++;

	return OK;
}

int Push_OPND(OPND_STACK *S, OPND_TYPE e)
{
	if (OPND_StackLength(S) >= S->stackSize)
	{
		S->base = (OPND_TYPE *)realloc
		(S->base, (S->stackSize + STACK_INCREMENT) * sizeof(OPND_TYPE));

		if (!S->base)
			return Error;

		S->stackSize += STACK_INCREMENT;
	}

	*S->top = e;
	S->top++;

	return OK;
}

int Pop_OPTR(OPTR_STACK *S, OPTR_TYPE *e)
{

	if (OPTR_StackEmpty(S))
	{
		printf("This Stack is Empty.\n");
		return Error;
	}
	else
	{
		*e = *(--S->top);
		return OK;
	}
}

int Pop_OPND(OPND_STACK *S, OPND_TYPE *e)
{
	if (OPND_StackEmpty(S))
	{
		printf("This Stack is Empty.\n");
		return Error;
	}
	else
	{
		*e = *(--S->top);
		return OK;
	}
}

char GetTop_OPTR(OPTR_STACK *S)
{
	OPTR_TYPE *e = S->top;

	if (OPTR_StackEmpty(S))
	{
		printf("This Stack is Empty.\n");
		return Error;
	}
	else
	{
		*e = *(S->top - 1);
		return *e;
	}
}

double GetTop_OPND(OPND_STACK *S)
{
	OPND_TYPE *e = S->top;

	if (OPND_StackEmpty(S))
	{
		printf("This Stack is Empty.\n");
		return Error;
	}
	else
	{
		*e = *(S->top - 1);
		return *e;
	}
}

void test_OPTR(OPTR_STACK *S)
{
	char c;
	char *p = &c;
	printf("Input(char):\t");
	c = getchar();
	while (c != EOF&&c != '\n')
	{
		Push_OPTR(S, c);
		c = getchar();
	}
	while (S->top != S->base)
	{
		Pop_OPTR(S, p);
		printf("%c", *p);
	}
	printf("\n");
}

void test_OPND(OPND_STACK *S)
{
	double n = 0;
	printf("Input(10x):\t");
	scanf("%lf", &n);

	double *e;
	e = &n;

	while (n)
	{
		Push_OPND(S, n);
		printf("Input(10x):\t");
		scanf("%lf", &n);
	}

	while (!OPND_StackEmpty(S))
	{
		Pop_OPND(S, e);
		printf("%.2lf\n", *e);
	}
}

//calculate

QUEUE_TYPE ReQueue(QUEUE *Q)
{
	QUEUE_TYPE Element, *e = &Element;
	DeQueue(Q, e);

	return *e;
}

bool calculate()
{
	QUEUE *Q = NEW_QUEUE;
	CreateQueue(Q);

	OPTR_STACK *S_OPTR = NEW_OPTR;
	InitOPTR_Stack(S_OPTR);

	OPND_STACK *S_OPND = NEW_OPND;
	InitOPND_Stack(S_OPND);

	Push_OPTR(S_OPTR, '#');
	Push_OPTR(S_OPTR, 0);
	char input;
	char *c = &input;		//=getchar();
	char r = {}, *x = &r;	//rubbish

	double result = 0;		//运算结果
	double *result_point = &result;

	char OPTR = {};		//操作符
	char *optr = &OPTR;

	printf("Input:\n");

	do
	{
		*c = getchar();
		EnQueue(Q, *c);
	} while (*c != '\n');

	*c = ReQueue(Q);

	while (*c != '#' || GetTop_OPTR(S_OPTR) != '#')
	{
		if (*c >= '0'&&*c <= '9' || *c == '.')
		{
			double num = conversion(Q, c);							//数据
			Push_OPND(S_OPND, num);
		}

		else if (*c == 'x' || *c == 'y' || *c == 'z')				//变量
		{
			
			double x;
			printf("%c=", *c);
			scanf("%lf", &x);
			Push_OPND(S_OPND, x);
			*c = ReQueue(Q);
			getchar();
		}

		else if (*c == ' ')						//特殊情况处理
			*c = ReQueue(Q);
		else if (*c == '\n')					//公式结尾
			*c = '#';

		else
		{
			if (*c >= 'A'&&*c <= 'z')
			{
				*c = isFunction(Q, c);
				if (*c == 'e')
					return Error;
			}

			/*入栈前应该先判断优先级，优先级高则入栈并读入下一个字符
			优先级低则将前两个数据进行运算，运算结果入数据栈，然后运算符入符号栈*/

			switch (priority(GetTop_OPTR(S_OPTR), c))
			{
			case '<':
				Push_OPTR(S_OPTR, *c);
				*c = ReQueue(Q);
				break;
			case '=':		//脱括号
				Pop_OPTR(S_OPTR, x);
				*c = ReQueue(Q);
				break;
			case '>':
				Operate(S_OPTR, S_OPND);
				break;
			case NULL:
				return Error;
			default:
				break;
			}//switch
		}


	}//while

	Pop_OPND(S_OPND, result_point);
	printf("%lf\n", result);								//打印结果

	return OK;
}

double conversion(QUEUE *Q, char *c)					//char->double
{
	double num = 0;
	int i = -1;				//小数位数计数器

	while (*c >= '0'&&*c <= '9')
	{
		num = num * 10 + (int)*c - 48;
		*c = ReQueue(Q);
	}
	if (*c == '.')
	{
		*c = ReQueue(Q);
		while (*c >= '0'&&*c <= '9')
		{
			num += ((int)*c - 48)*pow(10, i--);
			*c = ReQueue(Q);
		}
	}

	return num;
}

char isFunction(QUEUE *Q, char *c)
{
	if (*c == 's'&&ReQueue(Q) == 'i'&&ReQueue(Q) == 'n')
		return 's';		//if(sin)

	else if (*c == 'c'&&ReQueue(Q) == 'o'&&ReQueue(Q) == 's')
		return 'c';		//if(cos)

	else if (*c == 't'&&ReQueue(Q) == 'a'&&ReQueue(Q) == 'n')
		return 't';		//if(tan)

	else if (*c == 'x')
		return 'x';		//if(x)

	else
		return 'e';
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
		case '/':	return '<';	break;
		case '(':	return '<';	break;
		case ')':	return '>';	break;
		case '#':	return '>';	break;
		case 's':	return '<';	break;
		case 'c':	return '<';	break;
		case 't':	return '<';	break;
		default:break;
		}
	case '-':
		switch (*c)
		{
		case '+':	return '>';	break;
		case '-':	return '>';	break;
		case '*':	return '<';	break;
		case '/':	return '<';	break;
		case '(':	return '<';	break;
		case ')':	return '>';	break;
		case '#':	return '>';	break;
		case 's':	return '<';	break;
		case 'c':	return '<';	break;
		case 't':	return '<';	break;
		default:break;
		}
	case '*':
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
		default:break;
		}
	case '/':
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
		default:break;
		}
	default:break;
	}

	return NULL;
}

int Operate(OPTR_STACK *S_OPTR, OPND_STACK *S_OPND)
{
	char op = {};
	char *optr = &op;
	Pop_OPTR(S_OPTR, optr);		//取出操作符

	double opnd_pre = 0, opnd_bac = 0;
	double *pre = &opnd_pre, *bac = &opnd_bac;

	/*进行运算*/

	double result = 0;

	switch (*optr)
	{
	case '+':
		Pop_OPND(S_OPND, bac);
		Pop_OPND(S_OPND, pre);
		result = opnd_pre + opnd_bac;
		break;
	case '-':
		Pop_OPND(S_OPND, bac);
		Pop_OPND(S_OPND, pre);
		result = opnd_pre - opnd_bac;
		break;
	case '*':
		Pop_OPND(S_OPND, bac);
		Pop_OPND(S_OPND, pre);
		result = opnd_pre * opnd_bac;
		break;
	case '/':
		Pop_OPND(S_OPND, bac);
		Pop_OPND(S_OPND, pre);
		result = opnd_pre / opnd_bac;
		break;
	case 's':
		Pop_OPND(S_OPND, bac);
		result = sin(opnd_bac);
		break;
	case 'c':
		Pop_OPND(S_OPND, bac);
		result = cos(opnd_bac);
		break;
	case 't':
		Pop_OPND(S_OPND, bac);
		result = tan(opnd_bac);
		break;
	}

	Push_OPND(S_OPND, result);

	return OK;
}
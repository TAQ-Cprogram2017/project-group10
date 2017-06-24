#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
using namespace std;
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
#define pi 3.1415926
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
char ReQueue(QUEUE *Q);								        //获取队列中第一个元素
bool calculate();											//计算器
double conversion(QUEUE *Q, char *c);						//char->double
char isFunction(QUEUE *Q, char *c);							//判断是否为函数
char priority(char pre, char *c);							//优先级
int Operate(OPTR_STACK *S_OPTR, OPND_STACK *S_OPND);		//运算
int round(int a, int b);
int pow(int a, int b);
int DecTrance_b(int a, int b);
int b_TranceDec(int a, int b);
int f(int x, int y);

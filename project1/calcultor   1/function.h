#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#pragma warning(disable:4996)
#define STACK_INIT_SIZE 100//宏定义栈的长度
#define STACK_INCREMENT 50
#define OPTR_TYPE char//宏定义char变量
#define OPND_TYPE double//宏定义double变量
#define NEW_OPTR (struct OPTR *)malloc(sizeof(struct OPTR))//初始化字符栈的内存空间
#define NEW_OPND (struct OPND *)malloc(sizeof(struct OPND))//初始化数字栈的内存空间
#define plus(a,b) a+b //加法
#define subract(a,b) a-b//减法
#define multiply(a,b) a*b//乘法
#define division(a,b) a/b//除法
#define True 1
#define False 0
#define Error 1
#define OK 0
#define pi 3.1415926
#define e 2.7182818
struct OPTR//字符栈
{
	OPTR_TYPE *base;
	OPTR_TYPE *top;//字符栈的top指针
	int stackSize;
};typedef struct OPTR OPTR_STACK;
struct OPND//数字栈
{
	OPND_TYPE *base;
	OPND_TYPE *top;//数字栈的top指针
	int stackSize;
};typedef struct OPND OPND_STACK;
int InitOPTR_Stack(OPTR_STACK *S);
int InitOPND_Stack(OPND_STACK *S);
void DestroyOPTR_Stack(OPTR_STACK *S);
void DestroyOPND_Stack(OPND_STACK *S);
void ClearOPTR_Stack(OPTR_STACK *S);
void ClearOPND_Stack(OPND_STACK *S);
int OPTR_StackEmpty(OPTR_STACK *S);
int OPND_StackEmpty(OPND_STACK *S);
int OPTR_StackLength(OPTR_STACK *S);
int OPND_StackLength(OPND_STACK *S);
bool Push_OPTR(OPTR_STACK *S, OPTR_TYPE d);
bool Push_OPND(OPND_STACK *S, OPND_TYPE d);
bool Pop_OPTR(OPTR_STACK *S, OPTR_TYPE *d);
bool Pop_OPND(OPND_STACK *S, OPND_TYPE *d);
char GetTop_OPTR(OPTR_STACK *S);
double GetTop_OPND(OPND_STACK *S);
char priority(char pre, char *c);
void calculate(OPND_STACK*S, OPTR_STACK*S1);
void judjment(char c, OPND_STACK*S, OPTR_STACK*S1);
void read(double x, OPTR_STACK *S1, OPND_STACK *S,char a[]);
int round(int a, int b);
int pow(int a, int b);
int DecTrance_b(int a, int b);
int b_TranceDec(int a, int b);
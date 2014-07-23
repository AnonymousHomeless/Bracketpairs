#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "main.h"

int main()
{
	int a;
	int i;					//用于for循环
	int iCount = 0;			//用于计算左括号的数	
	char cBrackets[30];		//用于存放入栈的数据
	char cOut;				//用于存放出栈的数据
	struct SStack *Stack = NULL;

	Stack = InitStack();
	fflush(stdin);
	fflush(stdout);
	printf("请输入你要检验的括弧：");
	gets(cBrackets);

	for (i = 0; i < (sizeof(cBrackets)/8); i++)
	{
		if ((cBrackets[i] == '(') || (cBrackets[i] == '[') || (cBrackets[i] == '{'))
		{
			Push(Stack, cBrackets[i]);
			iCount++;
		}
	}

	for (i = 0; i < (sizeof(cBrackets)/8); i++)
	{
		if ((cBrackets[i] == ')') || (cBrackets[i] == ']') || (cBrackets[i] == '}'))
		{
			Pop(Stack, &cOut);
			if((cBrackets[i] == cOut + 1) || (cBrackets[i] == cOut + 2))
				iCount--;
		}
	}
	if(iCount == 0)
		printf("括弧匹配！\n");
	else
		printf("括弧不匹配！\n");
	scanf("%d", &a);
	return 0;
}

//构建空栈
struct SStack *InitStack()
{
	struct SStack *Stack;
	Stack = (struct SStack *)malloc(sizeof(struct SStack));
	Stack->pBase = (struct SNode *)malloc(INIT_SIZE * sizeof(struct SNode));
	if(Stack->pBase == NULL)
		exit(1);
	Stack->pTop = Stack->pBase;
	Stack->iSize = INIT_SIZE;
}

//入栈
struct SStack *Push(struct SStack *Stack, char cBracket)
{
	Stack->pTop->cData = cBracket;
	Stack->pTop += (sizeof(struct SNode) / 8);
	Stack->iSize++;
	return Stack;
}

//出栈
struct SStack *Pop(struct SStack *Stack, char *cBracket)
{
	Stack->pTop -= (sizeof(struct SNode) / 8);
	*cBracket = Stack->pTop->cData;
	Stack->iSize--;
	return Stack;
}

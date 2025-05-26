#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

//内存泄漏检查，勿动
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
//内存泄漏检查，勿动

typedef struct _TreeNode
{
	int data;
	struct _TreeNode *pLeft;
	struct _TreeNode *pRight;
}TreeNode;


TreeNode *InitTreeNode(int data)
{
	TreeNode *pNew = malloc(sizeof(TreeNode));
	assert(pNew != NULL);

	pNew->data = data;
	pNew->pLeft = NULL;
	pNew->pRight = NULL;

	return pNew;
}

void UnInitTreeNode(TreeNode *pNode)
{
	free(pNode);
	pNode = NULL;
}

void FreeAll(TreeNode *pRoot)
{
	if (pRoot == NULL)
	{
		return;
	}

	//优先往左侧递归
	if (pRoot->pLeft != NULL)
	{
		FreeAll(pRoot->pLeft);
		pRoot->pLeft = NULL;//上一层释放完，设置为NULL
	}

	//然后往右侧递归
	if (pRoot->pRight != NULL)
	{
		FreeAll(pRoot->pRight);
		pRoot->pRight = NULL;//上一层释放完，设置为NULL
	}

	//当前节点两个子节点都为NULL
	free(pRoot);//直接释放
	pRoot = NULL;
}


TreeNode *AddLeft(TreeNode *pNode, int data)
{
	assert(pNode != NULL);
	TreeNode *pLeft = InitTreeNode(data);
	pNode->pLeft = pLeft;
	return pLeft;
}

TreeNode *AddRight(TreeNode *pNode, int data)
{
	assert(pNode != NULL);
	TreeNode *pRight = InitTreeNode(data);
	pNode->pRight = pRight;
	return pRight;
}

typedef void(*Func)(int data);

void PreOrder(TreeNode *pRoot, Func pFunc)
{
	if (pRoot == NULL)
	{
		return;
	}

	pFunc(pRoot->data);

	if (pRoot->pLeft != NULL)
	{
		PreOrder(pRoot->pLeft, pFunc);
	}

	if (pRoot->pRight != NULL)
	{
		PreOrder(pRoot->pRight, pFunc);
	}
}

void MidOrder(TreeNode *pRoot, Func pFunc)
{
	if (pRoot == NULL)
	{
		return;
	}

	if (pRoot->pLeft != NULL)
	{
		MidOrder(pRoot->pLeft, pFunc);
	}

	pFunc(pRoot->data);

	if (pRoot->pRight != NULL)
	{
		MidOrder(pRoot->pRight, pFunc);
	}
}

void PstOrder(TreeNode *pRoot, Func pFunc)
{
	if (pRoot == NULL)
	{
		return;
	}

	if (pRoot->pLeft != NULL)
	{
		PstOrder(pRoot->pLeft, pFunc);
	}

	if (pRoot->pRight != NULL)
	{
		PstOrder(pRoot->pRight, pFunc);
	}

	pFunc(pRoot->data);
}


#define MAX_STACK_DEPTH 32

void StackPreOrder(TreeNode *pRoot, Func pFunc)
{
	if (pRoot == NULL)
	{
		return;
	}

	TreeNode *pStack[MAX_STACK_DEPTH] = { 0 };
	size_t szTop = MAX_STACK_DEPTH;//从高往低

	TreeNode *pCurr = pRoot;
	while (true)
	{
		//访问左节点
		if (pCurr != NULL)
		{
			assert(szTop > 0);//不能等于0，否则下面会使用-1访问出现问题，小于零就更不行了
			pFunc(pCurr->data);//调用
			pStack[--szTop] = pCurr;//当前节点进栈
			pCurr = pCurr->pLeft;
		}
		else//否则尝试访问右节点
		{
			if (szTop >= MAX_STACK_DEPTH)//到头了，结束
			{
				return;//直接返回
			}
			//从栈内弹出并访问右节点
			pCurr = pStack[szTop++];
			pCurr = pCurr->pRight;//移动到新节点
			//如果还是null则会继续弹出直到找到一个可用节点或栈空结束
		}
	}
}

void StackMidOrder(TreeNode *pRoot, Func pFunc)
{
	if (pRoot == NULL)
	{
		return;
	}

	TreeNode *pStack[MAX_STACK_DEPTH] = { 0 };
	size_t szTop = MAX_STACK_DEPTH;	//从高往低

	TreeNode *pCurr = pRoot;
	while (true)
	{
		//访问左节点
		if (pCurr != NULL)
		{
			assert(szTop > 0);//不能等于0，否则下面会使用-1访问出现问题，小于零就更不行了
			pStack[--szTop] = pCurr;//当前节点进栈
			pCurr = pCurr->pLeft;
		}
		else//否则尝试访问右节点
		{
			if (szTop >= MAX_STACK_DEPTH)//到头了，结束
			{
				return;//直接返回
			}
			//从栈内弹出并访问右节点
			pCurr = pStack[szTop++];
			pFunc(pCurr->data);//调用
			pCurr = pCurr->pRight;//移动到新节点
			//如果还是null则会继续弹出直到找到一个可用节点或栈空结束
		}
	}
}

void StackPstOrder(TreeNode *pRoot, Func pFunc)
{
	if (pRoot == NULL)
	{
		return;
	}

	TreeNode *pStack[MAX_STACK_DEPTH] = { 0 };
	size_t szTop = MAX_STACK_DEPTH;//从高往低

	TreeNode *pCurr = pRoot;
	TreeNode *pPrev = NULL;
	while (true)
	{
		while (pCurr != NULL)
		{
			assert(szTop > 0);//不能等于0，否则下面会使用-1访问出现问题，小于零就更不行了
			pStack[--szTop] = pCurr;//当前节点进栈
			pCurr = pCurr->pLeft;//访问左节点
		}
		//全部完成后

		//取出栈顶
		pCurr = pStack[szTop];

		// 如果右子树存在且未被访问
		if (pCurr->pRight != NULL && pCurr->pRight != pPrev)
		{
			pCurr = pCurr->pRight; //转向右子树
			continue;
		}
		
		// 处理当前节点并弹出栈
		pFunc(pCurr->data);
		if (++szTop >= MAX_STACK_DEPTH)
		{
			return;//为空，结束
		}

		pPrev = pCurr;//更新前一个访问节点
		pCurr = NULL;//强制触发回溯
	}
}




void PrintFunc(int data)
{
	printf("%c ", (char)data);
}

int main(void)
{
	//内存泄漏检查，勿动
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_FILE);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	//内存泄漏检查，勿动

	TreeNode *pRoot = InitTreeNode('A');
	TreeNode *pL, *pR;

	pL = AddLeft(pRoot, 'B');
	pL = AddLeft(pL, 'D');
	pR = AddRight(pL, 'H');
	pL = AddLeft(pL, 'G');

	pR = AddRight(pRoot, 'C');
	pL = AddLeft(pR, 'E');
	pR = AddRight(pR, 'F');
	pR = AddRight(pL, 'I');

	PreOrder(pRoot, PrintFunc);
	putchar('\n');
	StackPreOrder(pRoot, PrintFunc);
	putchar('\n');
	putchar('\n');
	
	MidOrder(pRoot, PrintFunc);
	putchar('\n');
	StackMidOrder(pRoot, PrintFunc);
	putchar('\n');
	putchar('\n');
	
	PstOrder(pRoot, PrintFunc);
	putchar('\n');
	StackPstOrder(pRoot, PrintFunc);
	putchar('\n');
	putchar('\n');

	FreeAll(pRoot);

	return 0;
}
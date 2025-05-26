#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct NODE {
	int data;
	struct NODE* pNext;
} NODE, * PNODE;

typedef struct Stask {
	PNODE ptop;   //顶端
	PNODE pbottom;  //底部
} STACK, * PSTACK;

void init(PSTACK);
void push(PSTACK, int);
void traverse(PSTACK);
bool pop(PSTACK, int*);

int main(void) {
	STACK S;
	int val;

	init(&S);

	push(&S, 1);
	push(&S, 2);
	push(&S, 3);
	push(&S, 4);
	push(&S, 5);
	traverse(&S);

	if (pop(&S, &val))
		printf("出栈成功出栈的元素是%d\n", val);
	else
		printf("出栈失败\n");

	traverse(&S);

	return 0;
}

void init(PSTACK ps) {
	ps->ptop = (PNODE)malloc(sizeof(NODE));
	if (NULL == ps->ptop) {
		printf("动态内存分配失败");
		exit(-1);
	}
	else {
		ps->pbottom = ps->ptop;
		ps->ptop->pNext = NULL;
	}
}

void push(PSTACK ps, int val) {
	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	if (NULL == pNew) {
		printf("动态内存分配失败");
		exit(-1);
	}
	else {
		pNew->data = val;
		pNew->pNext = ps->ptop;
		ps->ptop = pNew;
	}
}

void traverse(PSTACK ps) {
	PNODE p = ps->ptop;
	while (p != ps->pbottom) {
		printf("%d ", p->data);
		p = p->pNext;
	}
	printf("\n");
	return;
}

bool empty(PSTACK ps) {
	if (ps->ptop == ps->pbottom) {
		return true;
	}
	else {
		return false;
	}
}

bool pop(PSTACK ps, int* pval) {
	if (empty(ps)) {
		return false;
	}
	else
	{
		PNODE r = ps->ptop;
		*pval = r->data;
		ps->ptop = r->pNext;
		free(r);
		r = NULL;
		return true;
	}
}

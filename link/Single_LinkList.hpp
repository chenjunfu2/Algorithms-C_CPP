#pragma once
#include <new>

template<typename DataType>
class Single_List
{
public:
	//节点声明
	struct Node
	{
		Node *pNext;//下一个节点
		DataType tData;//数据
	};
private:
	Node *pHead;//头部
public:
	//默认无参构造
	Single_List(void) :pHead(nullptr)
	{}

	//析构
	~Single_List(void)
	{
		RemoveAll();
	}

	//查找第一个值为tDataFind的节点
	Node *FindFirst(const DataType &tDataFind)
	{
		Node *pFind = pHead;
		while (pFind != nullptr)//从头遍历比较
		{
			if (pFind->tData == tDataFind)
			{
				return pFind;
			}
			pFind = pFind->pNext;
		}

		return nullptr;
	}

	//查找最后一个值为tDataFind的节点
	Node *FindLast(const DataType &tDataFind)
	{
		Node *pFind = pHead, *pTemp = nullptr;
		while (pFind != nullptr)//从头遍历比较，每次遇到相同的就保存
		{
			if (pFind->tData == tDataFind)
			{
				pTemp = pFind;
			}
			pFind = pFind->pNext;
		}

		return pTemp;
	}

	//头插
	bool InsertHead(const DataType &tData)
	{
		//分配并初始化
		Node *pInsert = new(std::nothrow) Node{pHead,tData};
		if (pInsert == nullptr)
		{
			return false;
		}

		//设置头节点为新节点
		pHead = pInsert;

		return true;
	}

	//尾插
	bool InsertTail(const DataType &tData)
	{
		//分配并初始化
		Node *pInsert = new(std::nothrow) Node{nullptr,tData};
		if (pInsert == nullptr)
		{
			return false;
		}

		if (pHead == nullptr)//头节点
		{
			//设置头节点为新节点
			pHead = pInsert;
			return true;//头插
		}

		Node *pTail = pHead;
		while (pTail->pNext != nullptr)//遍历获取尾节点
		{
			pTail = pTail->pNext;
		}

		//设置最后一个节点的下一个节点为新节点
		pTail->pNext = pInsert;

		return true;
	}

	//中间插入(在pInsertPrev指向的元素后插入)
	bool InsertMid(const DataType &tData, Node *pInsertPrev)
	{
		if (pInsertPrev == nullptr)
		{
			return false;
		}

		//分配并初始化
		Node *pInsert = new(std::nothrow) Node{pInsertPrev->pNext,tData};
		if (pInsert == nullptr)
		{
			return false;
		}

		//设置插入点的下一个节点为新节点
		pInsertPrev->pNext = pInsert;

		return true;
	}

	//头删
	bool RemoveHead(void)
	{
		if (pHead == nullptr)
		{
			return false;
		}

		//保存头部指针
		Node *pRemove = pHead;

		//设置头指针
		pHead = pHead->pNext;

		//删除
		delete pRemove;
		pRemove = nullptr;

		return true;
	}

	//尾删
	bool RemoveTail(void)
	{
		if (pHead == nullptr)
		{
			return false;
		}

		if (pHead == nullptr)//头节点
		{
			return false;
		}
		else if (pHead->pNext == nullptr)//只有一个元素
		{
			delete pHead;
			pHead = nullptr;
		}

		Node *pTailPrev = pHead;
		while (pTailPrev->pNext->pNext != nullptr)//遍历获取尾节点的前节点
		{
			pTailPrev = pTailPrev->pNext;
		}

		//删除
		delete pTailPrev->pNext;
		pTailPrev->pNext = nullptr;

		return true;
	}

	//中间删除
	bool RemoveMid(Node *pRemove)
	{
		if (pRemove == nullptr)
		{
			return false;
		}

		if (pHead == nullptr)//头节点
		{
			return false;
		}

		if (pRemove == pHead)//只有一个元素
		{
			delete pHead;
			pHead = nullptr;
		}

		Node *pRemovePrev = pHead;
		while (pRemovePrev->pNext != pRemove)//遍历获取删除节点的前节点
		{
			pRemovePrev = pRemovePrev->pNext;
		}

		//设置前节点的下一个节点为删除节点的下一个节点
		pRemovePrev->pNext = pRemove->pNext;

		//删除
		delete pRemove;
		pRemove = nullptr;

		return true;
	}

	//删除所有元素，清空链表
	void RemoveAll(void)
	{
		Node *pDel = pHead;//pDel存放待删除节点，从头节点开始删除
		while (pDel != nullptr)//遍历删除所有元素
		{
			pHead = pHead->pNext;//移动当前节点到下一个节点
			delete pDel;//删除上一个节点
			pDel = pHead;//待删除节点设为当前节点
		}

		//置空链表
		pHead = nullptr;
	}

	//是否为空
	bool IsEmpty(void)
	{
		return pHead == nullptr;
	}

	//获取头部指针
	Node *GetHead(void)
	{
		return pHead;
	}

	//获取尾部指针
	Node *GetTail(void)
	{
		if (pHead == nullptr)
		{
			return nullptr;
		}

		Node *pTail = pHead;
		while (pTail->pNext != nullptr)//遍历获取尾节点
		{
			pTail = pTail->pNext;
		}

		return pTail;
	}
};
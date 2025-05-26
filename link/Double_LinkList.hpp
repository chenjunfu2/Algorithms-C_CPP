#pragma once
#include <new>

template<typename DataType>
class Double_List
{
public:
	//节点声明
	struct Node
	{
		Node *pPrev;//上一个节点
		Node *pNext;//下一个节点
		DataType tData;//数据
	};
private:
	Node *pHead;//头部
	Node *pTail;//尾部
public:
	//默认无参构造
	Double_List(void) :pHead(nullptr), pTail(nullptr)
	{}

	//析构
	~Double_List(void)
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
		Node *pFind = pTail;
		while (pFind != nullptr)//从尾遍历比较
		{
			if (pFind->tData == tDataFind)
			{
				return pFind;
			}
			pFind = pFind->pPrev;
		}

		return nullptr;
	}
	
	//头插
	bool InsertHead(const DataType &tData)
	{
		//分配并初始化
		Node *pInsert = new(std::nothrow) Node{nullptr,pHead,tData};
		if (pInsert == nullptr)
		{
			return false;
		}

		//设置头节点指向前一个节点的指针为当前分配的节点
		if (pHead != nullptr)
		{
			pHead->pPrev = pInsert;
		}

		//设置头节点为新节点
		pHead = pInsert;

		//设置尾节点
		if (pTail == nullptr)
		{
			pTail = pInsert;
		}

		return true;
	}

	//尾插
	bool InsertTail(const DataType &tData)
	{
		//分配并初始化
		Node *pInsert = new(std::nothrow) Node{pTail,nullptr,tData};
		if (pInsert == nullptr)
		{
			return false;
		}

		//设置尾节点的后一个节点指针为当前分配的节点
		if (pTail != nullptr)
		{
			pTail->pNext = pInsert;
		}

		//设置尾节点为新节点
		pTail = pInsert;

		//设置头节点
		if (pHead == nullptr)
		{
			pHead = pInsert;
		}

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
		Node *pInsert = new(std::nothrow) Node{pInsertPrev,pInsertPrev->pNext,tData};
		if (pInsert == nullptr)
		{
			return false;
		}

		//设置插入点的下一个节点为新节点
		pInsertPrev->pNext = pInsert;

		//如果存在下一个节点，那么下一个节点的上一个节点为新节点
		if (pInsert->pNext != nullptr)
		{
			pInsert->pNext->pPrev = pInsert;
		}
		else//如果不存在下一个节点，即当前节点是尾节点
		{
			pTail = pInsert;//设置尾节点为新插入的节点
		}

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

		//设置指针
		pHead = pHead->pNext;
		if (pHead != nullptr)//还有元素
		{
			pHead->pPrev = nullptr;//取消对前一个元素指针的引用
		}
		else//删完了
		{
			pTail = nullptr;//尾部指针也要取消对最后一个元素的引用
		}

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

		//保存尾部指针
		Node *pRemove = pTail;

		//设置指针
		pTail = pTail->pPrev;
		if (pTail != nullptr)//还有元素
		{
			pTail->pNext = nullptr;//取消对后一个元素指针的引用
		}
		else//删完了
		{
			pHead = nullptr;//头部指针也要取消对最后一个元素的引用
		}

		//删除
		delete pRemove;
		pRemove = nullptr;

		return true;
	}

	//中间删除
	bool RemoveMid(Node *pRemove)
	{
		if (pRemove == nullptr)
		{
			return false;
		}

		//设置前节点的后节点指针为要删除节点的后节点指针
		if (pRemove->pPrev != nullptr)
		{
			pRemove->pPrev->pNext = pRemove->pNext;
		}
		else//要删除节点是头节点
		{
			pHead = pRemove->pNext;//设置头节点指向要删除节点的下一个节点
		}

		//设置后节点的前节点指针为要删除节点的前节点指针
		if (pRemove->pNext != nullptr)
		{
			pRemove->pNext->pPrev = pRemove->pPrev;
		}
		else//要删除节点是尾节点
		{
			pTail = pRemove->pPrev;//设置尾节点指向要删除节点的上一个节点
		}

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
		pTail = nullptr;
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
		return pTail;
	}
};
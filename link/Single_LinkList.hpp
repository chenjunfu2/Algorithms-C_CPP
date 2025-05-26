#pragma once
#include <new>

template<typename DataType>
class Single_List
{
public:
	//�ڵ�����
	struct Node
	{
		Node *pNext;//��һ���ڵ�
		DataType tData;//����
	};
private:
	Node *pHead;//ͷ��
public:
	//Ĭ���޲ι���
	Single_List(void) :pHead(nullptr)
	{}

	//����
	~Single_List(void)
	{
		RemoveAll();
	}

	//���ҵ�һ��ֵΪtDataFind�Ľڵ�
	Node *FindFirst(const DataType &tDataFind)
	{
		Node *pFind = pHead;
		while (pFind != nullptr)//��ͷ�����Ƚ�
		{
			if (pFind->tData == tDataFind)
			{
				return pFind;
			}
			pFind = pFind->pNext;
		}

		return nullptr;
	}

	//�������һ��ֵΪtDataFind�Ľڵ�
	Node *FindLast(const DataType &tDataFind)
	{
		Node *pFind = pHead, *pTemp = nullptr;
		while (pFind != nullptr)//��ͷ�����Ƚϣ�ÿ��������ͬ�ľͱ���
		{
			if (pFind->tData == tDataFind)
			{
				pTemp = pFind;
			}
			pFind = pFind->pNext;
		}

		return pTemp;
	}

	//ͷ��
	bool InsertHead(const DataType &tData)
	{
		//���䲢��ʼ��
		Node *pInsert = new(std::nothrow) Node{pHead,tData};
		if (pInsert == nullptr)
		{
			return false;
		}

		//����ͷ�ڵ�Ϊ�½ڵ�
		pHead = pInsert;

		return true;
	}

	//β��
	bool InsertTail(const DataType &tData)
	{
		//���䲢��ʼ��
		Node *pInsert = new(std::nothrow) Node{nullptr,tData};
		if (pInsert == nullptr)
		{
			return false;
		}

		if (pHead == nullptr)//ͷ�ڵ�
		{
			//����ͷ�ڵ�Ϊ�½ڵ�
			pHead = pInsert;
			return true;//ͷ��
		}

		Node *pTail = pHead;
		while (pTail->pNext != nullptr)//������ȡβ�ڵ�
		{
			pTail = pTail->pNext;
		}

		//�������һ���ڵ����һ���ڵ�Ϊ�½ڵ�
		pTail->pNext = pInsert;

		return true;
	}

	//�м����(��pInsertPrevָ���Ԫ�غ����)
	bool InsertMid(const DataType &tData, Node *pInsertPrev)
	{
		if (pInsertPrev == nullptr)
		{
			return false;
		}

		//���䲢��ʼ��
		Node *pInsert = new(std::nothrow) Node{pInsertPrev->pNext,tData};
		if (pInsert == nullptr)
		{
			return false;
		}

		//���ò�������һ���ڵ�Ϊ�½ڵ�
		pInsertPrev->pNext = pInsert;

		return true;
	}

	//ͷɾ
	bool RemoveHead(void)
	{
		if (pHead == nullptr)
		{
			return false;
		}

		//����ͷ��ָ��
		Node *pRemove = pHead;

		//����ͷָ��
		pHead = pHead->pNext;

		//ɾ��
		delete pRemove;
		pRemove = nullptr;

		return true;
	}

	//βɾ
	bool RemoveTail(void)
	{
		if (pHead == nullptr)
		{
			return false;
		}

		if (pHead == nullptr)//ͷ�ڵ�
		{
			return false;
		}
		else if (pHead->pNext == nullptr)//ֻ��һ��Ԫ��
		{
			delete pHead;
			pHead = nullptr;
		}

		Node *pTailPrev = pHead;
		while (pTailPrev->pNext->pNext != nullptr)//������ȡβ�ڵ��ǰ�ڵ�
		{
			pTailPrev = pTailPrev->pNext;
		}

		//ɾ��
		delete pTailPrev->pNext;
		pTailPrev->pNext = nullptr;

		return true;
	}

	//�м�ɾ��
	bool RemoveMid(Node *pRemove)
	{
		if (pRemove == nullptr)
		{
			return false;
		}

		if (pHead == nullptr)//ͷ�ڵ�
		{
			return false;
		}

		if (pRemove == pHead)//ֻ��һ��Ԫ��
		{
			delete pHead;
			pHead = nullptr;
		}

		Node *pRemovePrev = pHead;
		while (pRemovePrev->pNext != pRemove)//������ȡɾ���ڵ��ǰ�ڵ�
		{
			pRemovePrev = pRemovePrev->pNext;
		}

		//����ǰ�ڵ����һ���ڵ�Ϊɾ���ڵ����һ���ڵ�
		pRemovePrev->pNext = pRemove->pNext;

		//ɾ��
		delete pRemove;
		pRemove = nullptr;

		return true;
	}

	//ɾ������Ԫ�أ��������
	void RemoveAll(void)
	{
		Node *pDel = pHead;//pDel��Ŵ�ɾ���ڵ㣬��ͷ�ڵ㿪ʼɾ��
		while (pDel != nullptr)//����ɾ������Ԫ��
		{
			pHead = pHead->pNext;//�ƶ���ǰ�ڵ㵽��һ���ڵ�
			delete pDel;//ɾ����һ���ڵ�
			pDel = pHead;//��ɾ���ڵ���Ϊ��ǰ�ڵ�
		}

		//�ÿ�����
		pHead = nullptr;
	}

	//�Ƿ�Ϊ��
	bool IsEmpty(void)
	{
		return pHead == nullptr;
	}

	//��ȡͷ��ָ��
	Node *GetHead(void)
	{
		return pHead;
	}

	//��ȡβ��ָ��
	Node *GetTail(void)
	{
		if (pHead == nullptr)
		{
			return nullptr;
		}

		Node *pTail = pHead;
		while (pTail->pNext != nullptr)//������ȡβ�ڵ�
		{
			pTail = pTail->pNext;
		}

		return pTail;
	}
};
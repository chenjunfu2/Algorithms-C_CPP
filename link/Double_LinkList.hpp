#pragma once
#include <new>

template<typename DataType>
class Double_List
{
public:
	//�ڵ�����
	struct Node
	{
		Node *pPrev;//��һ���ڵ�
		Node *pNext;//��һ���ڵ�
		DataType tData;//����
	};
private:
	Node *pHead;//ͷ��
	Node *pTail;//β��
public:
	//Ĭ���޲ι���
	Double_List(void) :pHead(nullptr), pTail(nullptr)
	{}

	//����
	~Double_List(void)
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
		Node *pFind = pTail;
		while (pFind != nullptr)//��β�����Ƚ�
		{
			if (pFind->tData == tDataFind)
			{
				return pFind;
			}
			pFind = pFind->pPrev;
		}

		return nullptr;
	}
	
	//ͷ��
	bool InsertHead(const DataType &tData)
	{
		//���䲢��ʼ��
		Node *pInsert = new(std::nothrow) Node{nullptr,pHead,tData};
		if (pInsert == nullptr)
		{
			return false;
		}

		//����ͷ�ڵ�ָ��ǰһ���ڵ��ָ��Ϊ��ǰ����Ľڵ�
		if (pHead != nullptr)
		{
			pHead->pPrev = pInsert;
		}

		//����ͷ�ڵ�Ϊ�½ڵ�
		pHead = pInsert;

		//����β�ڵ�
		if (pTail == nullptr)
		{
			pTail = pInsert;
		}

		return true;
	}

	//β��
	bool InsertTail(const DataType &tData)
	{
		//���䲢��ʼ��
		Node *pInsert = new(std::nothrow) Node{pTail,nullptr,tData};
		if (pInsert == nullptr)
		{
			return false;
		}

		//����β�ڵ�ĺ�һ���ڵ�ָ��Ϊ��ǰ����Ľڵ�
		if (pTail != nullptr)
		{
			pTail->pNext = pInsert;
		}

		//����β�ڵ�Ϊ�½ڵ�
		pTail = pInsert;

		//����ͷ�ڵ�
		if (pHead == nullptr)
		{
			pHead = pInsert;
		}

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
		Node *pInsert = new(std::nothrow) Node{pInsertPrev,pInsertPrev->pNext,tData};
		if (pInsert == nullptr)
		{
			return false;
		}

		//���ò�������һ���ڵ�Ϊ�½ڵ�
		pInsertPrev->pNext = pInsert;

		//���������һ���ڵ㣬��ô��һ���ڵ����һ���ڵ�Ϊ�½ڵ�
		if (pInsert->pNext != nullptr)
		{
			pInsert->pNext->pPrev = pInsert;
		}
		else//�����������һ���ڵ㣬����ǰ�ڵ���β�ڵ�
		{
			pTail = pInsert;//����β�ڵ�Ϊ�²���Ľڵ�
		}

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

		//����ָ��
		pHead = pHead->pNext;
		if (pHead != nullptr)//����Ԫ��
		{
			pHead->pPrev = nullptr;//ȡ����ǰһ��Ԫ��ָ�������
		}
		else//ɾ����
		{
			pTail = nullptr;//β��ָ��ҲҪȡ�������һ��Ԫ�ص�����
		}

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

		//����β��ָ��
		Node *pRemove = pTail;

		//����ָ��
		pTail = pTail->pPrev;
		if (pTail != nullptr)//����Ԫ��
		{
			pTail->pNext = nullptr;//ȡ���Ժ�һ��Ԫ��ָ�������
		}
		else//ɾ����
		{
			pHead = nullptr;//ͷ��ָ��ҲҪȡ�������һ��Ԫ�ص�����
		}

		//ɾ��
		delete pRemove;
		pRemove = nullptr;

		return true;
	}

	//�м�ɾ��
	bool RemoveMid(Node *pRemove)
	{
		if (pRemove == nullptr)
		{
			return false;
		}

		//����ǰ�ڵ�ĺ�ڵ�ָ��ΪҪɾ���ڵ�ĺ�ڵ�ָ��
		if (pRemove->pPrev != nullptr)
		{
			pRemove->pPrev->pNext = pRemove->pNext;
		}
		else//Ҫɾ���ڵ���ͷ�ڵ�
		{
			pHead = pRemove->pNext;//����ͷ�ڵ�ָ��Ҫɾ���ڵ����һ���ڵ�
		}

		//���ú�ڵ��ǰ�ڵ�ָ��ΪҪɾ���ڵ��ǰ�ڵ�ָ��
		if (pRemove->pNext != nullptr)
		{
			pRemove->pNext->pPrev = pRemove->pPrev;
		}
		else//Ҫɾ���ڵ���β�ڵ�
		{
			pTail = pRemove->pPrev;//����β�ڵ�ָ��Ҫɾ���ڵ����һ���ڵ�
		}

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
		pTail = nullptr;
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
		return pTail;
	}
};
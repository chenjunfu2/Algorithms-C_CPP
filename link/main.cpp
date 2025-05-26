#include "Double_LinkList.hpp"
#include "Single_LinkList.hpp"

#include <stdio.h>

int main(void)
{
	Double_List<int> dl;
	Single_List<int> sl;

	for (int i = 0; i < 64; ++i)
	{
		dl.InsertHead(i);
		sl.InsertHead(i);

		dl.InsertTail(63 - i);
		sl.InsertTail(63 - i);
	}

	dl.InsertMid(-1, dl.FindFirst(32));
	sl.InsertMid(-1, sl.FindFirst(32));

	dl.InsertMid(-1, dl.FindLast(32));
	sl.InsertMid(-1, sl.FindLast(32));

	for (int i = 0; i < 16; ++i)
	{
		dl.RemoveHead();
		sl.RemoveHead();

		dl.RemoveTail();
		sl.RemoveTail();
	}

	dl.RemoveMid(dl.FindFirst(24));
	sl.RemoveMid(sl.FindFirst(24));

	dl.RemoveMid(dl.FindLast(24));
	sl.RemoveMid(sl.FindLast(24));


	puts("dl:");
	for (auto *it = dl.GetHead(); it != nullptr; it = it->pNext)
	{
		printf("%d ", it->tData);
	}

	puts("\n\nsl:");
	for (auto *it = sl.GetHead(); it != nullptr; it = it->pNext)
	{
		printf("%d ", it->tData);
	}

	puts("\n");

	printf("%d %d\n%d %d\n", dl.GetHead()->tData, dl.GetTail()->tData, sl.GetHead()->tData, sl.GetTail()->tData);

	dl.RemoveAll();
	sl.RemoveAll();

	printf("\n%d %p %p\n%d %p %p", dl.IsEmpty(), dl.GetHead(), dl.GetTail(), sl.IsEmpty(), sl.GetHead(), sl.GetTail());

	return 0;
}
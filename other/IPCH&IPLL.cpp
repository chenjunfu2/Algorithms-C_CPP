//#define __INPCHAR
#define __INPLLU

#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

#undef HIWORD
#undef LOWORD

#define HIWORD(ll,nn)	((ll)>>(nn))
#define LOWORD(ll,nn)	(((ll)<<(nn))>>(nn))


template<typename T,typename T1, typename T2>
void INWORD(T& a, T1 a1, T2 a2, int n)
{
	a = 0;
	a |= a1;
	a <<= n;
	a |= a2;
}

template<typename T, typename T1, typename T2>
void ANWORD(T& a, T1 a1, T2 a2, int n)
{
	T1 nx = HIWORD(a, n) ^ a1;
	T2 ny = LOWORD(a, n) ^ a2;
	INWORD(a, nx, ny, n);
}

unsigned long long atoull(char const* stri)
{
	unsigned long long n(0), i(0);
	size_t j = strlen(stri) - 1;

	while (stri[i] != '\0')
	{
		//0~9:48~57
		if (stri[i] >= 48 && stri[i] <= 57)
		{
			if (i != 0)
			{
				unsigned long long an(10);

				for (int k = 0; k < i - 1; ++k)
				{
					an *= 10;
				}

				n += an * ((unsigned long long)stri[j] - 48LLU);
			}
			else
			{
				n += ((unsigned long long)stri[j] - 48LLU);
			}
		}
		else
		{
			return 0LLU;
		}

		--j;
		++i;
	}

	return n;
}


#ifdef __INPCHAR

int main(void)
{
	unsigned long long n;
	unsigned int n1, n2, r1, r2, k, r;

	srand((unsigned int)time(nullptr));

	cout.fill('0');

	while (true)
	{
		k = 0;

		{
			Sleep(1);
			r1 = (double)rand() / RAND_MAX * 0x0000FFFF;
			Sleep(1);
			r2 = (double)rand() / RAND_MAX * 0x0000FFFF;
			
			INWORD(r, r1, r2, 16);
			//r ^= 0xD21963CE;
		}

		cout << "input:";

		while ((n1 = cin.get()) != '\n')
		{
			if (k == 0)
			{
				cout << "output:";
				cout.width(10);
				cout << r;

				k = 1;
			}

			{
				n = 0;
				ANWORD(n1, r1, r2, 16);
				n |= n1;
				n <<= 32;
			}

			if ((n2 = cin.get()) != '\n')
			{
				ANWORD(n2, r2, r1, 16);
				n |= n2;

				//n ^= 0xE3FF327A239BD1CE;
				cout.width(20);
				cout << n;
			}
			else
			{
				n |= 0x00000000;

				//n ^= 0xE3FF327A239BD1CE;
				cout.width(20);
				cout << n;

				break;
			}
		}

		cin.clear();
		cout << endl;
	}
	cin.clear();

	return 0;
}

#endif

#ifdef __INPLLU


int main(void)
{
	unsigned long long n;
	unsigned int n1, n2, r1, r2, k, r;
	char iptl[11], ipth[21];

	while (true)
	{
		k = 0;

		cout << "input:";

		{
			cin.get(iptl, 11);
			r = atoull(iptl);
			goto sdd;
		}

		while (cin.get(ipth, 21))
		{
			{
				n = atoull(ipth);
			}
		sdd:
			if (k == 0)
			{
				k = 1;

				r1 = HIWORD(r, 16);
				r2 = LOWORD(r, 16);

				cout << "output:";

				continue;
			}

			if (n != 0x0000000000000000)
			{
				n1 = HIWORD(n, 32);
				ANWORD(n1, r1, r2, 16);
				cout.put(n1);

				if ((n2 = LOWORD(n, 32)) != 0x00000000)
				{
					ANWORD(n2, r2, r1, 16);
					cout.put(n2);
				}
			}

			if ((k = cin.get()) != '\n')
			{
				cin.putback(k);
			}
			else
			{
				cin.putback(k);
				break;
			}
		}

		cin.clear();

		while (cin.get() != '\n')	continue;
		cout << endl;
	}
	cin.clear();

	return 0;
}


#endif

//2021.11.05
//�м� �� ���� : 4m 52s
//�Է� : 42s
//���� : 30m 55s

//�� : 36m 29s
//��Ǯ�鼭 ��û ��������


#include <iostream>
#include <cmath>

using namespace std;

int ifUnderPrime(int n);
bool ifPrime(int n);

int main()
{
	int A, B;
	cin >> A >> B;

	int tot = 0;
	//���� ���� ��������� ���ϱ�
	for (int i = A; i <= B; i++)
		if(ifUnderPrime(i))
			tot ++;

	cout << tot;

	return 0;
}

int ifUnderPrime(int n)
{
	if (n == 1) return false;
	int sqrtN = (int)(sqrt(n));
	int tot = 0;
	for (int i = 2; i <= sqrtN; i++)
	{
		if (!(n % i))
		{
			tot++;
			n = (int)(n / i);
			i--;
		}
	}

	if (n != 1)
		tot++;

	return ifPrime(tot);
}

bool ifPrime(int n)
{
	if (n == 1) return false;

	bool res = true;

	for (int i = 2; i <= (int)(sqrt(n)); i++)
	{
		if (!(n % i))
		{
			res = false;
			break;
		}
	}

	return res;
}
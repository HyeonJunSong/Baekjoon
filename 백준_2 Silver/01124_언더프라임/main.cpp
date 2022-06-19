//2021.11.05
//분석 및 설계 : 4m 52s
//입력 : 42s
//구현 : 30m 55s

//총 : 36m 29s
//※풀면서 엄청 졸았음※


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
	//포문 돌며 언더프라임 구하기
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
#include <iostream>

using namespace std;


int Combination(int n, int r);

int main()
{
	int T;
	cin >> T;

	int* N = new int[T];
	int* M = new int[T];
	for (int i = 0; i < T; i++)
	{
		cin >> N[i];
		cin >> M[i];
	}


	for (int i = 0; i < T; i++)
	{
		cout << Combination(M[i], N[i]) << endl;
	}

	return 0;
}

int Combination(int n, int r) // n = 2, r = 3
{
	if (r > 4);
	else if (r == 4)
		return n * (n - 1) * (n - 2) * (n - 3) / 24;
	else if (r == 3)
		return n * (n - 1) * (n - 2) / 6;
	else if (r == 2) // 0
		return (n * (n - 1)) / 2;
	else if (r == 1)
		return n;

	int tot = 0;

	for (int i = 0; i < n - r + 1; i++)
	{
		tot += Combination(n - i - 1, r - 1);
	}

	return tot;
}
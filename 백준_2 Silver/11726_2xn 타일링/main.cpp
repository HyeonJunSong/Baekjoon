#include <iostream>

using namespace std;

int tiling(int N);
int memo[1001] = { 0 };

int main()
{
	int N;
	cin >> N;
	memo[1] = 1;
	memo[2] = 2;

	cout << tiling(N);
}

int tiling(int N)
{
	if (memo[N] != 0)
		return memo[N];

	int tot = 0;
	tot += tiling(N - 2);
	tot += tiling(N - 1);

	tot %= 10007;
	memo[N] = tot;


	return tot;
}
//2021.11.03
//입력 : 1m 49s
//해결 : 26m 5s

//총 : 27m 54s


#include <iostream>
#include <cmath>

using namespace std;

int minMove(int x, int y);

int main()
{
	int T;
	cin >> T;

	int* x = new int[T];
	int* y = new int[T];
	for (int i = 0; i < T; i++)
		cin >> x[i] >> y[i];

	for (int i = 0; i < T; i++)
		cout << minMove(x[i], y[i]) << endl;

	return 0;
}

int minMove(int x, int y)
{
	int distance = y - x;

	int n = (int)(sqrt(double(distance)));


	if (distance == n * n)
		return 2 * n - 1;
	else if (distance <= n * (n + 1))
		return 2 * n;
	else
		return 2 * n + 1;

}
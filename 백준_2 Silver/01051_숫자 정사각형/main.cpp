//2021.11.04
//�м� �� ���� : 5m 12s
//�Է� : 1m 56s
//���� : 11m 29s


#include <iostream>

using namespace std;

int main()
{
	int N, M;
	cin >> N >> M;

	string* rect = new string[N];
	for (int i = 0; i < N; i++)
		cin >> rect[i];

	int min = N;
	if (min > M) min = M;

	int res = 1;

	for (int l = 1; l <= min; l++)
	{
		for (int i = 0; i <= N - l; i++)
		{
			for (int j = 0; j <= M - l; j++)
			{
				bool ifAllSame = true;
				char num = rect[i][j];

				if (rect[i + (l - 1)][j] != num) ifAllSame = false;
				else if (rect[i][j + (l - 1)] != num) ifAllSame = false;
				else if (rect[i + (l - 1)][j + (l - 1)] != num) ifAllSame = false;

				if (ifAllSame)
					res = l;
			}
		}
	}

	cout << res * res;

	return 0;
}
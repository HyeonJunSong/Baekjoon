//2021.11.04
//�м� �� ���� : 3m 42s
//�Է� : 37s
//���� : 4m

//�� : 8m 19s

#include <iostream>

using namespace std;

int main()
{
	int N, k, l;
	cin >> N >> k >> l;

	k--;
	l--;
	int round = 1;

	while (true)
	{

		if ((int)(k / 2) == (int)(l / 2))
			break;

		k = (int)(k / 2);
		l = (int)(l / 2);
		round++;
	}

	cout << round;

	return 0;
}
/*
//2121.11.05
//�м� �� ���� : 5m 1s
//�Է� : 1m 58s
//���� : 12m 40s

#include <iostream>
#include <string>

using namespace std;

bool ifJeopDoo(string strA, string strB);	//A�� B�� ���ξ�����

int main()
{
	int N;
	cin >> N;

	string* str = new string[N];
	for (int i = 0; i < N; i++)
		cin >> str[i];

	int cnt = 0;
	bool* sameCheck = new bool[N] {false};
	for (int i = 0; i < N; i++)
	{
		if (sameCheck[i]) continue;

		bool ifJ = false;
		for (int j = 0; j < N; j++)
		{
			if (i == j) continue;

			if (str[i] == str[j])
			{
				sameCheck[j] = true;
				continue;
			}

			if(ifJeopDoo(str[i], str[j]))
			{
				ifJ = true;
				break;
			}
		}
		if (!ifJ) cnt++;
	}

	cout << cnt;

	return 0;
}

bool ifJeopDoo(string strA, string strB)	//A�� B�� ���ξ�����
{
	if (strA.length() > strB.length()) return false;

	bool ifTrue = true;
	for (int i = 0; i < (int)strA.length(); i++)
		if (strA[i] != strB[i]) ifTrue = false;

	return ifTrue;
}
*/
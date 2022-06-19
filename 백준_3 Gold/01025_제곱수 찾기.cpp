//2021.11.03
//ют╥б : 4m 58s

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int StringToInt(string str);
int maxSquare(string* arr, int N, int M, int iP, int jP);

int main()
{
	int N, M;
	cin >> N >> M;

	string* arr = new string [N];
	for (int i = 0; i < N; i++)
		cin >> arr[i];

	int maxNum = -1;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			int temp = maxSquare(arr, N, M, i, j);
			if (temp > maxNum)
				maxNum = temp;
		}
	}

	cout << maxNum;

	return 0;
}

int StringToInt(string str)
{
	int tot = 0;
	int len = str.length();

	for (int i = 0; i < len; i++)
		tot += (int)(str[i] - '0') * (int)(pow(10, len - i - 1));


	return tot;
}


int maxSquare(string* arr, int N, int M, int iP, int jP)
{
	int res = -1;
	if (arr[iP][jP] == '0') res = 0;
	else if (arr[iP][jP] == '1') res = 1;
	else if (arr[iP][jP] == '4') res = 4;
	else if (arr[iP][jP] == '9') res = 9;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (iP == i && jP == j)
				continue;

			string sNum = "";
			sNum += arr[iP][jP];
			int num;
			sNum += arr[i][j];

			num = StringToInt(sNum);
			if ((int)(pow((int)(sqrt(num)), 2)) == num)
				if (res < num)
					res = num;

			int id = i - iP;
			int jd = j - jP;
			int n = 2;
			while (0 <= iP + n * id && iP + n * id < N && 0 <= jP + n * jd && jP + n * jd < M)
			{
				sNum += arr[iP + n * id][jP + n * jd];
				
				num = StringToInt(sNum);
				if ((int)(pow((int)(sqrt(num)), 2)) == num)
					if (res < num)
						res = num;

				n++;
			}

		}
	}

	return res;
}
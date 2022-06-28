//2021.11.06
//분석 및 설계 : 10m 5s
//입력 : 1m 41s
//구현 : 57m 34s
//소숫점 자릿수 출력때문에 오답나옴 -> 다른건줄알고 계속 시간까먹음

#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

int main()
{
	int N;
	cin >> N;

	long double** coor = new long double* [N];
	for (int i = 0; i < N; i++)
	{
		coor[i] = new long double[2];
		cin >> coor[i][0] >> coor[i][1];
	}

	long double max = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			for (int k = j + 1; k < N; k++)
			{
				long double a = sqrt(pow(coor[j][0] - coor[i][0], 2) + pow(coor[j][1] - coor[i][1], 2));
				long double b = sqrt(pow(coor[k][0] - coor[j][0], 2) + pow(coor[k][1] - coor[j][1], 2));
				long double c = sqrt(pow(coor[i][0] - coor[k][0], 2) + pow(coor[i][1] - coor[k][1], 2));
				long double s = (a + b + c) / 2;

				long double area = sqrt(s * (s - a) * (s - b) * (s - c));

				/*
				long double area = ((coor[i][0] * coor[j][1] + coor[j][0] * coor[k][1] + coor[k][0] * coor[i][1]) 
					- (coor[i][1] * coor[j][0] + coor[j][1] * coor[k][0] + coor[k][1] * coor[i][0])) / 2;
				if (area < 0) area *= -1;
				*/

				if (area > max) max = area;
			}
		}
	}

	cout.precision(10);
	cout << fixed;
	cout << max;
	cout.unsetf(ios::fixed);

	return 0;
}
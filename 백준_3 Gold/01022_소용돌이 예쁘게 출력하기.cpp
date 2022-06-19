/*
//2021.11.03

//이해 및 설계 : 4m 15s
//입력 : 1m 47s
//구현 : 2h 7m 11s 에서 포기... 애초에 설계를 잘못했음 문제 개 엿같음 시발거

#include <iostream>
#include <cmath>
using namespace std;

int getNum(int i, int j);
void printPretty(int digit, int i, int j, bool ifLast);


int main()
{
	int r1, c1, r2, c2;
	cin >> r1 >> c1 >> r2 >> c2;
	

	int max = 0;
	int n1 = getNum(r1, c1);
	int n2 = getNum(r1, c2);
	int n3 = getNum(r2, c1);
	int n4 = getNum(r2, c2);
	if (max < n1) max = n1;
	else if (max < n2) max = n2;
	else if (max < n3) max = n3;
	else if (max < n4) max = n4;


	int digit = 1;
	while (true)
	{
		if (!(int)(max / (int)(pow(10, digit))))
			break;
		digit++;
	}

	for (int i = r1; i <= r2; i++)
	{
		for (int j = c1; j <= c2; j++)
		{
			bool ifLast = false;
			if (j == c2) ifLast = true;
			printPretty(digit, i, j, ifLast);
		}
		if (i != r2) cout << endl;
	}

	return 0;
}


void makeBoard(int** board, int n)
{
	board[n][n] = 1;

	int cnt = 1;
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < (i + 1) * 2; k++)
		{
			board[n + i - k][n + 1 + i] = ++cnt;
		}

		for (int k = 0; k < (i + 1) * 2; k++)
		{
			board[n - 1 - i][n + i - k] = ++cnt;
		}

		for (int k = 0; k < (i + 1) * 2; k++)
		{
			board[n - i + k][n - 1 - i] = ++cnt;
		}

		for (int k = 0; k < (i + 1) * 2; k++)
		{
			board[n + 1 + i][n - i + k] = ++cnt;
		}
	}
}

int getNum(int i, int j)
{
	int num;
	////숫자구하기
	//n 구하기
	int n = 0;
	int oC;	// other Coordinate
	if (abs(i) < abs(j))
	{
		n = abs(j);
		oC = i;
	}
	else
	{
		n = abs(i);
		oC = j;
	}
	//본인의 케이스를 구한다
	// 꼭짓점    //    0:y+ 1:x- 2:y- 3:x+
	int c = 0;
	if (abs(i) == abs(j))
	{
		if (i > 0 && j > 0) c = 0;
		else if (i > 0 && j < 0) c = 1;
		else if (i < 0 && j < 0) c = 2;
		else if (i < 0 && j > 0) c = 3;

		switch (c)
		{
		case 0: case 1:
			oC = n;
			break;
		case 2: case 3:
			oC = -n;
			break;
		}
	}
	else if (i == n) c = 0;
	else if (-j == n) c = 1;
	else if (-i == n) c = 2;
	else if (j == n) c = 3;


	//케이스에 따라 계산
	switch (c)
	{
	case 0:	case 1:
		num = (2 * n + 1) * (2 * n + 1) - c * 2 * n - (n - oC);
		break;
	case 2:	case 3:
		num = (2 * n + 1) * (2 * n + 1) - c * 2 * n - (n + oC);
		break;
	}
	return num;
}

void printPretty(int digit, int i, int j, bool ifLast)
{
	int num = getNum(i, j);

	//num의 자릿수 구하기
	int Curdigit = 1;
	while (true)
	{
		if (!(int)(num / (int)(pow(10, Curdigit))))
			break;
		Curdigit++;
	}


	//출력
	for (int i = 0; i < digit - Curdigit; i++) cout << ' ';
	cout << num;
	if (!ifLast) cout << ' ';
}
*/
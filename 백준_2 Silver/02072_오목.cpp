//2021.11.02
//입력_ 5m 26s
//풀이_1h 18m 39s

//총_ 1h 24m 5s

#include <iostream>
using namespace std;

int board[19][19] = { 0 };	// 1: 흑, 2: 백
bool ifWin(int xP, int yP);

int main()
{
	int N;
	cin >> N;

	int ans = -1;
	bool end = false;

	for (int i = 0; i < N; i++)
	{
		int x, y;
		cin >> y >> x;

		if (!(i % 2))
			board[y - 1][x - 1] = 1;
		else
			board[y - 1][x - 1] = 2;

		if (!end && ifWin(x - 1, y - 1))
		{
			ans = i + 1;
			end = true;
		}
	}

	cout << ans;


	return 0;
}

bool ifWin(int xP, int yP)
{
	int color = board[yP][xP];
	int x, y;
	int cnt;

	int state = 0; // 0 : 미상, 1: 오목, 2: 육목 이상

	////가로
	x = xP, y = yP;
	cnt = 1;

	//끝지점 찾기
	while (x != 0 && board[y][x - 1] == color)
		x--;

	//반대쪽으로 가면서 세기
	while (x != 18 && board[y][x + 1] == color)
	{
		x++;
		cnt++;
	}
	//5일때 res true
	if (state != 2)
	{
		if (cnt == 5)
			state = 1;
		else if (cnt > 5)
			state = 2;
	}


	//세로
	x = xP, y = yP;
	cnt = 1;

	//끝지점 찾기
	while (y != 0 && board[y - 1][x] == color)
		y--;

	//반대쪽으로 가면서 세기
	while (y != 18 && board[y + 1][x] == color)
	{
		y++;
		cnt++;
	}
	//5일때 res true
	if (state != 2)
	{
		if (cnt == 5)
			state = 1;
		else if (cnt > 5)
			state = 2;
	}



	//대각선
	x = xP, y = yP;
	cnt = 1;

	//끝지점 찾기
	while (x != 0 && y != 0 && board[y - 1][x - 1] == color)
		x--, y--;

	//반대쪽으로 가면서 세기
	while (x != 18 && y != 18 && board[y + 1][x + 1] == color)
	{
		x++, y++;
		cnt++;
	}
	//5일때 res true
	if (state != 2)
	{
		if (cnt == 5)
			state = 1;
		else if (cnt > 5)
			state = 2;
	}

	if (state == 1)
		return true;



	//다른 대각선
	x = xP, y = yP;
	cnt = 1;

	//끝지점 찾기
	while (x != 18 && y != 0 && board[y - 1][x + 1] == color)
		x++, y--;

	//반대쪽으로 가면서 세기
	while (x != 0 && y != 18 && board[y + 1][x - 1] == color)
	{
		x--, y++;
		cnt++;
	}
	//5일때 res true
	if (state != 2)
	{
		if (cnt == 5)
			state = 1;
		else if (cnt > 5)
			state = 2;
	}

	if (state == 1)
		return true;

	return false;
}
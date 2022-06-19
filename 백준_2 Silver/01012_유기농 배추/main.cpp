/*

//2021.11.05
//분석 및 설계 : 3m 38s
//입력 : 7m 28s 
//구현 : 1h 20에서 포기 _ 런타임에러남

#include <iostream>
#include <vector>

using namespace std;

int mazeOrder[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };	// y, x
typedef struct Node
{
	int x;
	int y;
	int dir;
}node;

int minimumBug(int M, int N, int K, int** cabbage);

int main()
{
	int T;
	cin >> T;
	int* M = new int[T];
	int* N = new int[T];
	int* K = new int[T];
	int*** cabbage = new int** [T];

	for (int i = 0; i < T; i++)
	{
		cin >> M[i] >> N[i] >> K[i];

		cabbage[i] = new int* [K[i]];
		for(int j = 0; j < K[i]; j++)
		{
			cabbage[i][j] = new int[2];
			cin >> cabbage[i][j][0] >> cabbage[i][j][1];
		}
	}

	for (int i = 0; i < T; i++)
		cout << minimumBug(M[i], N[i], K[i], cabbage[i]) << endl;

	return 0;
}

int minimumBug(int M, int N, int K, int** cabbage)
{
	bool** farm = new bool* [N + 2];
	bool** check = new bool* [N + 2];
	for (int i = 0; i < N + 2; i++)
	{
		farm[i] = new bool[M + 2]{ false };
		check[i] = new bool[M + 2]{ false };
	}
	for (int i = 0; i < K; i++)
	{
		farm[cabbage[i][1] + 1][cabbage[i][0] + 1] = true;
	}
	vector<node> stack;	//미로탐색에 쓰일 스택.

	int cnt = 0;

	for (int i = 1; i < N + 1; i++)
	{
		for (int j = 1; j < M + 1; j++)
		{
			if (check[i][j] || !farm[i][j]) continue;

			int x = j, y = i;
			node n = { x, y, -1 };
			stack.push_back(n);

			while (!stack.empty())
			{
				node cur = stack.back();
				stack.pop_back();

				check[cur.y][cur.x] = true;

				while (cur.dir <= 3)
				{
					cur.dir++;

					if (farm[cur.y + mazeOrder[cur.dir][0]][cur.x + mazeOrder[cur.dir][1]] &&
						!check[cur.y + mazeOrder[cur.dir][0]][cur.x + mazeOrder[cur.dir][1]])
					{
						node next = { cur.x + mazeOrder[cur.dir][1], cur.y + mazeOrder[cur.dir][0], -1 };
						stack.push_back(cur);
						stack.push_back(next);
						break;
					}
				}

			}

			cnt++;
		}
	}

	return cnt;
}
*/
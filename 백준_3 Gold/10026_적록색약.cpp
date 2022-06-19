//2021.12.11
//설계 : 7m 41s
//입력 : 3m 19s
//구현 : 29m 4s

#include <iostream>
#include <string>
#include <list>

using namespace std;

int coor[8][2] = {
	{-1, 0},
	{ 0, 1},
	{ 1, 0},
	{ 0,-1},
};

typedef struct Node {
	int y;
	int x;
}node;

int numOfDistriction(string* field, int N);

int main() {
	int N;
	cin >> N;
	string* field = new string[N];
	for (int i = 0; i < N; i++) {
		cin >> field[i];
	}

	cout << numOfDistriction(field, N) << ' ';

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (field[i][j] == 'G') field[i][j] = 'R';
		}
	}

	cout << numOfDistriction(field, N);

	return 0;
}

int numOfDistriction(string* field, int N) {
	list<node> Q;
	bool** check = new bool* [N];
	for (int i = 0; i < N; i++) check[i] = new bool[N] {false};
	int cnt = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!check[i][j]) {
				node temp = { i, j };
				Q.push_back(temp);
				char color = field[i][j];
				check[i][j] = true;

				while (!Q.empty()) {
					node cur = Q.front();
					Q.pop_front();

					for (int i = 0; i < 4; i++) {
						if (0 <= cur.y + coor[i][0] && cur.y + coor[i][0] < N
						 && 0 <= cur.x + coor[i][1] && cur.x + coor[i][1] < N) {
							if (field[cur.y + coor[i][0]][cur.x + coor[i][1]] == color) {
								if (!check[cur.y + coor[i][0]][cur.x + coor[i][1]]) {
									node nex = { cur.y + coor[i][0] , cur.x + coor[i][1] };
									check[cur.y + coor[i][0]][cur.x + coor[i][1]] = true;
									Q.push_back(nex);
								}
							}
						}
					}
				}

				cnt++;
			}
		}
	}
	return cnt;
}
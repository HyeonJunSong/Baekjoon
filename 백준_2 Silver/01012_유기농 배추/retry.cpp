//22.01.01

#include <iostream>
#include <list>

using namespace std;

int direction[4][2] = {
	{-1,  0},
	{ 0,  1},
	{ 1,  0},
	{ 0 ,-1}
};

typedef struct Node {
	int I;
	int J;
}node;

int main() {
	int T;
	cin >> T;


	for (int t = 0; t < T; t++) {

		int M, N, K;
		cin >> M >> N >> K;
		bool** field = new bool*[N];
		for (int i = 0; i < N; i++)
			field[i] = new bool[M] {false};

		for (int i = 0; i < K; i++) {
			int I, J;
			cin >> J >> I;
			field[I][J] = true;
		}

		int tot = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (!field[i][j]) continue;

				//현재좌표와 인접한 배추들을 모두 색칠 후 리턴. =>큐.
				list<node> Queue;
				Queue.push_back({ i, j });
				field[i][j] = false;

				while (!Queue.empty()) {
					node cur = Queue.front();
					Queue.pop_front();


					for (int dir = 0; dir < 4; dir++) {
						if (0 <= cur.I + direction[dir][0] && cur.I + direction[dir][0] < N) {
							if (0 <= cur.J + direction[dir][1] && cur.J + direction[dir][1] < M) {
								if (field[cur.I + direction[dir][0]][cur.J + direction[dir][1]]) {
									Queue.push_back({ cur.I + direction[dir][0], cur.J + direction[dir][1] });
									field[cur.I + direction[dir][0]][cur.J + direction[dir][1]] = false;
								}
							}
						}
					}
				}
				tot++;
			}
		}

		cout << tot << endl;
	}

	return 0;
}
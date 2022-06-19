////21.12.16
//이해 및 설계 : 17m 9s
//입력 : 1m 52s
//구현 : 1h 2s

//tot : 1h 19m 3s

#include <iostream>
#include <vector>

using namespace std;
#define MAX 987654321;

int combination(int n, int r, int** distance, int remain, vector<int> res, int numOfHouse);
int minimumDistance(vector<int> res, int** distance, int numOfHouse);

typedef struct Node {
	int y;
	int x;
}node;

int main() {
	int N, M;
	cin >> N >> M;

	int** map = new int* [N];
	for (int i = 0; i < N; i++) {
		map[i] = new int[N];
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	
	//변수
	vector<node> chicken;	//치킨집 좌표
	vector<node> house;	//집 좌표

	int** distance;	//치킨집과 집사이의 거리

	//치킨집과 집의 좌표구하기

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 1) house.push_back({ i, j });
			else if (map[i][j] == 2) chicken.push_back({ i, j });
		}
	}

	



	//각 치킨집에서 집들까지의 거리를 나타내는 배열 만들기
	distance = new int* [(int)(chicken.size())];
	for (int i = 0; i < (int)(chicken.size()); i++) distance[i] = new int[(int)(house.size())];

	for (int i = 0; i < int(chicken.size()); i++) {
		for (int j = 0; j < (int)(house.size()); j++) {
			distance[i][j] = abs(chicken[i].y - house[j].y) + abs(chicken[i].x - house[j].x);
		}
	}


	//조합

	int finalMinDis = MAX;

	for (int i = 1; i <= M; i++) {
		vector<int> res;
		int minDis = combination((int)(chicken.size()), i, distance, 0, res, (int)(house.size()));
		if (minDis < finalMinDis) finalMinDis = minDis;
	}
	cout << finalMinDis;

	return 0;
}

int combination(int n, int r, int** distance, int remain, vector<int> res, int numOfHouse) {
	int minDis = MAX;
	if (r == 0) {
		return minimumDistance(res, distance, numOfHouse);
	}

	for (int i = remain; i <= n - r; i++) {
		res.push_back(i);

		int totDis = combination(n, r - 1, distance, i + 1, res, numOfHouse);
		if (totDis < minDis) minDis = totDis;

		res.pop_back();
	}

	return minDis;
}

int minimumDistance(vector<int> res, int** distance, int numOfHouse) {
	int totMinDis = 0;
	for (int i = 0; i < numOfHouse; i++) {
		int minDis = MAX;
		for (int j = 0; j < (int)(res.size()); j++) {
			if (distance[res[j]][i] < minDis) minDis = distance[res[j]][i];
		}

		totMinDis += minDis;
	}

	return totMinDis;
}
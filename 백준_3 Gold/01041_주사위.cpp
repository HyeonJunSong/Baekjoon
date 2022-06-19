////21.12.17
//분석 및 설계 : 20m 25s
//입력 : 1m 20s
//구현 : 20m 1s
//tot : 41m 46s

#include <iostream>

using namespace std;

#define MAX 123456789

int threeSides[8][3] = {
	{ 0, 1, 2 },
	{ 0, 1, 3 },
	{ 0, 4, 2 },
	{ 0, 4, 3 },
	{ 5, 1, 2 },
	{ 5, 1, 3 },
	{ 5, 4, 2 },
	{ 5, 4, 3 },
};

int twoSides[12][2] = {
	{ 0, 1 },
	{ 0, 2 },
	{ 0, 3 },
	{ 0, 4 },
	{ 5, 1 },
	{ 5, 2 },
	{ 5, 3 },
	{ 5, 4 },
	{ 1, 2 },
	{ 1, 3 },
	{ 4, 2 },
	{ 4, 3 },
};


int main() {
	double N;
	cin >> N;
	
	double dice[6];
	for (int i = 0; i < 6; i++) cin >> dice[i];


	if (N == 1.0) {
		//1면의 최대값
		double maxOfOne = 0;
		for (int i = 0; i < 6; i++) {
			if (dice[i] > maxOfOne) maxOfOne = dice[i];
		}

		int tot = 0;
		for (int i = 0; i < 6; i++) tot += dice[i];
		tot -= maxOfOne;

		cout.precision(0);
		cout << fixed;
		cout << tot;
		cout.unsetf(ios::fixed);
	
	}
	else {
		//3면의 최솟값
		double minOfThree = MAX;
		for (int i = 0; i < 8; i++) {
			int sum = dice[threeSides[i][0]] + dice[threeSides[i][1]] + dice[threeSides[i][2]];
			if (sum < minOfThree) minOfThree = sum;
		}

		//2면의 최솟값
		double minOfTwo = MAX;
		for (int i = 0; i < 12; i++) {
			int sum = dice[twoSides[i][0]] + dice[twoSides[i][1]];
			if (sum < minOfTwo) minOfTwo = sum;
		}

		//1면의 최솟값
		double minOfOne = MAX;
		for (int i = 0; i < 6; i++) {
			if (dice[i] < minOfOne) minOfOne = dice[i];
		}



		//답 구하기
		double tot = 0;
		tot += minOfThree * 4;
		tot += minOfTwo * (8 * (N - 2) + 4);
		tot += minOfOne * (N - 2) * (5 * N - 6);

		cout.precision(0);
		cout << fixed;
		cout << tot;
		cout.unsetf(ios::fixed);
	}

	return 0;
}
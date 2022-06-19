////22.02.02
//���� �� ���� : 35m 53s
//�Է� : 1m 51s
//���� : 1h 28m 56s

//tot : 2h 06m 40s

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int primeTable[15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

bool ifRight(int N, vector<int>* goal, vector<int> current);

int main() {
	int N;
	cin >> N;
	int* P = new int[N];
	for (int i = 0; i < N; i++) cin >> P[i];

	int* S = new int[N];
	for (int i = 0; i < N; i++) cin >> S[i];

	//������ǥ
	vector<int>* goal = new vector<int>[3];
	for (int i = 0; i < N; i++) {
		goal[P[i]].push_back(i);
	}

	//��ȯ���� �ľ�
	bool* check = new bool[N] {false};
	vector<int> cir;

	for (int i = 0; i < N; i++) {
		if (check[i]) continue;

		int cnt = 1;
		int next = S[i];
		check[i] = true;
		while (next != i) {
			cnt++;
			check[next] = true;
			next = S[next];
		}

		cir.push_back(cnt);
	}

	////�ּ� ��ȯȽ�� ���ϱ�

	//���ڵ� �� ����ϱ�
	vector<int*> table = vector<int*>(cir.size());
	for (vector<int>::size_type i = 0; i < cir.size(); i++) {
		table[i] = new int[15]{0};
		while (cir[i] != 1) {
			for (int j = 0; j < 15; j++) {
				if (!(cir[i] % primeTable[j])) {
					table[i][j]++;
					cir[i] = (int)(cir[i] / primeTable[j]);
					break;
				}
			}
		}
	}

	//�ּҰ���� ���ϱ�
	int minNum = 1;
	for (int i = 0; i < 15; i++) {
		int max = table[0][i];
		for (vector<int*>::size_type j = 1; j < table.size(); j++)
			if (table[j][i] > max) max = table[j][i];

		minNum *= pow(primeTable[i], max);
	}

	////���� ���ϰ� �ݺ�
	vector<int> original;
	for (int i = 0; i < N; i++) original.push_back(i);
	
	int cnt = 0;
	for (int i = 0; i < minNum; i++) {
		if (ifRight(N, goal, original)) break;

		//����

		int next[48];
		for (int j = 0; j < N; j++) {
			next[S[j]] = original[j];
		}
		original.clear();
		for (int j = 0; j < N; j++) {
			original.push_back(next[j]);
		}
		cnt++;
	}

	if (cnt == minNum) {
		cout << -1;
	}
	else {
		cout << cnt;
	}


	return 0;
}

bool ifRight(int N, vector<int>* goal, vector<int> current) {
	for (int i = 0; i < N; i++) {
		bool ifIn = false;
		for (vector<int>::size_type j = 0; j < goal[i % 3].size(); j++)
			if (goal[i % 3][j] == current[i])
				ifIn = true;

		if (!ifIn) {
			return false;
		}
	}

	return true;
}
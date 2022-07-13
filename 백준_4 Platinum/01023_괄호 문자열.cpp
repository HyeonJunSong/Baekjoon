#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<long long>> memo;

long long N;

long long possibleNum(long long nL, long long nR);
string getKth(string cur, long long nL, long long nR, long long K);
bool ifPossible(string cur);

int main() {
	long long K;
	cin >> N >> K;

	memo = vector<vector<long long>>(N + 1, vector<long long>(N + 1, -1));

	long long max = possibleNum(0, 0);

	if (K >= max) {
		cout << -1;
	}
	else {
		cout << getKth("", 0, 0, K + 1);
	}

	/*
	for (int k = 1; k <= pow(2, N); k++) {
		cout << endl << getKth("", 0, 0, k);
	}
	*/

	return 0;
}

long long possibleNum(long long nL, long long nR) {

	if (nL < nR) return (long long)(pow(2, N - (nL + nR)));
	if (nL > ((double)(N) / 2)) return (long long)(pow(2, N - (nL + nR)));

	if (memo[nL + 1][nR] == -1) memo[nL + 1][nR] = possibleNum(nL + 1, nR);
	if (memo[nL][nR + 1] == -1) memo[nL][nR + 1] = possibleNum(nL, nR + 1);

	return memo[nL + 1][nR] + memo[nL][nR + 1];
}

string getKth(string cur, long long nL, long long nR, long long K) {

	if (K == 1) {
		int curSize = cur.size();
		for (int i = 0; i < N - curSize; i++) cur += '(';
		return cur;
	}

	if (nL + nR == N) {
		return cur;
	}

	long long curPossibleNum;
	if (ifPossible(cur)) curPossibleNum = (long long)(pow(2, N - (nL + nR) - 1));
	else curPossibleNum = possibleNum(nL + 1, nR);

	if (curPossibleNum < K) {
		return getKth(cur + ')', nL, nR + 1, K - curPossibleNum);
	}
	else {
		return getKth(cur + '(', nL + 1, nR, K);
	}
}

bool ifPossible(string cur) {

	int nL = 0;
	int nR = 0;

	for (int i = 0; i < cur.size(); i++) {
		if (cur[i] == '(') nL++;
		else nR++;

		if (nL < nR) return true;
	}

	return false;
}
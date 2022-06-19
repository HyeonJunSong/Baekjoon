////2022.01.11
//48m 34s

#include <iostream>
#include <string>

using namespace std;

int retNum(int r, int c);

int main() {

	int r1, c1, r2, c2;
	cin >> r1 >> c1 >> r2 >> c2;

	int rLen = r2 - r1 + 1;
	int cLen = c2 - c1 + 1;

	int** arr = new int* [rLen];
	for (int i = 0; i < rLen; i++) arr[i] = new int[cLen];

	int maxDigit = 0;
	for (int i = 0; i < rLen; i++) {
		for (int j = 0; j < cLen; j++) {
			arr[i][j] = retNum(r1 + i, c1 + j);
			int curDigit = to_string(arr[i][j]).size();
			if (curDigit > maxDigit) maxDigit = curDigit;
		}
	}
	for (int i = 0; i < rLen; i++) {
		for (int j = 0; j < cLen; j++) {

			int curDigit = to_string(arr[i][j]).size();
			for (int k = 0; k < maxDigit - curDigit; k++) cout << ' ';
			cout << arr[i][j];

			if (j == cLen - 1) cout << endl;
			else cout << ' ';
		}
	}

	return 0;
}

int retNum(int r, int c) {
	int n;
	abs(c) > abs(r) ? n = abs(c) : n = abs(r);

	int S = 4 * n * n - 4 * n + 1;

	if (c == n) {
		if (r == n) return S + 8 * n;
		else return S + (n - r);
	}
	else if (r == -1 * n) return S + n * 2 + (n - c);
	else if (c == -1 * n) return S + n * 4 + (n + r);
	else if (r == n) return S + n * 6 + (n + c);
}
#include <iostream>
#include <cmath>

using namespace std;

int minN(int N, int n);

int main() {
	int N, L;

	cin >> N >> L;

	for (int n = L; n <= 100; n++) {
		int ifPossible = minN(N, n);
		if (ifPossible != -1) {
			for (int j = 0; j < n; j++)
				cout << ifPossible + j << ' ';
			return 0;
		}
	}

	cout << -1;
	return 0;
}

int minN(int N, int n) {
	double res = ((2 * N) / (double)(n)-n + 1) / (double)(2);
	if (res == (int)(res) && (int)(res) >= 0){
		return (int)(res);
	}
	return -1;
}
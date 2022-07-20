#include <iostream>
#include <cmath>

using namespace std;

int s, N, K, r1, r2, c1, c2;

int curColor(int r, int c, int curS);
int main() {

	cin >> s >> N >> K >> r1 >> r2 >> c1 >> c2;

	for (int i = r1; i <= r2; i++) {
		for (int j = c1; j <= c2; j++) {
			cout << curColor(i, j, s);
		}
		cout << "\n";
	}

	return 0;
}

int curColor(int r, int c, int curS) {

	if (curS == 0) return 0;

	if (pow(N, curS - 1) * (N - K) / 2 <= r && r < pow(N, curS - 1) * (N + K) / 2
		&& pow(N, curS - 1) * (N - K) / 2 <= c && c < pow(N, curS - 1) * (N + K) / 2) {
		return 1;
	}

	r %= (int)(pow(N, curS - 1));
	c %= (int)(pow(N, curS - 1));


	return curColor(r, c, curS - 1);
}
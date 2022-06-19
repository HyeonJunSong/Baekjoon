#include <iostream>
#include <vector>

using namespace std;
int combi(int n, int r);

int main() {
	int N;
	cin >> N;

	if (N < 10) {
		cout << N;
	}
	else if (N > 1022) {
		cout << -1;
	}
	else {
		//자릿수 구하기
		int n = 1;
		int tot = 9;

		while (true) {
			int thisDigit = combi(10, n + 1);
			if (tot + thisDigit >= N) {
				break;
			}
			tot += thisDigit;
			n++;
		}
		n++;

		//숫자 구하기
		int num = n - 1;
		vector<int> res;

		while (true) {
			while (true) {
				int thisDigit = combi(num, n - 1);
				if (tot + thisDigit < N) {
					num++;
					tot += thisDigit;
				}
				else break;
			}
			if (n == 1) {
				res.push_back(num);
				break;
			}

			res.push_back(num);
			n--;
			num = n - 1;
		}

		for (vector<int>::size_type i = 0; i < res.size(); i++) {
			cout << res[i];
		}
	}

}

int combi(int n, int r) {
	if (r == 0 || n == r) return 1;
	if (r == 1 || n - 1 == r) return n;
	return combi(n - 1, r) + combi(n - 1, r - 1);
}
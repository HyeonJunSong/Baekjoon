////22.07.08
//25m 41s

#include <iostream>
#include <vector>

using namespace std;

int N;
vector<long long> buildings;

int retVisibleBuilingNum(int I);
bool ifVisible(int I, int target);

int main() {

	cin >> N;

	buildings = vector<long long>(N);

	for (int i = 0; i < N; i++) cin >> buildings[i];

	int maxVisb = 0;
	for (int i = 0; i < N; i++) {
		int res = retVisibleBuilingNum(i);
		if (res > maxVisb) maxVisb = res;
	}

	cout << maxVisb;

	return 0;


}

int retVisibleBuilingNum(int I) {

	int cnt = 0;
	for (int i = 0; i < N; i++) {
		if (i == I) continue;
		if (ifVisible(I, i)) cnt++;
	}

	return cnt;
}

bool ifVisible(int I, int target) {
	if (target < I) {
		for (int i = target + 1; i < I; i++) {
			if ((buildings[I] - buildings[target]) / (double)(I - target) * (i - I) + buildings[I] <= buildings[i])
				return false;
		}
	}
	else {
		for (int i = I + 1; i < target; i++) {
			if ((buildings[target] - buildings[I]) / (double)(target - I) * (i - target) + buildings[target] <= buildings[i])
				return false;
		}
	}

	return true;
}
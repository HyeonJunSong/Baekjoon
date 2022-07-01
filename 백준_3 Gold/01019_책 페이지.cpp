#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

vector<int> nums(10, 0);

int N;
int digit;

void byFront(int d);

int main() {
	cin >> N;
	digit = to_string(N).size() - 1;

	for (int d = digit; d >= 1; d--) {
		byFront(d);
	}

	for (int i = 0; i <= N % 10; i++)
		nums[i] += 1;
	if (digit == 0) nums[0] -= 1;

	for (int i = 0; i < 10; i++)
		cout << nums[i] << ' ';

	return 0;
}

void byFront(int d) {

	int n = (int)(N / pow(10, d)) % 10;

	for (int i = 0; i < 10; i++) nums[i] += (n) * (d) * pow(10, d - 1);

	if (d == digit) {
		string ones = "";
		for (int i = 0; i < d; i++) ones += '1';

		nums[0] -= stoi(ones);
	}

	for (int i = 0; i < n; i++) nums[i] += pow(10, d);
	if (d == digit) nums[0] -= pow(10, d);

	nums[n] += N % (int)(pow(10, d)) + 1;
}
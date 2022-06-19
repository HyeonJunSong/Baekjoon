#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
	int N;
	cin >> N;

	//N벡터화.

	vector<int> num;

	while (N != 0) {
		num.push_back(N % 10);
		N = (int)(N / 10);
	}

	int digit = (int)(num.size());

	vector<int> numOf;
	for (int i = 0; i < 10; i++) numOf.push_back(0);


	/*
	//자리이전
	numOf[0] += digit * pow(10, digit - 1);
	for (int i = 0; i < digit; i++) {
		numOf[0] -= (int)(pow(10, i));
	}

	numOf[1] += digit * (int)(pow(10, digit - 1));
	numOf[2] += digit * (int)(pow(10, digit - 1));
	numOf[3] += digit * (int)(pow(10, digit - 1));
	numOf[4] += digit * (int)(pow(10, digit - 1));
	numOf[5] += digit * (int)(pow(10, digit - 1));
	numOf[6] += digit * (int)(pow(10, digit - 1));
	numOf[7] += digit * (int)(pow(10, digit - 1));
	numOf[8] += digit * (int)(pow(10, digit - 1));
	numOf[9] += digit * (int)(pow(10, digit - 1));
	*/

	//
	for (int i = digit; i > 1; i--) {
		for (int j = 0; j < num[i - 1]; j++) {
			numOf[num[j]] += (int)(pow(10, ))
		}
	}


	return 0;
}
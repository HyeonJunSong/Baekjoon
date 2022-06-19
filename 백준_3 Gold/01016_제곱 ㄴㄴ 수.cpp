////21.12.16
//입력 : 51s
//구현 : 1h 25m 59s
//tot : 1h 26m 50s

#include <iostream>
#include <set>
#include <vector>
#include <cmath>

using namespace std;


int main() {
	double min, max;
	cin >> min >> max;


	//primeTable 만들기

	vector<int> primeTable;
	primeTable.push_back(2);
	for (int i = 3; i <= (int)(pow(max, 0.5)); i++) {
		bool ifPrime = true;
		for (vector<int>::size_type j = 0; j < primeTable.size(); j++) {
			if (!(i % primeTable[j])) ifPrime = false;
			if ((int)(pow((double)(primeTable[j]), 2.0)) > i) break;
		}

		if (ifPrime) primeTable.push_back((double)(i));
	}

	vector<double> newPrimeTable;
	for (vector<int>::size_type i = 0; i < primeTable.size(); i++) {
		newPrimeTable.push_back(pow((double)(primeTable[i]), 2));
	}

	//primeTable 돌며 set에다가 배수들 집어넣기
	set<double> S;
	for (int i = 0; i < (int)(newPrimeTable.size()); i++) {
		double num = ceil(min / newPrimeTable[i]) * newPrimeTable[i];

		while (num <= max) {
			S.insert(num);
			num += newPrimeTable[i];
		}
	}

	//전체길이에서 set 사이즈 빼기
	cout << max - min + 1 - (double)(S.size());





	return 0;
}

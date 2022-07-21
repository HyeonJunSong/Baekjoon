////22.07.22
//이해 및 설계 : 10m 1s
//입력 : 2m 42s
//구현 : 2h 6m 59s
// '<'이거랑'>'이거 잘못 써서 34분 날려먹었다고?ㅋㅋ

//tot : 2h 19m 43s

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>

using namespace std;

set<int> prime;
map<int, map<int, int>> factors;

void primeInit();
map<int, int> factorization(int num);
map<int, int> getLCM(map<int, int> a, map<int, int> b);
map<int, int> toMake(map<int, int>& LCM, map<int, int>& num);
void mult(map<int, int> num, map<int, int>& target);
int mapToNum(map<int, int>& num);
pair<int, int> abbreviation(int a, int b);

int main() {
	
	primeInit();

	int N;
	cin >> N;
	vector<pair<int, int>> ingredient(N - 1);
	vector<pair<int, int>> ratio;

	for (int i = 0; i < N - 1; i++) {
		int inpRatio1, inpRatio2;
		cin >> ingredient[i].first >> ingredient[i].second >> inpRatio1 >> inpRatio2;
		ratio.push_back(abbreviation(inpRatio1, inpRatio2));
	}
	vector<map<int, int>> weight(N);
	vector<vector<int>> connected(N, vector<int>());

	for (int i = 0; i < N - 1; i++) {
		connected[ingredient[i].first].push_back(ingredient[i].second);
		connected[ingredient[i].second].push_back(ingredient[i].first);
	}

	if (factors.find(ratio[0].first) == factors.end()) factors[ratio[0].first] = factorization(ratio[0].first);
	if (factors.find(ratio[0].second) == factors.end()) factors[ratio[0].second] = factorization(ratio[0].second);

	weight[ingredient[0].first] = factors[ratio[0].first];
	weight[ingredient[0].second] = factors[ratio[0].second];

	for (int i = 1; i < N - 1; i++) {
		if (weight[ingredient[i].first].size() == 0) {

			//둘다 처음
			if (weight[ingredient[i].second].size() == 0) {
				ingredient.push_back(ingredient[i]);
				ingredient.erase(ingredient.begin() + i);

				ratio.push_back(ratio[i]);
				ratio.erase(ratio.begin() + i);

				i--;
			}
			else {
				//앞에거만 처음

				if (factors.find(ratio[i].second) == factors.end()) factors[ratio[i].second] = factorization(ratio[i].second);
				auto res = getLCM(factors[ratio[i].second], weight[ingredient[i].second]);

				auto multNum = toMake(res, weight[ingredient[i].second]);
				for (int j = 0; j < weight.size(); j++) {
					if (weight[j].size() != 0) mult(multNum, weight[j]);
				}

				if (factors.find(ratio[i].first) == factors.end()) factors[ratio[i].first] = factorization(ratio[i].first);
				weight[ingredient[i].first] = factors[ratio[i].first];
				mult(toMake(res, factors[ratio[i].second]), weight[ingredient[i].first]);

			}
		}
		else {
			if (weight[ingredient[i].second].size() == 0) {

				if (factors.find(ratio[i].first) == factors.end()) factors[ratio[i].first] = factorization(ratio[i].first);
				auto res = getLCM(factors[ratio[i].first], weight[ingredient[i].first]);

				auto multNum = toMake(res, weight[ingredient[i].first]);
				for (int j = 0; j < weight.size(); j++) {
					if (weight[j].size() != 0) mult(multNum, weight[j]);
				}

				if (factors.find(ratio[i].second) == factors.end()) factors[ratio[i].second] = factorization(ratio[i].second);
				weight[ingredient[i].second] = factors[ratio[i].second];
				mult(toMake(res, factors[ratio[i].first]), weight[ingredient[i].second]);

			}
			else {
				continue;
			}
		}
	}

	for (int i = 0; i < N; i++) cout << mapToNum(weight[i]) << ' ';

	return 0;

}

//에라토스테네스 체 함수
void primeInit() {

	for (int i = 2; i < 2520; i++) {
		bool ifPrime = true;
		for (auto iter = prime.begin(); iter != prime.end(); iter++) {
			if (i % *iter == 0) {
				ifPrime = false;
				break;
			}
		}
		if (ifPrime) prime.insert(i);
	}

}

//소인수 분해하는 함수
map<int, int> factorization(int num) {
	auto iter = prime.begin();

	map<int, int> newFactor;

	while (num != 1) {
		if (num % *iter == 0) {
			if (newFactor.find(*iter) != newFactor.end()) newFactor[*iter]++;
			else newFactor[*iter] = 1;
			num /= *iter;
		}
		else *iter++;
	}

	newFactor[1] = 1;

	return newFactor;
}

//최소공배수 구하는 함수
map<int, int> getLCM(map<int, int> a, map<int, int> b) {
	auto iterA = a.begin();
	auto iterB = b.begin();

	map<int, int> LCM;
	while (iterA != a.end() && iterB != b.end()) {
		if (iterA->first == iterB->first) {
			LCM[iterA->first] = iterA->second > iterB->second ? iterA->second : iterB->second;
			iterA++; iterB++;
		}
		else {
			if (iterA->first < iterB->first) {
				LCM[iterA->first] = iterA->second;
				iterA++;
			}
			else {
				LCM[iterB->first] = iterB->second;
				iterB++;
			}
		}
	}

	for (; iterA != a.end(); iterA++) LCM[iterA->first] = iterA->second;
	for (; iterB != b.end(); iterB++) LCM[iterB->first] = iterB->second;

	return LCM;
}

//최소공배수를 만들기 위한 수
map<int, int> toMake(map<int, int>& LCM, map<int, int>& num) {
	
	map<int, int> res;
	for (auto iter = LCM.begin(); iter != LCM.end(); iter++) {
		auto search = num.find(iter->first);
		if (search == num.end()) res[iter->first] = iter->second;
		else if(iter->second != search->second) res[iter->first] = iter->second - search->second;
	}

	return res;
}

void mult(map<int, int> num, map<int, int>& target) {
	for (auto iter = num.begin(); iter != num.end(); iter++) {
		if (target.find(iter->first) == target.end()) target[iter->first] = iter->second;
		else target[iter->first] += iter->second;
	}
}

int mapToNum(map<int, int>& num) {
	int res = 1;
	for (auto iter = num.begin(); iter != num.end(); iter++) res *= (int)(pow(iter->first, iter->second));

	return res;
}

pair<int, int> abbreviation(int a, int b) {
	vector<int> Tprimes = { 2, 3, 5, 7 };
	int i = 0;
	while (i < 4) {
		if (a % Tprimes[i] == 0 && b % Tprimes[i] == 0) {
			a /= Tprimes[i];
			b /= Tprimes[i];
		}
		else i++;
	}

	return make_pair(a, b);
}
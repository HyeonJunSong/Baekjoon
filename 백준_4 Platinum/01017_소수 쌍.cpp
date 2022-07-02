#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

set<int> primes;
vector<vector<int>> leftPairInd;
vector<int> rightPairInd;

bool makePair(int target, vector<bool>& check);

bool compare(vector<int> a, vector<int> b) {
	return a.size() < b.size();
}


int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int N;
	cin >> N;

	vector<int> nums(N);
	int largest = 0;
	for (int i = 0; i < N; i++) {
		cin >> nums[i];
		if (largest < nums[i]) largest = nums[i];
	}


	//에라체 만들기
	for (int i = 2; i < largest * 2; i++) {
		bool ifPrime = true;
		for (auto iter = primes.begin(); iter != primes.end(); iter++) {
			if (!(i % *iter)) {
				ifPrime = false;
				break;
			}
		}

		if (!ifPrime) continue;

		primes.insert(i);
	}

	vector<int> left;
	vector<int> right;

	left.push_back(nums[0]);
	for (int i = 1; i < nums.size(); i++) {
		if ((nums[0] + nums[i]) % 2) right.push_back(nums[i]);
		else left.push_back(nums[i]);
	}

	if (left.size() != right.size()) {
		cout << -1;
		return 0;
	}


	leftPairInd = vector<vector<int>>(left.size(), vector<int>());
	vector<int> answer;

	for (int i = 1; i < left.size(); i++) {
		for (int j = 0; j < right.size(); j++) {
			if (primes.find(left[i] + right[j]) != primes.end())
				leftPairInd[i].push_back(j);
		}
	}

	sort(leftPairInd.begin() + 1, leftPairInd.end(), compare);

	for (int i = 0; i < right.size(); i++) {
		if (primes.find(left[0] + right[i]) != primes.end()) {
			leftPairInd[0].clear();
			rightPairInd = vector<int>(right.size(), -1);	//누구한테 몇번째 인지

			rightPairInd[i] = 0;
			leftPairInd[0].push_back(i);

			bool ifCanMakePair = true;
			for (int i = 1; i < leftPairInd.size(); i++) {

				vector<bool> check(left.size(), false);
				check[0] = true;

				if (!makePair(i, check)) {
					ifCanMakePair = false;
					break;
				}
			}

			if (ifCanMakePair)
				answer.push_back(right[i]);
		}
	}



	if (answer.size() == 0) cout << -1;
	else {
		sort(answer.begin(), answer.end());
		for (int i = 0; i < answer.size(); i++) cout << answer[i] << ' ';
	}
	return 0;
}

bool makePair(int target, vector<bool>& check) {
	for (int i = 0; i < leftPairInd[target].size(); i++) {
		if (rightPairInd[leftPairInd[target][i]] == -1) {
			rightPairInd[leftPairInd[target][i]] = target;
			return true;
		}
	}

	for (int i = 0; i < leftPairInd[target].size(); i++) {
		if (rightPairInd[leftPairInd[target][i]] != -1) {

			if (check[rightPairInd[leftPairInd[target][i]]] || leftPairInd[rightPairInd[leftPairInd[target][i]]].size() == 1) continue;

			check[rightPairInd[leftPairInd[target][i]]] = true;
			if (!makePair(rightPairInd[leftPairInd[target][i]], check)) {
				continue;
			}
		}
		rightPairInd[leftPairInd[target][i]] = target;
		return true;
	}

	return false;
}
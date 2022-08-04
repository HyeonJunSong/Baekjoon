#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

class node {
public:
	string numStr;
	int st;
	int swapNum;

	node(string numStrP, int stP, int swapNumP) : numStr(numStrP), st(stP), swapNum(swapNumP) {};
};

int main() {

	int N, K;
	cin >> N >> K;
	string numStr = to_string(N);

	if (numStr.size() == 1) {
		cout << -1;
		return 0;
	}
	else if (numStr.size() == 2) {
		if (numStr[1] == '0') {
			cout << -1;
			return 0;
		}
		else if (K % 2 != 0) {
			char temp = numStr[0];
			numStr[0] = numStr[1];
			numStr[1] = temp;
		}

		cout << numStr;
		return 0;
	}

	string maxStr = "";
	for (int i = 0; i < numStr.size(); i++) maxStr += '0';

	deque<node> Q;
	Q.push_back(node(numStr, 0, 0));
	
	while (!Q.empty()) {
		node curNode = Q.front();
		Q.pop_front();
		if (curNode.swapNum == K) {
			if (maxStr.compare(curNode.numStr) < 0) maxStr = curNode.numStr;
			continue;
		}
		if (curNode.st == curNode.numStr.size() - 1) {
			if ((K - curNode.swapNum) % 2 != 0) {
				char temp = curNode.numStr[curNode.numStr.size() - 2];
				curNode.numStr[curNode.numStr.size() - 2] = curNode.numStr[curNode.numStr.size() - 1];
				curNode.numStr[curNode.numStr.size() - 1] = temp;
			}
			if (maxStr.compare(curNode.numStr) < 0) maxStr = curNode.numStr;
			continue;
		}

		//가장 큰 수 찾기
		char maxNum = curNode.numStr[curNode.st];
		for (int i = curNode.st + 1; i < curNode.numStr.size(); i++)
			if (maxNum < curNode.numStr[i]) maxNum = curNode.numStr[i];

		//Q에 넣기

		if (curNode.numStr[curNode.st] == maxNum) {
			Q.push_back(node(curNode.numStr, curNode.st + 1, curNode.swapNum));
		}

		for (int i = curNode.st + 1; i < curNode.numStr.size(); i++) {
			if (curNode.numStr[i] == maxNum) {
				string tempStr = curNode.numStr;
				char temp = tempStr[curNode.st];
				tempStr[curNode.st] = tempStr[i];
				tempStr[i] = temp;
				Q.push_back(node(tempStr, curNode.st + 1, curNode.swapNum + 1));
			}
		}
	}

	cout << maxStr;

	return 0;
}
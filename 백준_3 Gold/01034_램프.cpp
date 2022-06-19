////21.12.17
//1h 36m 51s
//코드 븅신같이 헷갈려서 오래걸림;;

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct Node {
	int numOfD;	//dark
	int numOfS;	//same
}node;

int numOfHoles(string str);

int main() {
	int N, M, K;
	cin >> N >> M;
	
	string* lamp = new string[N];
	for (int i = 0; i < N; i++) {
		cin >> lamp[i];
	}
	cin >> K;


	node* numOfDark = new node[N];

	bool* check = new bool[N];
	for (int i = 0; i < N; i++) check[i] = true;

	int n = 0;
	for (int i = 0; i < N; i++) {
		if (!check[i]) continue;
		numOfDark[n] = { numOfHoles(lamp[i]), 1 };

		check[i] = false;
		for (int j = i + 1; j < N; j++) {
			if (!check[j]) continue;

			if (lamp[i] == lamp[j]) {
				check[j] = false;
				numOfDark[n].numOfS++;
			}
		}
		n++;
	}


	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (numOfDark[i].numOfS < numOfDark[j].numOfS) {
				node temp = numOfDark[i];
				numOfDark[i] = numOfDark[j];
				numOfDark[j] = temp;
			}
		}
	}


	bool ifKOdd = K % 2;

	bool ifPrinted = false;
	for (int i = 0; i < n; i++) {
		if (numOfDark[i].numOfD <= K && (ifKOdd == numOfDark[i].numOfD % 2)) {
			cout << numOfDark[i].numOfS;
			ifPrinted = true;
			break;
		}
	}

	if (!ifPrinted) cout << 0;


	return 0;
}

int numOfHoles(string str) {
	int tot = 0;
	for (string::size_type i = 0; i < str.size(); i++) {
		if (str[i] == '0') tot++;
	}
	return tot;
}
//22.02.09

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


typedef struct Node {
	int W;
	int V;
	bool check;
}node;

bool comp(node n1, node n2) {
	return n1.W > n2.W;
}

int** memo;
vector<node> thing;
int N;

int MaxVal(int K, int prvInd);

int main() {
	int K;
	cin >> N >> K;

	memo = new int* [K + 1];
	for (int i = 0; i < K + 1; i++) {
		memo[i] = new int[K + 1];
		for (int j = 0; j < K + 1; j++)
			memo[i][j] = -1;
	}
	for (int i = 0; i < N; i++) {
		int inpW, inpV;
		cin >> inpW >> inpV;
		thing.push_back({ inpW, inpV, false });
	}

	sort(thing.begin(), thing.end(), comp);

	int ans = MaxVal(K, 0);
	if (ans < 0) cout << 0;
	else cout << ans;


	return 0;
}

int MaxVal(int K, int prvInd) {	//K의 무게로 낼 수 있는 최대 V
	int i = prvInd;	
	for (; i < N; i++)
		if (thing[i].W <= K) break;
	


	if (i == N)
		return 0;

	int Max = -1;
	for (; i < N; i++) {
		int cur = memo[K - thing[i].W][prvInd];

		if (cur == -1){
			int cur = thing[i].V + MaxVal(K - thing[i].W, i + 1);
			memo[K - thing[i].W][prvInd] = cur;
		}

		if (Max < cur) {
			Max = cur;
		}
	}

	return Max;
}